#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plaintext[] = "This is a secret message.";
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    char ciphertext[100];
    int i;


    for (i = 0; plaintext[i]; i++) {
        plaintext[i] = toupper(plaintext[i]);
    }

    for (i = 0; plaintext[i]; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = key[plaintext[i] - 'A'];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';

    printf("Plaintext: %s\n", plaintext);
    printf("Key: %s\n", key);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
