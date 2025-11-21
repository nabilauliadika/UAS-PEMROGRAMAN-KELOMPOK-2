#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fungsiAdmin.h"
#include "fungsiUser.h"

// Fungsi utama
int main(int argc, char *argv[]) // Program utama untuk login dan menampilkan menu sesuai role
{
    if (argc != 3) { // Memeriksa jumlah argumen
        printf("Cara penggunaan:\n./%s <username> <password>\n", argv[0]);
        return EXIT_FAILURE; // Keluar jika argumen tidak sesuai
    }

    char input_user[50], input_pass[50]; // Menyimpan username dan password dari argumen
    char username[50], password[50], role[50]; // Menyimpan data dari file akun.txt
    bool login_success = false; // Menandai status login

    strncpy(input_user, argv[1], sizeof(input_user)-1); // Menyalin username dari argumen
    strncpy(input_pass, argv[2], sizeof(input_pass)-1); // Menyalin password dari argumen

    FILE *file = fopen("akun.txt", "r");  // Membuka file akun.txt untuk membaca data user
    // Memeriksa apakah file berhasil dibuka
    if (!file) {
        perror("Gagal membuka akun.txt");
        return EXIT_FAILURE;
    }

    // Membaca setiap baris dan memeriksa username dan password
    while (fscanf(file, "%49s %49s %49s", username, password, role) == 3) {
        if (strcmp(input_user, username) == 0 && strcmp(input_pass, password) == 0) // Memeriksa kecocokan username dan password 
        {
            printf("\nLogin berhasil! Selamat datang, %s.\nRole: %s\n", username, role);
            login_success = true; // Menandai login berhasil
            break; // Keluar dari loop jika login berhasil
        }
    }
    fclose(file); // Menutup file setelah selesai membaca

    if (!login_success) { // Memeriksa status login
        printf("Login gagal! Username atau password salah.\n");
        return EXIT_FAILURE; // Keluar jika login gagal
    }

    if (strcmp(role, "admin") == 0) //jika role admin, tampilkan menu admin
    {
        menuAdmin();
    } 
    else if (strcmp(role, "user") == 0) //jika role user, tampilkan menu user
    {
        menuUser(username);
    } 
    else //jika role tidak valid
    {
        printf("Role tidak valid.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; // Keluar dengan kode sukses
}

