#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fungsiAdmin.h"
#include "fungsiUser.h"

// Fungsi untuk memeriksa apakah username sudah ada
bool username_exists(const char *username) {
    FILE *file = fopen("akun.txt", "r");
    if (!file) return false;  

    // Membaca setiap baris dan memeriksa username
    char u[50], p[50], r[50];
    // Membaca file hingga akhir
    while (fscanf(file, "%49s %49s %49s", u, p, r) == 3) {
        if (strcmp(u, username) == 0) {
            fclose(file);
            return true;  
        }
    }
    fclose(file); // Menutup file setelah selesai membaca
    return false;
}

// Fungsi untuk mendaftarkan user baru
void register_user(const char *username, const char *password) {
    // Memeriksa apakah username sudah ada
    if (username_exists(username)) {
        printf("Gagal: username '%s' sudah terdaftar. Tidak boleh daftar dua kali.\n", username);
        exit(EXIT_FAILURE);
    }

    // Membuka file untuk menambahkan user baru
    FILE *file = fopen("akun.txt", "a");
    if (!file) {
        perror("Gagal membuka akun.txt"); // Menampilkan pesan error jika gagal membuka file
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s %s user\n", username, password); // Menambahkan user baru ke file
    fclose(file);

    printf("Registrasi berhasil! User '%s' telah dibuat.\n", username);
}

// Fungsi utama
int main(int argc, char *argv[]) 
{

    // Memeriksa jumlah argumen
    if (argc != 4) { // Program name + mode + username + password
        printf("Cara penggunaan:\n"); 
        printf("./%s register <username> <password>\n", argv[0]);
        printf("./%s login <username> <password>\n\n", argv[0]);
        return EXIT_FAILURE; // Keluar dengan kode kegagalan
    }

    char mode[20]; // Menyimpan mode operasi (register atau login)
    strncpy(mode, argv[1], sizeof(mode)-1); // Menyalin mode dari argumen

    char input_user[50], input_pass[50]; // Menyimpan username dan password dari argumen
    strncpy(input_user, argv[2], sizeof(input_user)-1); // Menyalin username dari argumen
    strncpy(input_pass, argv[3], sizeof(input_pass)-1); // Menyalin password dari argumen

    // MODE REGISTER
    // Memeriksa apakah mode adalah "register"
    if (strcmp(mode, "register") == 0) {
        register_user(input_user, input_pass); // Memanggil fungsi untuk mendaftarkan user baru
        return EXIT_SUCCESS;
    }
}
