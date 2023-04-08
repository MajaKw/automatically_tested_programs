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

        //Insertion Sort
        for (j = 1; j < n; ++j) {
            int k = j - 1;
            int temp = tri[j];
            while (tri[k] > temp && k >= 0) {
                tri[k + 1] = tri[k];
                --k;
            }
            tri[k + 1] = temp;
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