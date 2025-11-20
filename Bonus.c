#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 5000
#define MAX_LEN 100

int isValidChar(char c) {
    return isalnum(c) || c == '\'';
}

void normalizeApostrophe(char *line) {
    int i;
    for (i = 0; line[i]; i++) {
        // ganti typographic apostrophe ’ menjadi '
        if (line[i] == '\xE2' && line[i+1] == '\x80' && line[i+2] == '\x99') {
            line[i] = '\'';
            memmove(&line[i+1], &line[i+3], strlen(&line[i+3]) + 1);
        }
    }
}

void toLowerStr(char *s) {
    int i;
    for (i = 0; s[i]; i++)
        s[i] = tolower((unsigned char)s[i]);
}

int exists(char arr[][MAX_LEN], int count, const char *w) {
    int i;
    for (i = 0; i < count; i++)
        if (strcmp(arr[i], w) == 0)
            return 1;
    return 0;
}

int main() {
    FILE *in = fopen("lirik.txt", "r");
    FILE *out = fopen("kosa-kata.word", "w");

    char line[1000];
    char words[MAX_WORDS][MAX_LEN];
    int wc = 0;
    int firstLine = 1;

    if (!in || !out) {
        printf("Gagal membuka file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), in)) {

        normalizeApostrophe(line); // FIX penting!

        if (firstLine) {
            fprintf(out, "%s", line);
            firstLine = 0;
            continue;
        }

        int len = strlen(line), i, idx = 0;
        char temp[MAX_LEN];

        for (i = 0; i <= len; i++) {

            if (isValidChar(line[i])) {
                temp[idx++] = line[i];
            } else {
                if (idx > 0) {
                    temp[idx] = '\0';
                    idx = 0;

                    // hapus apostrof di awal/akhir kata jika ada
                    while (temp[0] == '\'' && strlen(temp) > 1)
                        memmove(temp, temp + 1, strlen(temp));

                    while (temp[strlen(temp) - 1] == '\'' && strlen(temp) > 1)
                        temp[strlen(temp) - 1] = '\0';

                    toLowerStr(temp);

                    if (!exists(words, wc, temp))
                        strcpy(words[wc++], temp);
                }
            }
        }
    }

    int i;
    for (i = 0; i < wc; i++)
        fprintf(out, "%s=\n", words[i]);

    fclose(in);
    fclose(out);

    return 0;
}
