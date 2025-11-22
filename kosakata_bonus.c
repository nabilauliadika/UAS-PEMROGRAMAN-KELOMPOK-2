#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Program ini tugasnya membaca lirik dari file
// lalu ngambil semua kata unik, dijadiin huruf kecil,
// dibersihin dari tanda baca, dan ditulis ke file lain.

#define MAX_WORDS 5000
#define MAX_LEN   100

// Fungsi cek apakah karakter itu bagian dari kata
// (huruf, angka, atau apostrof untuk kata seperti weren't)
int isValidChar(char c) {
    return isalnum((unsigned char)c) || c == '\'';
}

// Bersihin apostrof aneh (’) jadi apostrof biasa (')
void normalizeApostrophe(char *s) {
    for (int i = 0; s[i]; i++) {
        // kalau ketemu karakter apostrof versi UTF-8
        if ((unsigned char)s[i] == 0xE2 &&
            (unsigned char)s[i+1] == 0x80 &&
            (unsigned char)s[i+2] == 0x99) {
            s[i] = '\''; // ganti jadi '
            // geser sisanya
            memmove(&s[i+1], &s[i+3], strlen(&s[i+3]) + 1);
        }
    }
}

// Menghilangkan apostrof di depan atau belakang kata
void cleanApostrophe(char *s) {
    int len = strlen(s);

    // buang apostrof depan
    while (s[0] == '\'' && len > 1) {
        memmove(s, s + 1, len);
        len--;
    }

    // buang apostrof belakang
    while (len > 1 && s[len - 1] == '\'') {
        s[--len] = '\0';
    }
}

int main() {
    FILE *in = fopen("lirik.txt", "r");
    FILE *out = fopen("kosa-kata.word", "w");

    // Kalau file nggak kebuka, lapor error
    if (!in || !out) {
        printf("Gagal membuka file. Pastikan lirik.txt ada.\n");
        return 1;
    }

    char line[1000];
    char words[MAX_WORDS][MAX_LEN]; // tempat nyimpen kata unik
    int wordCount = 0;
    int firstLine = 1; // baris judul

    while (fgets(line, sizeof(line), in)) {
        normalizeApostrophe(line);

        // Baris pertama (judul) dicetak langsung
        if (firstLine) {
            fprintf(out, "%s", line);
            firstLine = 0;
            continue;
        }

        int i = 0, idx = 0;
        char temp[MAX_LEN];

        // Ambil kata satu-satu
        while (1) {
            char c = line[i];

            if (isValidChar(c)) {
                // Masukkan karakter ke kata sementara
                if (idx < MAX_LEN - 1)
                    temp[idx++] = c;
            } else {
                // Kalau ketemu pemisah kata
                if (idx > 0) {
                    temp[idx] = '\0';   // selesai satu kata
                    idx = 0;

                    cleanApostrophe(temp); // bersihkan ujung kata

                    // ubah jadi huruf kecil semua
                    for (int k = 0; temp[k]; k++)
                        temp[k] = tolower(temp[k]);

                    // cek apakah kata sudah pernah disimpan
                    int exists = 0;
                    for (int w = 0; w < wordCount; w++) {
                        if (strcmp(words[w], temp) == 0) {
                            exists = 1;
                            break;
                        }
                    }

                    // kalau kata baru, simpan
                    if (!exists && wordCount < MAX_WORDS) {
                        strcpy(words[wordCount++], temp);
                    }
                }
            }

            if (c == '\0')
                break;
            i++;
        }
    }

    // Tulis semua kata unik ke file output
    for (int i = 0; i < wordCount; i++) {
        fprintf(out, "%s=\n", words[i]);
    }

    fclose(in);
    fclose(out);
    return 0;
}
