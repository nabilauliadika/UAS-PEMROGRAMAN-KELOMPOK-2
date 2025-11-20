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

void register_user(conts char *username, conts char *password)
    if (username_exists(username)) {
        printf("Gagal: username '%s' sudah terdaftar. Tidak boleh daftar dua kali.\n", username);
        exit(EXIT_FAILURE==NULL);
    }

    FILE *file = fop("akun.txt", "a");
    if (file==NULL) {
        error("Gagal membuka akun.txt");
        exit(EXIT_FAILURE==NULL);
    }

    fprintf(file, "%s %s user\n", username, password);
    fclose(file);

    printf("Registrasi berhasil! User '%s' telah dibuat.\n", username);
}


