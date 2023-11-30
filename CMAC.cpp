#include <stdio.h>
#include <stdint.h>

// Block size in bytes
#define BLOCK_SIZE 8 // For 64-bit block size
// #define BLOCK_SIZE 16 // For 128-bit block size

// Function to perform left shift on a byte array
void leftShift(uint8_t *input, int len) {
    uint8_t carry = 0;
    for (int i = 0; i < len; i++) {
        uint8_t nextCarry = input[i] >> 7;
        input[i] = (input[i] << 1) | carry;
        carry = nextCarry;
    }
}

int main() {
    uint8_t zeroBlock[BLOCK_SIZE] = {0}; // All-zero block

    // First subkey generation
    // Apply block cipher to zeroBlock
    // Here, we are simulating the block cipher operation with a simple print statement
    printf("Block cipher operation on zeroBlock\n");

    // Left shift and XOR constants
    uint8_t constRb = 0x87; // Constant for 128-bit block size (Rb = 0x87)
    // uint8_t constRb = 0x1B; // Constant for 64-bit block size (Rb = 0x1B)

    // Left shift the result of the block cipher operation
    leftShift(zeroBlock, BLOCK_SIZE);

    // If MSB of zeroBlock is 0, no XOR is needed, else XOR with constRb
    if (zeroBlock[0] & 0x80) {
        zeroBlock[BLOCK_SIZE - 1] ^= constRb;
    }

    // Print the first subkey
    printf("First Subkey: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", zeroBlock[i]);
    }
    printf("\n");

    // Second subkey generation
    leftShift(zeroBlock, BLOCK_SIZE);
    if (zeroBlock[0] & 0x80) {
        zeroBlock[BLOCK_SIZE - 1] ^= constRb;
    }

    // Print the second subkey
    printf("Second Subkey: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", zeroBlock[i]);
    }
    printf("\n");

    return 0;
}
