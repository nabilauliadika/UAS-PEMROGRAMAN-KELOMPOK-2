#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fungsiAdmin.h"
#include "fungsiUser.h"

bool username_exists(const char *username) {
    FILE *file = fopen("akun.txt", "r");
    if (!file) return false;  

    char u[50], p[50], r[50];
    while (fscanf(file, "%49s %49s %49s", u, p, r) == 3) {
        if (strcmp(u, username) == 0) {
            fclose(file);
            return true;  
        }
    }
    fclose(file);
    return false;
}

void register_user(const char *username, const char *password) {
    if (username_exists(username)) {
        printf("Gagal: username '%s' sudah terdaftar. Tidak boleh daftar dua kali.\n", username);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen("akun.txt", "a");
    if (!file) {
        perror("Gagal membuka akun.txt");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s %s user\n", username, password);
    fclose(file);

    printf("Registrasi berhasil! User '%s' telah dibuat.\n", username);
}

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Cara penggunaan:\n");
        printf("./%s register <username> <password>\n", argv[0]);
        printf("./%s login <username> <password>\n\n", argv[0]);
        return EXIT_FAILURE;
    }

    char mode[20];
    strncpy(mode, argv[1], sizeof(mode)-1);

    char input_user[50], input_pass[50];
    strncpy(input_user, argv[2], sizeof(input_user)-1);
    strncpy(input_pass, argv[3], sizeof(input_pass)-1);

    // MODE REGISTER
    if (strcmp(mode, "register") == 0) {
        register_user(input_user, input_pass);
        return EXIT_SUCCESS;
    }
