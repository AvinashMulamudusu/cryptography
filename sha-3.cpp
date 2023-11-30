#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void cbc_mac(unsigned char K[], unsigned char X[], unsigned char T[]) {
    int block_size = 16;
    for (int i = 0; i < block_size; i++) {
        X[i] ^= T[i];  
    }
    for (int i = 0; i < block_size; i++) {
        T[i] = X[i];
    }
}

int main() {
    unsigned char K[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    unsigned char X[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    unsigned char T[16];
    memcpy(T, K, 16); 
    cbc_mac(K, X, T);
    printf("MAC(K, X): ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", T[i]);
    }
    printf("\n");
    unsigned char X_concat[32];
    memcpy(X_concat, X, 16); 
    for (int i = 0; i < 16; i++) {
        X_concat[16 + i] = X[i] ^ T[i]; 
    }
    unsigned char T_concat[16];
    memcpy(T_concat, K, 16);
    cbc_mac(K, X_concat, T_concat);
    printf("MAC(K, X || (X ? T)): ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", T_concat[i]);
    }
    printf("\n");

    return 0;
}
