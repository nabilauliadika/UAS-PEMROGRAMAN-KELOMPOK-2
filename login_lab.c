#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fungsiAdmin.h"
#include "fungsiUser.h"

int main(int argc, char *argv[]) 
{
    // Validasi argumen
    if (argc != 3) 
    {
        printf("Cara penggunaan:\n./%s <username> <password>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char input_user[50], input_pass[50];
    char username[50], password[50], role[50];
    bool login_success = false;

    // Salin input agar aman
    strncpy(input_user, argv[1], sizeof(input_user)-1);
    strncpy(input_pass, argv[2], sizeof(input_pass)-1);

    // Buka file akun
    FILE *file = fopen("akun.txt", "r");
    if (!file) 
    {
        perror("Gagal membuka file akun.txt");
        return EXIT_FAILURE;
    }

    // Proses login
    while (fscanf(file, "%49s %49s %49s", username, password, role) == 3) 
    {
        if (strcmp(input_user, username) == 0 && strcmp(input_pass, password) == 0)
        {
            printf("Login berhasil! SELAMAT DATANG, %s.\nRole Anda: %s\n", username, role);
            login_success = true;
            break;
        }
    }
    fclose(file);

    // Jika gagal login
    if (!login_success) 
    {
        printf("Login gagal! Username atau password salah.\n");
        return EXIT_FAILURE;
    }

    // Cek role
    if (strcmp(role, "admin") == 0) 
    {
        menuAdmin(); // Panggil menu admin
    } else if (strcmp(role, "user") == 0) 
    {
        menuUser(username); // Panggil menu user
    } else 
    {
        printf("Role tidak dikenal.\n"); //jika role bukan admin atau user
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
