#include <stdio.h>
#include <stdlib.h>

int main() {

    void Swap(int ix_a, int ix_b, int* tri) {
        int temp = tri[ix_a];
        tri[ix_a] = tri[ix_b];
        tri[ix_b] = temp;
    }

    int i, j, z, n;
    int* tri;

    scanf("%d", &z);
    for (i = 0; i < z; ++i) {
        scanf("%d", &n);
        tri = malloc(n * sizeof(int));
        for (j = 0; j < n; ++j) {
            scanf("%d", &tri[j]);
        }
        //Bubble Sort
        int swap;
        int count = 0;
        do {
            swap = 0;
            ++count;
            for (j = 0; j < n - count; ++j) {
                int min = (tri[j] < tri[j + 1]) ? tri[j] : tri[j + 1];
                if (min != tri[j]) {
                    swap = 1;
                    Swap(j, j + 1, tri);
                }
            }
        } while (swap == 1);
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