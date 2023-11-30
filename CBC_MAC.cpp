#include <stdio.h>
#include <string.h>

// Example key (16 bytes)
unsigned char key[16] = {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x97, 0x46, 0x19, 0xa4, 0x62, 0x55
};

// XOR operation for two blocks of data
void xorBlocks(unsigned char *dest, const unsigned char *src1, const unsigned char *src2, int blockSize) {
    for (int i = 0; i < blockSize; i++) {
        dest[i] = src1[i] ^ src2[i];
    }
}

// AES encryption (dummy function)
void aesEncrypt(unsigned char *output, const unsigned char *input, const unsigned char *key, int blockSize) {
    // This is where actual AES encryption should be performed.
    // For simplicity, this function is a dummy and does nothing.
    memcpy(output, input, blockSize);
}

// CBC-MAC calculation
void cbcMac(unsigned char *mac, const unsigned char *message, int blockSize) {
    unsigned char iv[blockSize];  // Initialization vector
    unsigned char tmp[blockSize]; // Temporary storage for XOR result

    memset(iv, 0, blockSize); // Initialize IV to zeros

    // Encrypt the message using CBC mode with a dummy encryption function (AES)
    for (int i = 0; i < blockSize; i++) {
        tmp[i] = message[i] ^ iv[i];
    }

    aesEncrypt(mac, tmp, key, blockSize);
}

int main() {
    int blockSize = 16; // Block size in bytes

    unsigned char X[blockSize] = {
        0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20,
        0x61, 0x20, 0x74, 0x65, 0x73, 0x74, 0x20, 0x58
    }; // One-block message

    unsigned char T[blockSize];
    cbcMac(T, X, blockSize); // Calculate CBC-MAC for X

    unsigned char X_Xor_T[blockSize * 2];
    xorBlocks(X_Xor_T, X, T, blockSize); // X ? T

    unsigned char T_2[blockSize];
    cbcMac(T_2, X_Xor_T, blockSize * 2); // Calculate CBC-MAC for X || (X ? T)

    printf("CBC-MAC for X: ");
    for (int i = 0; i < blockSize; i++) {
        printf("%02x ", T[i]);
    }
    printf("\n");

    printf("CBC-MAC for X || (X ? T): ");
    for (int i = 0; i < blockSize; i++) {
        printf("%02x ", T_2[i]);
    }
    printf("\n");

    return 0;
}
