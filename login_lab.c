#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fungsiAdmin.h"
#include "fungsiUser.h"


int main (int argc, char *argv[]) {
    FILE  *file;
    char username[50], password[50], role[50];
    char input_user[50], input_pass[50];
    bool login_success = false;

    // cek argumen
    if (argc != 3) {
        printf("Cara penggunaan:\n./%s <username> <password>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // copy input agar aman
    strncpy(input_user, argv[1], 49);
    strncpy(input_pass, argv[2], 49);

    file = fopen("akun.txt", "r");
    if (file == NULL) {
        perror("Gagal membuka file akun.txt");
        return EXIT_FAILURE;
    }

    // baca file
    while (fscanf(file, "%49s %49s %49s", username, password, role) != EOF) {
        if (strcmp(input_user, username) == 0 &&
            strcmp(input_pass, password) == 0)
        {
            printf("Login berhasil! Selamat datang, %s. Role Anda: %s\n",
                   username, role);
            login_success = true;
            break;
        }
    }

    fclose(file); // tutup file

    if (!login_success) {
        printf("Login gagal! Username atau password salah.\n");
        return EXIT_FAILURE;
    }

    // cek role
    if (strcmp(role, "admin") == 0) {
        menuAdmin();
    } else {
        printf("Fitur untuk role selain admin belum tersedia.\n");
    }

    return EXIT_SUCCESS;
}



    
