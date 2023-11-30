#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

void print_hex(const char *prefix, const unsigned char *data, size_t len) {
    printf("%s: ", prefix);
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void encrypt_decrypt_des(const char *input, const char *key, const char *iv, int mode) {
    DES_cblock des_key;
    DES_key_schedule key_schedule;

    // Set the DES key
    memcpy(des_key, key, 8);
    DES_set_key(&des_key, &key_schedule);

    // Initialize the IV for CBC and CFB modes
    DES_cblock des_iv;
    memcpy(des_iv, iv, 8);

    size_t input_len = strlen(input);
    size_t padded_len = ((input_len + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    char *padded_input = malloc(padded_len);
    memcpy(padded_input, input, input_len);

    // Pad the input if needed
    if (input_len % BLOCK_SIZE != 0) {
        padded_input[input_len] = 0x80; // Padding starts with 1
        memset(padded_input + input_len + 1, 0, padded_len - input_len - 1);
    }

    char *output = malloc(padded_len);

    DES_cblock ivec;
    memset(ivec, 0, sizeof(ivec)); // Initialization vector for CFB mode

    if (mode == DES_ENCRYPT) {
        for (size_t i = 0; i < padded_len; i += BLOCK_SIZE) {
            if (mode == DES_CBC_MODE || mode == DES_CFB_MODE) {
                DES_cblock_xor((DES_cblock *)(padded_input + i), &ivec, (DES_cblock *)(padded_input + i));
            }

            DES_ecb_encrypt((DES_cblock *)(padded_input + i), (DES_cblock *)(output + i), &key_schedule, mode);

            if (mode == DES_CBC_MODE || mode == DES_CFB_MODE) {
                memcpy(ivec, output + i, BLOCK_SIZE);
            }
        }
    } else if (mode == DES_DECRYPT) {
        for (size_t i = 0; i < padded_len; i += BLOCK_SIZE) {
            DES_ecb_encrypt((DES_cblock *)(padded_input + i), (DES_cblock *)(output + i), &key_schedule, mode);

            if (mode == DES_CBC_MODE || mode == DES_CFB_MODE) {
                DES_cblock_xor((DES_cblock *)(output + i), &ivec, (DES_cblock *)(output + i));
                memcpy(ivec, padded_input + i, BLOCK_SIZE);
            }
        }
    }

    print_hex("Input", (const unsigned char *)padded_input, padded_len);
    print_hex("Output", (const unsigned char *)output, padded_len);

    free(padded_input);
    free(output);
}

int main() {
    const char *input = "Hello123";
    const char *key = "0123456789abcdef"; // 8 bytes for DES
    const char *iv = "12345678"; // 8 bytes for DES

    printf("ECB Encryption/Decryption:\n");
    encrypt_decrypt_des(input, key, iv, DES_ENCRYPT);
    encrypt_decrypt_des(input, key, iv, DES_DECRYPT);

    printf("\nCBC Encryption/Decryption:\n");
    encrypt_decrypt_des(input, key, iv, DES_ENCRYPT | DES_CBC_MODE);
    encrypt_decrypt_des(input, key, iv, DES_DECRYPT | DES_CBC_MODE);

    printf("\nCFB Encryption/Decryption:\n");
    encrypt_decrypt_des(input, key, iv, DES_ENCRYPT | DES_CFB_MODE);
    encrypt_decrypt_des(input, key, iv, DES_DECRYPT | DES_CFB_MODE);

    return 0;
}
