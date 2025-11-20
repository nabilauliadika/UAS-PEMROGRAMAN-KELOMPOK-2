#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*==== Struct untuk data alat lab ===*/
struct AlatLab {
    unsigned int id;
    char nama[50];
    char merk[50];
    char model[50];
    unsigned int tahun;
    unsigned int jumlah_unit;
    unsigned int jumlah_tersedia;
};

/*==== Bersihkan buffer input ===*/
void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/*==== Load alat dari file ===*/
int loadAlat(struct AlatLab daftar[]) 
{
    FILE *file = fopen("alat.txt", "r");
    if (file == NULL) {
        return 0;
    }

    int count = 0;

    while (fscanf(file, "%u|%49[^|]|%49[^|]|%49[^|]|%u|%u|%u\n",
            &daftar[count].id,
            daftar[count].nama,
            daftar[count].merk,
            daftar[count].model,
            &daftar[count].tahun,
            &daftar[count].jumlah_unit,
            &daftar[count].jumlah_tersedia) == 7)
    {
        count++;
    }

    fclose(file);
    return count;
}

/*==== Save alat ke file  ===*/
void saveAlat(struct AlatLab daftar[], int count) 
{
    FILE *file = fopen("alat.txt", "w");
    if (!file) {
        printf("Gagal membuka file alat.txt\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%u|%s|%s|%s|%u|%u|%u\n",
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

/*==== Tampilkan alat ===*/
void tampilkanAlat(struct AlatLab daftar[], int count)
{
    printf("\n== DAFTAR ALAT LAB ==\n");

    if (count == 0) {
        printf("Belum ada data alat.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
         printf(" ID      : %u \n Nama    : %s \n Merk    : %s \n Model   : %s \n Tahun   : %u \n Unit    : %u \n Tersedia: %u\n",
            daftar[i].id,
            daftar[i].nama,
            daftar[i].merk,
            daftar[i].model,
            daftar[i].tahun,
            daftar[i].jumlah_unit,
            daftar[i].jumlah_tersedia);
    print("\n");
    }
}

/*==== Tambah alat ===*/
void tambahAlat(struct AlatLab daftar[], int *count)
{
    struct AlatLab baru;

    printf("\n== Tambah Alat ==\n");

    printf("ID Alat: ");
    scanf("%u", &baru.id);
    clearInput();

    printf("Nama Alat: ");
    fgets(baru.nama, 50, stdin);
    baru.nama[strcspn(baru.nama, "\n")] = '\0';

    printf("Merk Alat: ");
    fgets(baru.merk, 50, stdin);
    baru.merk[strcspn(baru.merk, "\n")] = '\0';

    printf("Model Alat: ");
    fgets(baru.model, 50, stdin);
    baru.model[strcspn(baru.model, "\n")] = '\0';

    printf("Tahun Produksi: ");
    scanf("%u", &baru.tahun);
    clearInput();

    printf("Jumlah Unit: ");
    scanf("%u", &baru.jumlah_unit);
    clearInput();

    printf("Jumlah Tersedia: ");
    scanf("%u", &baru.jumlah_tersedia);
    clearInput();

    daftar[*count] = baru;
    (*count)++;

    saveAlat(daftar, *count);

    printf("Alat berhasil ditambahkan!\n");
}

/*==== Edit alat ===*/
void editAlat(struct AlatLab daftar[], int count)
{
    unsigned int id;
    printf("Masukkan ID alat yang akan diedit: ");
    scanf("%u", &id);
    clearInput();

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (daftar[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Alat tidak ditemukan.\n");
        return;
    }

    printf("Nama baru: ");
    fgets(daftar[index].nama, 50, stdin);
    daftar[index].nama[strcspn(daftar[index].nama, "\n")] = '\0';

    printf("Merk baru: ");
    fgets(daftar[index].merk, 50, stdin);
    daftar[index].merk[strcspn(daftar[index].merk, "\n")] = '\0';

    printf("Model baru: ");
    fgets(daftar[index].model, 50, stdin);
    daftar[index].model[strcspn(daftar[index].model, "\n")] = '\0';

    printf("Tahun Produksi baru: ");
    scanf("%u", &daftar[index].tahun);
    clearInput();

    printf("Jumlah Unit baru: ");
    scanf("%u", &daftar[index].jumlah_unit);
    clearInput();

    printf("Jumlah Tersedia baru: ");
    scanf("%u", &daftar[index].jumlah_tersedia);
    clearInput();

    saveAlat(daftar, count);

    printf("Alat berhasil diperbarui!\n");
}

/*==== Hapus alat ===*/
void hapusAlat(struct AlatLab daftar[], int *count)
{
    unsigned int id;
    printf("Masukkan ID alat yang akan dihapus: ");
    scanf("%u", &id);
    clearInput();

    int index = -1;
    for (int i = 0; i < *count; i++) {
        if (daftar[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Alat tidak ditemukan.\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        daftar[i] = daftar[i + 1];
    }

    (*count)--;

    saveAlat(daftar, *count);

    printf("Alat berhasil dihapus!\n");
}

/*==== Menu admin ===*/
void menuAdmin() 
{
    struct AlatLab daftar[100];
    int count = loadAlat(daftar);

    int pilihan;

    while (true) {
        printf("\n== MENU ADMIN ==\n");
        printf("1. Tampilkan Alat\n");
        printf("2. Tambah Alat\n");
        printf("3. Edit Alat\n");
        printf("4. Hapus Alat\n");
        printf("5. Logout\n\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);
        clearInput();

        switch (pilihan) {
            case 1: tampilkanAlat(daftar, count); break;
            case 2: tambahAlat(daftar, &count); break;
            case 3: editAlat(daftar, count); break;
            case 4: hapusAlat(daftar, &count); break;
            case 5: return;
            default: printf("Pilihan tidak valid.\n");
        }
    }
}



