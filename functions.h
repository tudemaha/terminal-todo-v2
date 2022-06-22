#include <stdio.h>
#include <string.h>

#define MAX_USER 50
#define MAX_TODO 50

struct User {
    char username[10];
    char password[8];
    bool used;
    struct User *next;
};

struct Todo {
    char activity[100];
    char date[11];
    char status;
    struct Todo *next;
};

FILE *file_open;
char buffer[1024];

bool login(char *username, char *password);
bool signup(char *username, char *password);
struct User *parse_user();
int getHash(char *username);
void removeNewLine();
void general_finish(char *username);
void strict_finish(char *username);
struct Todo *parse_todo(char *username);
void insert_todo(char *username);
void show_todo(char *username);



void removeNewLine() {
    fflush(stdin);
}

bool login(char *username, char *password) {
    int usernameHash = getHash(username);
    struct User *data = parse_user();
    

    // printf("%s %s\n", username, data[usernameHash].username);
    // printf("%s %s\n", password, data[usernameHash].password);

    if(strcmp(data[usernameHash].username, username) == 0
        && strcmp(data[usernameHash].password, password) == 0) return true;
    else {
        struct User *iterate = &(data[usernameHash]);
        while(iterate->next != NULL) {
            iterate = iterate->next;
            if(strcmp(iterate->username, username) == 0
                && strcmp(iterate->password, password) == 0) {
                    return true;
                }
        }
    }
    
    return false;
}

int getHash(char *username) {
    int index = 0;
    for(int i = 0; i < sizeof(username) / sizeof(username[0]); i++) {
        index += username[i];
    }
    return index % MAX_USER;
}

bool signup(char *username, char *password) {
    struct User *data = parse_user();
    int usernameHash = getHash(username);

    if(strcmp(data[usernameHash].username, username) == 0) return false;
    else {
        struct User *iterate = &(data[usernameHash]);
        while(iterate->next != NULL) {
            iterate = iterate->next;
            if(strcmp(iterate->username, username) == 0) return false;
        }
    }

    file_open = fopen("user_db.csv", "a+");
    fprintf(file_open, "%s;%s;\n", username, password);
    fclose(file_open);

    char *filename = malloc(sizeof(username));
    strcpy(filename, username);
    strcat(filename, ".csv");
    file_open = fopen(filename, "w");
    fclose(file_open);
    
    return true;
}

struct User *parse_user() {
    struct User *user_data = (struct User*)malloc(MAX_USER * sizeof(struct User));
    for(int i = 0; i < MAX_USER; i++) {
        user_data[i].used = false;
        user_data[i].next = NULL;
    }

    file_open = fopen("user_db.csv", "r");
    
    if(!file_open) {
        printf("\nData user tidak tersedia, aplikasi ditutup...\n");
        system("pause");
        exit(0);
    } else {
        while(fgets(buffer, 100, file_open)) {
            // printf("%s\n", buffer);
            char *value = strtok(buffer, ";");
            // printf("%s\n", value);
            int index = getHash(value);
            if(user_data[index].used == false) {
                user_data[index].used = true;
                strcpy(user_data[index].username, value);
                value = strtok(NULL, ";");
                // printf("%s\n", value);
                strcpy(user_data[index].password, value);
            } else {
                struct User *temp = (struct User*)malloc(sizeof(struct User));
                struct User *iterate = &(user_data[index]);
                temp->used = true;
                temp->next = NULL;
                strcpy(temp->username, value);
                value = strtok(NULL, ";");
                strcpy(temp->password, value);

                while(iterate->next != NULL) {
                    iterate = iterate->next;
                }
                iterate->next = temp;
            }
        }
    }
    fclose(file_open);
    return user_data;
}

struct Todo *parse_todo(char *username) {
    struct Todo *head = NULL;
    struct Todo *tail = NULL;
    
    char *filename = malloc(sizeof(username));
    strcpy(filename, username);
    strcat(filename, ".csv");

    file_open = fopen(filename, "r");

    if(!file_open) {
        printf("\nData user tidak tersedia, aplikasi ditutup...\n");
        system("pause");
        exit(0);
    } else {
        while(fgets(buffer, 100, file_open)) {
            struct Todo *temp = (struct Todo*)malloc(sizeof(struct Todo));

            char *value = strtok(buffer, ";");
            strcpy(temp->activity, value);

            value = strtok(NULL, ";");
            strcpy(temp->date, value);

            value = strtok(NULL, ";");
            temp->status = *value;

            temp->next = NULL;

            if(head == NULL) head = tail = temp;
            else {
                tail->next = temp;
                tail = temp;
            }
        }
    }

    fclose(file_open);
    return head;
}

