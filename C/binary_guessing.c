#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main()
{

    int z, j;
    scanf("%d", &z);
    for (j = 0; j < z; ++j)
    {

        int i, n, left, right, station, k;
        int count = 0;
        int* possible;
        int* result;

        scanf("%d", &n);
        scanf("%d", &station);
        k = (int)sqrt((double)10000000) + 1;
        possible = malloc((n / 2 + 1) * sizeof(int));
        result = malloc((n / 2 + 1) * sizeof(int));

        for (i = 0; i < n; ++i)
        {
            if (i != n - 1)
                scanf("%d", &right);
            if (i == 0)
            {
                if (n == 1)
                {
                    *(possible + count) = 0;
                    ++count;
                }
                else if (station < right)
                {
                    *(possible + count) = 0;
                    ++count;
                }
            }
            else if (i == n - 1)
            {
                if (station < left)
                {
                    *(possible + count) = i;
                    ++count;
                }
            }
            else if (station < left && station < right)
            {
                *(possible + count) = i;
                ++count;
            }
            left = station;
            station = right;
        }

        // maksymalnie moze byc k = sqrt(n) + 1 stacji, wybieramy k binarnie i sprawdzamy czy sie da tyle stacji
        int b = 0;
        int e = k;
        int mid, x;
        int max = 0;
        int reality = 1;
        if (count == 0)
        {
            max = 0;
            printf("%d\n", max);
        }
        else
        {
            do
            {
                reality = 1;
                mid = (b + e) / 2;
                int temp = *possible;
                for (i = 1; i < count; ++i)
                {
                    if (*(possible + i) - temp >= mid)
                    {
                        ++reality;
                        temp = *(possible + i);
                    }
                    if (reality >= mid)
                        break;
                }
                if (reality >= mid)
                {
                    b = mid + 1;
                    if (mid > max)
                        max = mid;
                }
                else
                {
                    e = mid - 1;
                }
            } while (b <= e);

            x = 1;
            *result = *possible;
            int temp = *possible;
            for (i = 1; i < count; ++i)
            {
                if (*(possible + i) - temp >= max)
                {
                    temp = *(possible + i);
                    *(result + x) = temp;
                    ++x;
                }
            }

            printf("%d\n", max);
            for (i = 0; i < max; ++i)
            {
                if (i == max - 1)
                {
                    printf("%d\n", *(result + i));
                }
                else
                {
                    printf("%d ", *(result + i));
                }
            }
        }
        free(possible);
        free(result);

    } //z

    return 0;
}