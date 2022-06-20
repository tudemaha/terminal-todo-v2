#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

struct user {
    char username[11];
    char password[9];
};

void currentSession(char *username);

int main() {
    char choice;
    struct user temp;

    start:
    system("cls");
    system("color 07");
    printf(
        "=================================\n"
        "||      SELAMAT DATANG DI      ||\n"
        "||   APLIKASI TERMINAL TO-DO   ||\n"
        "=================================\n\n"
    );

    printf("============ BERANDA ============\n");
    printf("Silakan pilih menu berikut:\n1. Masuk\n2. Daftar\n3. Keluar Program\n");

    insert_menu:
    printf("Masukkan pilihan: ");
    scanf(" %c", &choice);

    switch(choice) {
        case '1':
            start_login:
            system("color 07");
            printf("\nUsername\t: ");
            removeNewLine();
            fgets(temp.username, 11, stdin);
            temp.username[strcspn(temp.username, "\n")] = 0;

            printf("Password\t: ");
            removeNewLine();
            fgets(temp.password, 9, stdin);
            temp.password[strcspn(temp.password, "\n")] = 0;

            if(login(temp.username, temp.password)) currentSession(temp.username);
            else {
                system("color 0c");
                printf("\nUsername atau password yang Anda masukkan tidak terdaftar.\n");
                login_confirm:
                printf("Ingin mengulangi? (y/n): ");
                scanf(" %c", &choice);
                if(choice == 'y' || choice == 'Y') goto start_login;
                else if(choice == 'n' || choice == 'N') goto start;
                else goto login_confirm;
            }

            goto start;
            break;

        case '2':
            system("color 07");
            printf(
                "\nSyarat pembuatan akun:\n"
                "1. Username maksimal 10 huruf.\n"
                "2. Username tidak boleh menggunakan spasi.\n"
                "3. Password dibuat dengan kombinasi angka, huruf, dan karakter.\n"
                "4. Password maksimal 8 karakter.\n"
                "5. Password tidak boleh berisi karakter titik dua ';'.\n"
                "6. Jika karakter yang dimasukkan di luar batas, maka akan diambil n karakter pertama.\n"
            );

            start_signup:
            printf("\nUsername\t: ");
            removeNewLine();
            fgets(temp.username, 11, stdin);
            temp.username[strcspn(temp.username, "\n")] = 0;
            
            printf("Password\t: ");
            removeNewLine();
            fgets(temp.password, 9, stdin);
            temp.password[strcspn(temp.password, "\n")] = 0;

            if(signup(temp.username, temp.password)) {
                system("color 17");
                printf("\nAkun berhasil didaftarkan.\n");
                printf("Username\t: %s\nPassword\t: %s\n", temp.username, temp.password);
                printf("\nSilakan gunakan akun Anda untuk masuk.\n");
                system("pause");
            } else {
                system("color 0c");
                printf("\nUsername yang Anda masukkan sudah digunakan.\n");
                signup_confirm:
                printf("Ingin mengulangi? (y/n): ");
                scanf(" %c", &choice);
                if(choice == 'y' || choice == 'Y') goto start_signup;
                else if(choice == 'n' || choice == 'N') goto start;
                else goto signup_confirm;
            }

            goto start;
            break;

        case '3':
            printf("\n");
            insert_exit:
            printf("Yakin untuk keluar program? (y/n): ");
            scanf(" %c", &choice);
            if(choice == 'y' || choice == 'Y') exit(0);
            else if(choice == 'n' || choice == 'N') goto start;
            else goto insert_exit;
            break;

        default:
            goto insert_menu;
            break;
    }

    return 0;
}

void currentSession(char *username) {
    char option;

    session:
    system("cls");
    system("color 17");
    printf("========== SESI AKTIF ==========\n");
    printf("Anda masuk sebagai %s.\n\n", username);
    
    printf("Menu:\n1. Tambah To-Do\n2. Selesaikan To-Do\n3. Lihat To-Do List\n4. Keluar\n");
    insert_option:
    printf("Masukkan pilihan: ");
    scanf(" %c", &option);

    switch(option) {
        case '1':
            insert_todo(username);
            goto session;
            break;

        case '2':
            printf("\nMode penyelesaian:\n1. Mode Biasa\n2. Mode Strict\n3. Batal\n");
            mode:
            printf("Masukkan pilihan: ");
            scanf(" %c", &option);
            switch(option) {
                case '1':
                    general_finish(username);
                    goto session;
                    break;

                case '2':
                    strict_finish(username);
                    goto session;
                    break;

                case '3':
                    goto session;
                    break;

                default:
                    goto mode;
                    break;
            }
            break;

        case '3':
            show_todo(username);
            system("pause");
            goto session;
            break;
            
        case '4':
            printf("\n");
            exit:
            printf("Keluar dan kembali ke beranda? (y/n): ");
            scanf(" %c", &option);
            if(option == 'y' || option == 'Y') return;
            else if(option == 'n' || option == 'N') goto session;
            else goto exit;
            break;

        default:
            goto insert_option;
            break;
    }
}