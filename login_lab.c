#include <stdio.h>  // deklarasi library standar input output
#include <stdlib.h> // deklarasi library standar umum
#include <string.h> // deklarasi library string

// mendefinisikan struktur data untuk menyimpan informasi akun
typedef struct {
    char username[50];
    char password[50];
    char role[20];
} Akun; // struktur data Akun

// fungsi utama program
int main (int argc, char *argv[]) // fungsi untuk menerima argumen dari command line
{
    // memeriksa jumlah argumen yang diberikan
    if (argc != 3) 
    {
        printf("\nCara pakai: %s <username> <password>\n\n", argv[0]);
        return 1;
    }

    // menyimpan argumen username dan password
    char *input_username = argv[1];
    char *input_password = argv[2];

    // membuka file yang berisi data akun
    FILE *file = fopen("file.txt", "r");

    // memeriksa apakah file berhasil dibuka
    if (file == NULL) { 
        printf("Tidak dapat membuka file");
        return 1;
    }

    // deklarasi variabel untuk menyimpan informasi akun
    Akun akun;
    int login_success = 0; // variabel untuk menandai keberhasilan login


    // membaca data akun dari file dan memeriksa kecocokan dengan input
    while (fscanf(file, "%s %s %s", akun.username, akun.password, akun.role) != EOF) 
    {
        // membandingkan input dengan data akun
        if (strcmp(input_username, akun.username) == 0 && strcmp(input_password, akun.password) == 0) 
        {
            // jika cocok, menampilkan pesan sukses dan peran akun
            printf("\nLogin berhasil!\nRole anda adalah: %s\n\n", akun.role);
            login_success = 1;
            break; // keluar dari loop setelah login berhasil
        }
    }

    // menutup file
    fclose(file);

    // jika login gagal, menampilkan pesan kegagalan
    if (!login_success) 
    {
        printf("\nLogin gagal! Username atau password salah.\n\n");
    }

    return EXIT_SUCCESS; // mengembalikan nilai sukses
}