#include <stdio.h>
#include <string.h>

// ECB Mode Encryption Function
void encrypt_ecb(const unsigned char* plaintext, const unsigned char* key, int block_size) {

    for (int i = 0; i < block_size; i++) {
        printf("%02X ", plaintext[i] ^ key[i]);
    }
    printf("\n");
}

// CBC Mode Encryption FunctionQ
void encrypt_cbc(const unsigned char* plaintext, const unsigned char* key, const unsigned char* iv, int block_size) {
    unsigned char previous_ciphertext[block_size];
    memcpy(previous_ciphertext, iv, block_size);

    for (int i = 0; i < block_size; i++) {
        unsigned char encrypted_block = plaintext[i] ^ previous_ciphertext[i] ^ key[i];
        printf("%02X ", encrypted_block);
        previous_ciphertext[i] = encrypted_block;
    }
    printf("\n");
}

int main() {
    const unsigned char key[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    const unsigned char iv[] = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    const int block_size = 8; // 64 bits or 8 bytes block size

    // Example plaintext blocks (P1, P2, P3) for demonstration
    const unsigned char plaintext1[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    const unsigned char plaintext2[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    const unsigned char plaintext3[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11};

    printf("ECB Mode:\n");
    printf("C1: ");
    encrypt_ecb(plaintext1, key, block_size);

    printf("C2: ");
    encrypt_ecb(plaintext2, key, block_size);

    printf("C3: ");
    encrypt_ecb(plaintext3, key, block_size);

    printf("\nCBC Mode:\n");
    printf("C1: ");
    encrypt_cbc(plaintext1, key, iv, block_size);

    printf("C2: ");
    encrypt_cbc(plaintext2, key, iv, block_size);

    printf("C3: ");
    encrypt_cbc(plaintext3, key, iv, block_size);

    return 0;
}
