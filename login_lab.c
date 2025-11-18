#include <stdio.h>  // deklarasi library standar input output
#include <stdlib.h> // deklarasi library standar umum
#include <string.h> // deklarasi library string
#include <stdbool.h> // deklarasi library boolean


int main (int argc, char *argv[]) {
    FILE  *file; // deklarasi pointer file
    char username[50], password[50], role[50]; // deklarasi variabel untuk username, password, dan role
    bool login_success = false; // variabel untuk menandai keberhasilan login

    // memeriksa jumlah argumen
    if (argc != 3) {
        printf("Cara penggunaan:\n./%s <username> <password>\n", argv[0]);
        return EXIT_FAILURE; // mengembalikan nilai gagal
    }

    file = fopen("akun.txt", "r"); // membuka file akun.txt dalam mode baca
    if (file == NULL) { // memeriksa apakah file berhasil dibuka
        perror("Gagal membuka file akun.txt");
        return EXIT_FAILURE; // mengembalikan nilai gagal
    }

    while (fscanf(file, "%s %s %s", username, password, role) != EOF) {
        if (strcmp(argv[1], username) == 0 && strcmp(argv[2], password) == 0) {
            printf("Login berhasil! Selamat datang, %s. Role Anda: %s\n", username, role);
            login_success = true; // menandai bahwa login berhasil
            break; // keluar dari loop setelah menemukan kecocokan
        }
    }

    fclose(file); // menutup file

    if (!login_success) { // memeriksa apakah login gagal
        printf("Login gagal! Username atau password salah.\n");
        return EXIT_FAILURE; // mengembalikan nilai gagal
    }

    if (strcmp(role, "admin") == 0) { // memeriksa apakah role adalah admin
        menuAdmin(); // memanggil fungsi menuAdmin
    } else {
        printf("Fitur untuk role selain admin belum tersedia.\n");
    }

    return EXIT_SUCCESS; // mengembalikan nilai sukses
}


    
