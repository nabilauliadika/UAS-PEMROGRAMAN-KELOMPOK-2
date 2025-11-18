#include <stdio.h>  // deklarasi library standar input output
#include <stdlib.h> // deklarasi library standar umum
#include <string.h> // deklarasi library string
#include <stdbool.h> // deklarasi library boolean


/*====struct untuk data alat lab===*/
struct AlatLab {
    unsigned int id;
    char nama[50];
    char merk[50];
    char model[50];
    unsigned int tahun;
    unsigned int jumlah_unit;
    unsigned int jumlah_tersedia;
}

/*====fungsi untuk load data alat lab dari file===*/
int loadAlat(struct AlatLab daftar[]) 
{
    FILE *file = fopen("alat.txt", "r");
    if (file == NULL) 
    {
        printf("Gagal membuka file alat.txt");
        return 0;
    }

    int count = 0;

    while (fscanf(file, "%u %s %s %s %u %u %u", 
            &daftar[count].id, 
            daftar[count].nama, 
            daftar[count].merk, 
            daftar[count].model, 
            &daftar[count].tahun, 
            &daftar[count].jumlah_unit, 
            &daftar[count].jumlah_tersedia) != EOF) 
        {
            count++;
        }

        fclose(file);
        return count;
}

/*====fungsi untuk menyimpan data alat lab ke file===*/
void saveAlat(struct Alatlab daftar[], int count) 
{
    FILE *file = fopen("alat.txt", "w");
    if (file == NULL) 
    {
        printf("Gagal membuka file alat.txt untuk menulis");
        return;
    }

    for (int i = 0; i < count; i++) 
    {
        fprintf(file, "%u %s %s %s %u %u %u\n", 
                daftar[i].id, 
                daftar[i].nama, 
                daftar[i].merk, 
                daftar[i].model, 
                daftar[i].tahun, 
                daftar[i].jumlah_unit, 
                daftar[i].jumlah_tersedia);
    }

    fclose(file);

}

/*====fungsi untuk menampilkan daftar alat lab===*/
void tampilkanAlat(struct AlatLab daftar[], int count) 
{
    struct Alatlab baru;

    printf("\n== Tambah Alat Lab ==\n");
    printf("ID Alat: ");
    scanf("%u", &baru.id);

    printf("Nama Alat: ");
    scanf("%s", baru.nama);

    printf("Merk Alat: ");
    scanf("%s", baru.merk);

    printf("Model Alat: ");
    scanf("%s", baru.model);

    printf("Tahun Produksi: ");
    scanf("%u", &baru.tahun);

    printf("Jumlah Unit: ");
    scanf("%u", &baru.jumlah_unit);

    printf("Jumlah Tersedia: ");
    scanf("%u", &baru.jumlah_tersedia);

    daftar[count] = baru;
    (*count)++;

    saveAlat(daftar, *count);

    printf("Alat lab berhasil ditambahkan!\n");
}

/*====fungsi untuk mengedit data alat lab===*/
void editAlat(struct AlatLab daftar[], int count) 
{
    unsigned int id;
    printf("\nMasukkan ID Alat yang akan diedit: ");
    scanf("%u", &id);

    int index = -1;

    for (int i = 0; i < count; i++)
    {
        if (daftar[i].id == id)
        {
            index = i;
            break;
        }
    }
    
        if (index == -1)
        {
            printf("Alat dengan ID %u tidak ditemukan.\n", id);
            return;
        }

    printf("Mengedit alat: %s\n", daftar[index].nama);

    printf("Nama baru: ");
    scanf("%s", daftar[index].nama);

    printf("Merk baru: ");
    scanf("%s", daftar[index].merk);

    printf("Model baru: ");
    scanf("%s", daftar[index].model);

    printf("Tahun Produksi baru: ");
    scanf("%u", &daftar[index].tahun);

    printf("Jumlah Unit baru: ");
    scanf("%u", &daftar[index].jumlah_unit);

    printf("Jumlah Tersedia baru: ");
    scanf("%u", &daftar[index].jumlah_tersedia);

    saveAlat(daftar, count);

    printf("Alat lab berhasil diperbarui!\n");
}

/*====fungsi untuk menghapus data alat lab===*/
void hapusAlat(struct AlatLab daftar[], int *count)
{
    unsigned int id;
    printf("\nMasukkan ID Alat yang akan dihapus: ");
    scanf("%u", &id);

    int index = -1;

    for (int i = 0; i < *count; i++)
    {
        if (daftar[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Alat dengan ID %u tidak ditemukan.\n", id);
        return;
    }

    for (int i = index; i < *count - 1; i++)
    {
        daftar[i] = daftar[i + 1];
    }

    (*count)--;

    saveAlat(daftar, *count);

    printf("Alat lab berhasil dihapus!\n");
}

/*====fungsi untuk menampilkan menu admin===*/
void menuAdmin() {
    struct AlatLab daftar[100];
    int count = loadAlat(daftar);
        
    int pilihan;
        
    while(true)
    {
        printf("\n== MENU ADMIN ==\n");
        printf("1. Tampilkan Alat Lab\n");
        printf("2. Tambah Alat Lab\n");
        printf("3. Edit Alat Lab\n");
        printf("4. Hapus Alat Lab\n");
        printf("5. Logout\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch(pilihan)
        {
            case 1: tampilkanAlat(daftar, count); break;
            case 2: tambahAlat(daftar, &count); break;
            case 3: editAlat(daftar, count); break;
            case 4: hapusAlat(daftar, &count); break;
            case 5: printf("Logout berhasil.\n"); return;
            default: printf("Opsi tidak valid. Silakan coba lagi.\n");
        }
    }
}


int main (int argc, char *argv[]) {
    FILE  *file; // deklarasi pointer file
    char username[50], password[50], role[50]; // deklarasi variabel untuk username, password, dan role
    int login_success = 0; // variabel untuk menandai keberhasilan login

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
            login_success = 1; // menandai bahwa login berhasil
            break; // keluar dari loop setelah menemukan kecocokan
        }
    }

    fclose(file); // menutup file

    if (login_success) {
        printf("\nlogin sukses\n");
        printf("Halo %s! Anda memiliki akses sebagai %s. \n", username, role);
        //DI SINI BISA DITAMBAHKAN KODE YANG NANTINYA AKAN DIJALANKAN UNTUK AKSES BERDASARKAN ROLE
    } else {
        printf("Login gagal! Username atau password salah.\n");
    }

    return EXIT_SUCCESS; // mengembalikan nilai sukses
}


    
