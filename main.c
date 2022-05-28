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

    insert_choice:
    printf("Masukkan pilihan: ");
    scanf(" %c", &choice);

    switch(choice) {
        case '1':
            printf("\nUsername\t: ");
            removeNewLine();
            fgets(temp.username, 11, stdin);
            temp.username[strcspn(temp.username, "\n")] = 0;

            printf("Password\t: ");
            removeNewLine();
            fgets(temp.password, 9, stdin);
            temp.password[strcspn(temp.password, "\n")] = 0;

            printf("%d\n", login(temp.username, temp.password));

            system("pause");
            system("cls");
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
                "6. Jika karakter yang dimasukkan di luar batas, maka akan diambil n karakter pertama.\n\n"
            );

            start_signup:
            printf("Username\t: ");
            removeNewLine();
            fgets(temp.username, 11, stdin);
            temp.username[strcspn(temp.username, "\n")] = 0;
            
            printf("Password\t: ");
            removeNewLine();
            fgets(temp.password, 9, stdin);
            temp.password[strcspn(temp.password, "\n")] = 0;

            printf("%d\n", signup(temp.username, temp.password));
            break;

        case '3':
            break;
        default:
            break;
    }

    return 0;
}