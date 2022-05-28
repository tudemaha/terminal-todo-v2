#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

struct user {
    char username[11];
    char password[9];
};

int main() {
    char choice;
    struct user temp;

    start:
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
            printf("\nUsername\t: ");
            removeNewLine();
            fgets(temp.username, 11, stdin);
            temp.username[strcspn(temp.username, "\n")] = 0;

            printf("Password\t: ");
            removeNewLine();
            fgets(temp.password, 9, stdin);
            temp.password[strcspn(temp.password, "\n")] = 0;

            if(login(temp.username, temp.password));
            else {
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
            printf(
                "\nSyarat pembuatan akun:\n"
                "1. Username maksimal 10 huruf.\n"
                "2. Username tidak boleh menggunakan spasi.\n"
                "3. Password dibuat dengan kombinasi angka, huruf, dan karakter.\n"
                "4. Password tidak maksimal 8 karakter.\n"
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
                printf("\nAkun berhasil didaftarkan.\n");
                printf("Username\t: %s\nPassword\t: %s\n", temp.username, temp.password);
                printf("\nSilakan gunakan akun Anda untuk masuk.\n");
                system("pause");
            } else {
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