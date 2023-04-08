#include <stdio.h>
#include <stdlib.h>

int main() {

    void Swap(int ix_a, int ix_b, int* tri) {
        int temp = tri[ix_a];
        tri[ix_a] = tri[ix_b];
        tri[ix_b] = temp;
    }

    int i, j, k, z, n;
    int* tri;

    scanf("%d", &z);
    for (i = 0; i < z; ++i) {
        scanf("%d", &n);
        tri = malloc(n * sizeof(int));
        for (j = 0; j < n; ++j) {
            scanf("%d", &tri[j]);
        }

        // Selection Sort
        for (j = 0; j < n - 1; ++j) {
            int min = j;
            int swap = 0;
            for (k = j + 1; k < n; ++k) {
                if (tri[k] < tri[min]) {
                    min = k;
                    swap = 1;
                }
            }
            if (swap == 1) Swap(j, min, tri);
        }

        for (j = 0; j < n; ++j) {
            printf("%d ", tri[j]);
        }
        printf("\n");
        //Wyznaczam ile trojkatow

        long long int number = 0;
        int left, right, iter;
        for (iter = n - 1; iter > 0; --iter) {
            left = 0;
            right = iter - 1;
            while (left < right) {
                if ((unsigned int)(tri[left] + tri[right]) > (unsigned int)(tri[iter])) {
                    number += right - left;
                    --right;
                }
                else ++left;
            }
        }
        printf("%lld\n", number);

        free(tri);
    }


    return 0;
}