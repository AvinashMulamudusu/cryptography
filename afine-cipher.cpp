#include <stdio.h>
#include <ctype.h>

int modInverse(int a, int m);
void findKey(int c1, int c2, int p1, int p2, int a, int b);
void decrypt(int a, int b, char ciphertext, char plaintext);

int main() {
    char ciphertext[1000] = "UBUUBBUBUUBBUUBUUBUUUBUUBBUUBUUBBUUBUUUBBUUBUUBBUUBUUBBUUBUUBBUUBUUBBUUBBUUBUUBBUUBUUBBUUBUUBBUUBUUBBUUB";
    char plaintext[1000];
    int freq[26] = {0};
    int i, j, c1, c2, p1, p2, a, b;

    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            freq[tolower(ciphertext[i]) - 'a']++;
        }
    }

    c1 = c2 = -1;
    p1 = p2 = -1;
    for (i = 0; i < 26; i++) {
        if (freq[i] > c1) {
            c2 = c1;
            p2 = p1;
            c1 = freq[i];
            p1 = i;
        } else if (freq[i] > c2) {
            c2 = freq[i];
            p2 = i;
        }
    }

    // find the key
    findKey(p1, p2, 'e' - 'a', 't' - 'a', &a, &b);

    // decrypt the ciphertext
    decrypt(a, b, ciphertext, plaintext);

    printf("Plaintext: %s\n", plaintext);

    return 0;
}