void insert_todo(char *username){
    char *filename = malloc(sizeof(username));
    strcpy(filename, username);
    strcat(filename, ".csv");


    char todo[2][500];

    tambah:
    removeNewLine();
    printf("\nIngatkan untuk (maks. 500 karakter): ");
    fgets(todo[0], 500, stdin);
    todo[0][strcspn(todo[0], "\n")] = 0;

    if(strlen(todo[0]) == 0) {
        printf("Anda belum memasukkan kegiatan.\n");
        goto tambah;
    }

    printf("Deadline (format: dd/mm/yyyy) [opsional]: ");
    fgets(todo[1], 11, stdin);
    todo[1][strcspn(todo[1], "\n")] = 0;
    if(strlen(todo[1]) == 0) strcpy(todo[1], "nd");

    if(!file_open) {
        printf("\nData user tidak tersedia, aplikasi ditutup...\n");
        system("pause");
        exit(0);
    } else {
        file_open = fopen(filename, "a+");
        fprintf(file_open, "%s;%s;0;\n", todo[0], todo[1]);
        fclose(file_open);
        printf("\nBerhasil memasukkan kegiatan.\n");
    }

    char pilihan;
    removeNewLine();
    ulang:
    printf("Ingin memasukkan kegiatan lain? (y/n): ");
    scanf("%c", &pilihan);
    switch(pilihan) {
        case 'y':
            goto tambah;
            break;

        case 'n':
            return;
            break;

        default:
        goto ulang;
            break;
    }

}

void show_todo(char *username){
    struct Todo *data = parse_todo(username);
    struct Todo *iterate = data;
    int id = 0;
    char *filename = malloc(sizeof(username));

    strcpy(filename, username);
    strcat(filename, ".csv");

    file_open = fopen(filename, "r");

    if(!file_open) {
        printf("\nData user tidak tersedia, aplikasi ditutup...\n");
        system("pause");
        exit(0);
    } else {
        printf("\nTo-Do List:\n");
        while(iterate != NULL) {
            printf("%d - %s - %s - %c\n", id, iterate->activity, iterate->date, iterate->status);
            id++;
            iterate = iterate->next;
        }
    }
    fclose(file_open);
}

void general_finish(char *username) {
    struct Todo *data = parse_todo(username);
    struct Todo *iterate;
    int id = 0, finish;
    char status;

    show_todo(username);

    iterate = data;
    while(iterate != NULL) {
        id++;
        iterate = iterate->next;
    }

    general_start:
    printf("\nMasukkan ID To-Do untuk diselesaikan (masukkan -1 untuk membatalkan): ");
    scanf("%d", &finish);

    if(finish < -1 || finish > id) {
        printf("Masukkan ID yang valid\n");
        goto general_start;
    }
    else if(finish == -1) return;
    else {
        iterate = data;
        for(int i = 0; i < finish; i++) {
            iterate = iterate->next;
        }
    }

    option:
    printf("Yakin menyelesaikan '%s'? (y/n): ", iterate->activity);
    scanf(" %c", &status);
    if(status == 'y' || status == 'Y') {
        iterate->status = '1';
    }
    else if(status == 'n' || status == 'N') goto general_start;
    else goto option;


    char *filename = malloc(sizeof(username));
    strcpy(filename, username);
    strcat(filename, ".csv");

    file_open = fopen(filename, "w");
    iterate = data;
    while(iterate != NULL) {
        fprintf(file_open, "%s;%s;%c;\n", iterate->activity, iterate->date, iterate->status);
        iterate = iterate->next;
    }
    fclose(file_open);

    printf("Berhasil menyelesaikan.\n");
    system("pause");
}

void strict_finish(char *username) {
    struct Todo *data = parse_todo(username);
    struct Todo *iterate;
    char status;
    
    iterate = data;
    while(iterate != NULL) {
        if(iterate->status == '0') {
            break;
        }
        iterate = iterate->next;
    }
    
    confirm:
    printf(
        "\nStrict mode akan menyelesaikan To-Do teratas yang belum diselesaikan\n"
        "Lanjutkan menyelesaikan '%s'? (y/n): ", iterate->activity);
    scanf(" %c", &status);

    if(status == 'y' || status == 'Y') iterate->status = '1';
    else if(status == 'n' || status == 'N') return;
    else goto confirm;
    
    char *filename = malloc(sizeof(username));
    strcpy(filename, username);
    strcat(filename, ".csv");

    file_open = fopen(filename, "w");
    iterate = data;
    while(iterate != NULL) {
        fprintf(file_open, "%s;%s;%c;\n", iterate->activity, iterate->date, iterate->status);
        iterate = iterate->next;
    }
    fclose(file_open);

    printf("Berhasil menyelesaikan.\n");
    system("pause");
}

