//nabil & raymond menjelaskan, kita menyimak.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 5000
#define MAX_LEN   100
#define HASH_SIZE 10007   // prime number for hashing

// Hash table untuk deteksi kata unik (lebih cepat dari linear search)
char hashTable[HASH_SIZE][MAX_LEN] = {0};

unsigned int hashFunc(const char *s) {
    unsigned long h = 5381;
    int c;
    while ((c = *s++)) h = ((h << 5) + h) + c;
    return h % HASH_SIZE;
}

int wordExists(const char *w) {
    unsigned int idx = hashFunc(w);
    return strcmp(hashTable[idx], w) == 0;
}

void saveWord(const char *w) {
    unsigned int idx = hashFunc(w);
    strcpy(hashTable[idx], w);
}

int isValidChar(char c) {
    return isalnum((unsigned char)c) || c == '\'';
}

void normalizeApostrophe(char *s) {
    char *p;
    while ((p = strstr(s, "\xE2\x80\x99"))) {
        *p = '\'';
        memmove(p + 1, p + 3, strlen(p + 3) + 1);
    }
}

void cleanApostrophe(char *s) {
    int len = strlen(s);

    // remove leading '
    while (s[0] == '\'' && len > 1) {
        memmove(s, s + 1, len);
        len--;
    }

    // remove trailing '
    while (len > 1 && s[len - 1] == '\'') {
        s[--len] = '\0';
    }
}

int main() {
    FILE *in = fopen("lirik.txt", "r");
    FILE *out = fopen("kosa-kata.word", "w");

    if (!in || !out) {
        printf("Gagal membuka file.\n");
        return 1;
    }

    char line[1000];
    int firstLine = 1;

    while (fgets(line, sizeof(line), in)) {

        normalizeApostrophe(line);

        // baris pertama langsung dicetak
        if (firstLine) {
            fprintf(out, "%s", line);
            firstLine = 0;
            continue;
        }

        int i = 0, idx = 0;
        char temp[MAX_LEN];

        while (1) {
            char c = line[i];

            if (isValidChar(c)) {
                if (idx < MAX_LEN - 1)
                    temp[idx++] = c;
            } else {
                if (idx > 0) {
                    temp[idx] = '\0';
                    idx = 0;

                    cleanApostrophe(temp);

                    for (int k = 0; temp[k]; k++)
                        temp[k] = tolower((unsigned char)temp[k]);

                    if (!wordExists(temp))
                        saveWord(temp);
                }
            }

            if (c == '\0')
                break;
            i++;
        }
    }

    // Output semua kata unik
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable[i][0]) {
            fprintf(out, "%s=\n", hashTable[i]);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
