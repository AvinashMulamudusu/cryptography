#include <stdio.h>
#include <string.h>

#define ROWS 5
#define COLS 5

void createPlayfairMatrix(char key[], char matrix[ROWS][COLS]);

int main() {
    char key[] = "MFHIKUNOPQZVWXYELARBDSBTC";
    char matrix[ROWS][COLS];
    createPlayfairMatrix(key, matrix);
    printf("Playfair matrix:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void createPlayfairMatrix(char key[], char matrix[ROWS][COLS]) {
    int i, j, k;
    int keylen = strlen(key);
    int is_present[26] = {0};

    // fill matrix with key
    k = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (k < keylen) {
                if (key[k] == 'J') { // replace J with I
                    matrix[i][j] = 'I';
                } else {
                    matrix[i][j] = key[k];
                }
                is_present[key[k] - 'A'] = 1;
                k++;
            }
        }
    }

    // fill matrix with remaining letters
    char ch = 'A';
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (matrix[i][j] == '\0') {
                while (is_present[ch - 'A']) {
                    ch++;
                }
                if (ch == 'J') { // replace J with I
                    ch++;
                }
                matrix[i][j] = ch;
                is_present[ch - 'A'] = 1;
            }
        }
    }
}
