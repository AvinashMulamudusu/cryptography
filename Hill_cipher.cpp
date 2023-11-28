#include <stdio.h>
#include <string.h>

#define MOD 26

void matrixMultiplication(int key[][2], int message[], int result[], int length) {
    int i, j;
    for (i = 0; i < length; i += 2) {
        int sum1 = 0, sum2 = 0;
        for (j = 0; j < 2; j++) {
            sum1 += key[j][0] * message[i+j];
            sum2 += key[j][1] * message[i+j];
        }
        result[i] = sum1 % MOD;
        result[i+1] = sum2 % MOD;
    }
}

void hillCipher(char message[], int key[][2]) {
    int length = strlen(message);
    int i, j;
    int messageArray[length];
    for (i = 0; i < length; i++) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            messageArray[i] = message[i] - 'a';
        } else {
            messageArray[i] = 23; // 'x' -> 23
        }
    }
    if (length % 2 != 0) {
        messageArray[length] = 23;
        length++;
    }
    int result[length];
    matrixMultiplication(key, messageArray, result, length);
    for (i = 0; i < length; i++) {
        if (result[i] == 23) {
            printf("x");
        } else {
            printf("%c", result[i] + 'a');
        }
    }
}

int main() {
    int key[2][2] = {{9, 4}, {5, 7}};
    char message[] = "meet me at the usual place at ten rather than eight oclock";
    hillCipher(message, key);
    printf("\n");
    return 0;
}
