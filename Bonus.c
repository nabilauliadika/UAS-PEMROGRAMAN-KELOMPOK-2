#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN   100
#define HASH_SIZE 10007   // prime for hashing

// Simple hash table: setiap slot menyimpan satu kata (string)
char hashTable[HASH_SIZE][MAX_LEN] = {0};

// djb2 hash function
unsigned int hashFunc(const char *s) {
    unsigned long h = 5381;
    int c;
    while ((c = *s++)) h = ((h << 5) + h) + c; // h = h*33 + c
    return h % HASH_SIZE;
}

// cek apakah kata sudah ada di slot hasil hash
int wordExists(const char *w) {
    unsigned int idx = hashFunc(w);
    return strcmp(hashTable[idx], w) == 0; // true jika sama
    // NOTE: collision handling belum diimplementasikan (bisa overwrite)
}

// simpan kata ke slot hash
void saveWord(const char *w) {
    unsigned int idx = hashFunc(w);
    strcpy(hashTable[idx], w); // tulis kata ke tabel
}

// valid jika huruf/angka atau apostrof
int isValidChar(char c) {
    return isalnum((unsigned char)c) || c == '\'';
}

// ganti UTF-8 right single quote (0xE2 0x80 0x99) jadi ASCII apostrophe '
void normalizeApostrophe(char *s) {
    char *p;
    while ((p = strstr(s, "\xE2\x80\x99"))) {
        *p = '\''; // taruh apostrof di byte pertama
        memmove(p + 1, p + 3, strlen(p + 3) + 1); // hapus dua byte sisanya dari sequence
    }
}

// buang apostrof di awal/akhir kata (tapi pertahankan jika hanya satu char)
void cleanApostrophe(char *s) {
    int len = strlen(s);
    while (s[0] == '\'' && len > 1) { memmove(s, s + 1, len); len--; }
    while (len > 1 && s[len - 1] == '\'') { s[--len] = '\0'; }
}

int main() {
    FILE *in = fopen("lirik.txt", "r");           // file input
    FILE *out = fopen("kosa-kata.word", "w");     // file output

    if (!in || !out) {                            // cek file
        printf("Gagal membuka file.\n");
        return 1;
    }

    char line[1000];
    int firstLine = 1;

    while (fgets(line, sizeof(line), in)) {       // baca baris demi baris
        normalizeApostrophe(line);                // normalisasi tanda kutip miring

        if (firstLine) {                          // baris pertama langsung ditulis (header)
            fprintf(out, "%s", line);
            firstLine = 0;
            continue;                             // skip parsing kata untuk baris ini
        }

        int i = 0, idx = 0;
        char temp[MAX_LEN];

        while (1) {
            char c = line[i];

            if (isValidChar(c)) {                 // jika karakter bagian kata
                if (idx < MAX_LEN - 1)
                    temp[idx++] = c;              // simpan ke buffer temp
            } else {
                if (idx > 0) {                    // akhir kata terdeteksi
                    temp[idx] = '\0';             // akhiri string
                    idx = 0;                      // reset untuk kata berikutnya

                    cleanApostrophe(temp);        // hapus apostrof pinggir
                    // ke-lowercase-an agar perbandingan case-insensitive
                    for (int k = 0; temp[k]; k++)
                        temp[k] = tolower((unsigned char)temp[k]);

                    if (!wordExists(temp))        // cek unik
                        saveWord(temp);           // simpan jika baru
                }
            }

            if (c == '\0')                         // akhir baris
                break;
            i++;
        }
    }

    // tulis semua kata unik yang ada di hashTable ke file output
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable[i][0]) {
            fprintf(out, "%s=\n", hashTable[i]);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
