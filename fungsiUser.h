#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*====struct untuk data alat lab===*/
struct Peminjaman {
	char username[50]; 
	unsigned int id_alat; 
};

/*====fungsi untuk load data peminjaman dari file===*/
int loadPeminjaman(struct Peminjaman list[])
{
	FILE *file = fopen("peminjaman.txt", "r"); 
	if (file == NULL) { 
		return 0; 
	}

	int count = 0;
	while (fscanf(file, "%49s %u", list[count].username, &list[count].id_alat) != EOF) {
		count++; 
	}

	fclose(file); 
	return count; 
}

/*====fungsi untuk menyimpan data peminjaman ke file===*/
void savePeminjaman(struct Peminjaman list[], int count)
{
	FILE *file = fopen("peminjaman.txt", "w"); 
	if (file == NULL) { 
		printf("Gagal membuka file peminjaman.txt untuk menulis\n");
		return; 
	}

	for (int i = 0; i < count; i++) {
		fprintf(file, "%s %u\n", list[i].username, list[i].id_alat);
	}

	fclose(file);
}

/*====fungsi untuk menambahkan data peminjaman baru ke file===*/
void appendPeminjaman(const char *username, unsigned int id_alat)
{
	FILE *file = fopen("peminjaman.txt", "a"); 
	if (file == NULL) { 
		printf("Gagal membuka file peminjaman.txt untuk append\n");
		return; 
	}

	fprintf(file, "%s %u\n", username, id_alat); 
	fclose(file); 
}

/*====fungsi untuk meminjam alat===*/
void pinjamAlat(const char *username, struct AlatLab daftar[], int *count)
{
	unsigned int id; 
	printf("\n== PINJAM ALAT ==\n"); 
	tampilkanAlat(daftar, *count); 

	printf("Masukkan ID alat yang ingin dipinjam: "); 
	scanf("%u", &id); 

	int index = -1; 
	for (int i = 0; i < *count; i++) {
		if (daftar[i].id == id) {
			index = i; 
			break; 
		}
	}

	if (index == -1) { 
		printf("Alat dengan ID %u tidak ditemukan.\n", id);
		return; 
	}

	if (daftar[index].jumlah_tersedia == 0) { 
		printf("Maaf, alat %s sedang tidak tersedia.\n", daftar[index].nama);
		return; 
	}

	daftar[index].jumlah_tersedia--;
	saveAlat(daftar, *count); 
	appendPeminjaman(username, id); 
	printf("Peminjaman berhasil: %s meminjam alat ID %u\n", username, id);
}

/*====fungsi untuk menampilkan alat yang dipinjam oleh user===*/
void tampilkanPeminjaman(const char *username)
{
	struct Peminjaman list[100]; 
	int count = loadPeminjaman(list); 

	printf("\n== DAFTAR PEMINJAMAN %s ==\n", username); 

	int found = 0; 
	for (int i = 0; i < count; i++) { 
		if (strcmp(list[i].username, username) == 0) { 
			printf("ID Alat: %u\n", list[i].id_alat); 
			found = 1; 
		}
	}

	if (!found) { 
		printf("Tidak ada alat yang dipinjam oleh %s.\n", username);
	}
}

/*====fungsi untuk mengembalikan alat===*/
void kembalikanAlat(const char *username, struct AlatLab daftar[], int *count)
{
	unsigned int id; 
	printf("\n== KEMBALIKAN ALAT ==\n"); 
	tampilkanPeminjaman(username); 
	printf("Masukkan ID alat yang dikembalikan: "); 
	scanf("%u", &id);

	
	struct Peminjaman list[100]; 
	int countP = loadPeminjaman(list); 

	int found = -1; 
	for (int i = 0; i < countP; i++) { 
		if (strcmp(list[i].username, username) == 0 && list[i].id_alat == id) {
			found = i; 
			break; 
		}
	}

	if (found == -1) { 
		printf("Tidak ditemukan peminjaman dengan ID %u untuk %s.\n", id, username);
		return; 
	}

	
	for (int i = found; i < countP - 1; i++) {
		list[i] = list[i + 1]; 
	}
	countP--; 
	savePeminjaman(list, countP); 

	
	int idxAlat = -1; 
	for (int i = 0; i < *count; i++) { 
		if (daftar[i].id == id) {
			idxAlat = i; 
			break; 
		}
	}

	if (idxAlat != -1) { 
		daftar[idxAlat].jumlah_tersedia++; 
		saveAlat(daftar, *count); 
	}

	printf("Pengembalian berhasil: %s mengembalikan alat ID %u\n", username, id); 
}

/*====fungsi untuk menampilkan menu user===*/
void menuUser(const char *username)
{
	struct AlatLab daftar[100]; 
	int count = loadAlat(daftar); 

	int pilihan; 

	while (true) { 
		printf("\n== MENU USER ==\n");
		printf("1. Tampilkan Alat Lab\n"); 
		printf("2. Pinjam Alat\n"); 
		printf("3. Tampilkan Alat yang Dipinjam\n"); 
		printf("4. Kembalikan Alat\n"); 
		printf("5. Logout\n"); 
		printf("Pilih opsi: "); 
		scanf("%d", &pilihan); 

		switch (pilihan) { 
			case 1: tampilkanAlat(daftar, count); break;
			case 2: pinjamAlat(username, daftar, &count); break; 
			case 3: tampilkanPeminjaman(username); break; 
			case 4: kembalikanAlat(username, daftar, &count); break; 
			case 5: printf("Logout berhasil.\n"); return; 
			default: printf("Opsi tidak valid. Silakan coba lagi.\n");
		}
	}
}



