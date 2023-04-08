#include  <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include <ctype.h>
#include <math.h>

int main() {

    void Neg(char* n) {
        int len = strlen(n);
        int j;
        for (j = 0; j < len; ++j) {
            if (n[j] == '1') {
                n[j] = '0';
            }
            else n[j] = '1';
        }
    }

    void Reverse(char* n) {
        int i;
        int len = strlen(n);
        char temp;
        for (i = 0; i < len / 2; ++i) {
            temp = n[i];
            n[i] = n[len - i - 1];
            n[len - i - 1] = temp;
        }
    }

    long long int toDecimal(int p, char* n) {
        int i = 0;
        int len = strlen(n);
        if (n[0] > '9') {
            n[0] = (int)n[0] - 'A' + 10;
        }
        else n[0] = (int)n[0] - '0';
        long long int result = (long long int)n[0];

        while (i < len - 1) {
            if (n[i + 1] > '9') {
                n[i + 1] = (int)n[i + 1] - 'A' + 10;
            }
            else n[i + 1] = (int)n[i + 1] - '0';
            result = result * ((long long int)p) + (long long int)n[i + 1];
            ++i;
        }
        return result;
    }

    char* fromDecimal(int p, long long int n, char* result) {
        int i = 0;
        int r;
        do {
            r = n % p;
            n = n / (long long int)p;
            if (r < 10) {
                result[i] = r + '0';
            }
            else {
                result[i] = r - 10 + 'A';
            }
            ++i;
        } while (n != 0);

        result[i] = '\0';
        Reverse(result);
        return result;
    }

    int z, i;
    scanf("%d", &z);
    for (i = 0; i < z; ++i) {

        char* instr = malloc(8 * sizeof(char));
        int p, q, j;
        char* n = malloc(65 * sizeof(char));
        char* result = malloc(65 * sizeof(char));
        char* rejestr = malloc(65 * sizeof(char));

        scanf("%s", instr);

        if (strcmp("CONVERT", instr) == 0) {

            scanf("%d %d %s", &p, &q, n);
            long long int temp = toDecimal(p, n);
            result = fromDecimal(q, temp, result);
            printf("%s\n", result);
        }
        else {
            if (strcmp("WRITE", instr) == 0) {
                long long int x;
                scanf("%d %lld", &p, &x);
                if (x >= 0) {
                    result = fromDecimal(2, x, result);
                }
                else result = fromDecimal(2, (-1) * (x + 1), result);
                int len = strlen(result);

                if (len > p - 1) {
                    printf("ERROR\n");
                }                
else {
                    //inicjalizuje pierwsze p-len miejsc na 0;
                    for (j = 0; j < p - len; ++j) {
                        rejestr[j] = '0';
                    }
                    for (j = p - len; j < p; ++j) {
                        rejestr[j] = result[j - p + len];
                    }
                    rejestr[p] = '\0';
                    if (x < 0) {
                        Neg(rejestr);
                    }
                    printf("%s\n", rejestr);
                }
                //getc(stdin);
            }
            else if (strcmp("READ", instr) == 0) {
                scanf("%s", rejestr);
                int len = strlen(rejestr);
                int k = 0;
                j = 0;
                if (rejestr[0] == '0') {
                    while (rejestr[j] == '0' && j < len - 1) {
                        ++j;
                    }
                    while (j < len) {
                        result[k] = rejestr[j];
                        ++k;
                        ++j;
                    }
                    result[k] = '\0';
                    long long int r;
                    r = toDecimal(2, result);
                    printf("%lld\n", r);

                }
                else {
                    Neg(rejestr);
                    while (rejestr[k] == '0' && k < strlen(rejestr) - 1) {
                        ++k;
                    }
                    int m = 0;
                    while (k < strlen(rejestr)) {
                        result[m] = rejestr[k];
                        ++m;
                        ++k;
                    }
                    result[m] = '\0';
                    long long int r;
                    r = (-1) * (toDecimal(2, result) + 1);
                    printf("%lld\n", r);
                }
            }
        }
        free(rejestr);
        free(instr);
        free(result);
        free(n);
    }//z


    return 0;
}