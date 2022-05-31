#include <stdio.h>
#include <string.h>

#define MAX_USER 50

struct parse_user {
    char username[10];
    char password[8];
    bool used;
    struct parse_user *next;
};

FILE *file_open;
char buffer[50];

bool login(char *username, char *password);
bool signup(char *username, char *password);
struct parse_user *user_parsing();
int getHash(char *username);
void removeNewLine();


bool login(char *username, char *password) {
    int usernameHash = getHash(username);
    struct parse_user *data = user_parsing();
    

    if(strcmp(data[usernameHash].username, username) == 0
        && strcmp(data[usernameHash].password, password) == 0) return true;
    else {
        struct parse_user *iterate = &(data[usernameHash]);
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

struct parse_user *user_parsing() {
    struct parse_user *user_data = (struct parse_user*)malloc(MAX_USER * sizeof(struct parse_user));
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
        while(fgets(buffer, 50, file_open)) {
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
                struct parse_user *temp = (struct parse_user*)malloc(sizeof(struct parse_user));
                struct parse_user *iterate = &(user_data[index]);
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

int getHash(char *username) {
    int index = 0;
    for(int i = 0; i < sizeof(username) / sizeof(username[0]); i++) {
        index += username[i];
    }
    return index % MAX_USER;
}

void removeNewLine() {
    fflush(stdin);
}

bool signup(char *username, char *password) {
    struct parse_user *data = user_parsing();
    int usernameHash = getHash(username);

    if(strcmp(data[usernameHash].username, username) == 0) return false;
    else {
        struct parse_user *iterate = &(data[usernameHash]);
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

//nina