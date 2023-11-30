#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h> 
#define MESSAGE "Hello, DSA!"
void handleErrors(void) {
    fprintf(stderr, "Error occurred.\n");
    exit(EXIT_FAILURE);
}
DSA* generateDSAKeyPair(void) {
    DSA *dsa = NULL;
    if ((dsa = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL)) == NULL) {
        handleErrors();
    }
    if (!DSA_generate_key(dsa)) {
        handleErrors();
    }
    return dsa;
}
void signAndVerifyMessage(DSA *dsa, const char *message) {
    int sig_len;
    unsigned char sig[DSA_size(dsa)];
    printf("Message: %s\n", message);
    if (DSA_sign(0, (const unsigned char *)message, strlen(message), sig, &sig_len, dsa) != 1) {
        handleErrors();
    }
    printf("Signature generated.\n");
    if (DSA_verify(0, (const unsigned char *)message, strlen(message), sig, sig_len, dsa) != 1) {
        printf("Signature verification failed.\n");
    } else {
        printf("Signature verified successfully.\n");
    }
}
int main(void) {
    DSA *dsa = generateDSAKeyPair();
    char userMessage[256];
    printf("Enter a message to sign: ");
    fgets(userMessage, sizeof(userMessage), stdin);
    userMessage[strcspn(userMessage, "\n")] = '\0';
    signAndVerifyMessage(dsa, userMessage);
    DSA_free(dsa);
    return 0;
}
