#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    char plaintext[1000], ciphertext[1000], key[1000];
    int i, j, k, len_plaintext, len_key;
    
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    len_plaintext = strlen(plaintext);
    
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    len_key = strlen(key);
    
    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';
    
    for (i = 0; i < len_plaintext; i++) {
        plaintext[i] = toupper(plaintext[i]);
    }
    
    j = 0;
    k = 0; 
    for (i = 0; i < len_plaintext; i++) {
        if (isalpha(plaintext[i])) {
            k = key[j] - 'A';
            
            ciphertext[i] = (plaintext[i] + k - 'A') % 26 + 'A';
            
            j = (j + 1) % len_key;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len_plaintext] = '\0';
    
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}

