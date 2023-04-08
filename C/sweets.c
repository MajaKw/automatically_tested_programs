#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int z, j;
    scanf("%d", &z);
    for (j = 0; j < z; ++j) {


        int n, f, i, max;
        int* a;
        int begin = 0;
        int ix = 1;
        int end = 2;
        int groupL = 1;
        int groupP = 1;
        int index = 1;

        int* liczl;
        int* liczr;

        scanf("%d %d", &n, &f);
        a = malloc(n * sizeof(int));

        for (i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            if (a[i] > max) max = a[i];
        }
        ++max;
        liczl = malloc(max * sizeof(int));
        liczr = malloc(max * sizeof(int));
        memset(liczr, 0, max * sizeof(int));
        memset(liczl, 0, max * sizeof(int));

        liczl[a[begin]] = 1;

        for (ix = 1; ix < n - 1; ++ix) {
            liczr[a[ix]] = 0;
            while (end < n && ix < end && liczr[a[end]] == 0) {
                liczr[a[end]] = 1;
                ++end;
            }
            if (ix > 1) {
                if (liczl[a[ix - 1]] == 1) {
                    while (liczl[a[ix - 1]] == 1 && begin < ix) {
                        liczl[a[begin]] = 0;
                        ++begin;
                    }
                }
                liczl[a[ix - 1]] = 1;
            }
            if (end - begin - 1 > groupL + groupP) {
                groupL = ix - begin;
                groupP = end - ix - 1;
                index = ix;
            }
            if (end > n - 1) break;
        }
        printf("%d %d %d\n", index, groupL, groupP);

        free(liczl);
        free(liczr);
        free(a);
    }//j
    return 0;
}