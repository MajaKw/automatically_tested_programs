#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int n, i, j, z;

    scanf("%d", &z);
    for (j = 0; j < z; ++j) {

        scanf("%d", &n);
        getc(stdin);
        typedef struct {
            char colour[13];
        }COLOUR;

        COLOUR* col = malloc(n * sizeof * col);


        for (i = 0; i < n - 1; ++i) {
            scanf("%[^ ]%*c", &col[i]);
        }
        scanf("%s", &col[n - 1]);

        int domP = 0;
        int domN = 0;
        char nameP[13];
        char nameN[13];
        for (i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                if (domP == 0) {
                    strcpy(nameP, col[i].colour);
                    ++domP;

                }
                else if (strcmp(col[i].colour, nameP) != 0) {
                    --domP;
                }
                else ++domP;
            }
            else {
                if (domN == 0) {
                    strcpy(nameN, col[i].colour);
                    ++domN;
                }
                else if (strcmp(col[i].colour, nameN) != 0) {
                    --domN;
                }
                else ++domN;
            }

        }
        int e = 0;
        int o = 0;
        for (i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                if (domP != 0 && strcmp(nameP, col[i].colour) == 0) ++e;
            }
            else if (domN != 0 && strcmp(nameN, col[i].colour) == 0) ++o;
        }
        if ((domP == 0 || n - 4 * e >= 0) && (domN == 0 || n - 4 * o >= 0)) {
            printf("NIE\n");
        }
        else {
            if ((domP != 0 && n - 4 * e < 0) && (domN == 0 || n - 4 * o >= 0)) {
                printf("JEDNA %s\n", nameP);
            }            
else if ((domP == 0 || n - 4 * e >= 0) && (domN != 0 && n - 4 * o < 0)) {
                printf("JEDNA %s\n", nameN);
            }            
else {
                if (strcmp(nameN, nameP) == 0) {
                    printf("JEDNA %s\n", nameP);
                }
                else printf("TAK %s %s\n", nameP, nameN);
            }
        }
        free(col);
    } //j
    return 0;
}