#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
} POINT;

int cmp(const void* x, const void* y)
{
    POINT* a = (POINT*)x;
    POINT* b = (POINT*)y;
    if (a->x > b->x)
    {
        return 1;
    }
    else if (a->x < b->x)
    {
        return -1;
    }
    else
        return 0;
}
int Can_place(int** A, int* rows, int* diagonal, int* diagonal2, int j, int ships, int m, int n, POINT* point, int counter, int swap)
{
    int false = 0;
    int true = 1;
    int i;
    if (ships == 0)
    {
        return true;
    }
    else
    {
        // i - rows --- coordinate - y
        // j - columns
        for (i = 0; i < n; ++i)
        {
            if (j > m)
            {
                return false;
            }

            else
            {
                if (rows[i] == 0 && diagonal[j - i + n - 1] == 0 && diagonal2[j + i] == 0)
                {
                    // check point is occupied
                    if (swap == 1)
                    {
                        point[counter].x = j;
                        point[counter].y = i;
                    }
                    else
                    {
                        point[counter].y = j;
                        point[counter].x = i;
                    }
                    rows[i] = 1;
                    diagonal[j - i + n - 1] = 1;
                    diagonal2[j + i] = 1;
                    --ships;
                    ++counter;
                    // check if it leads to a solution
                    int check = Can_place(A, rows, diagonal, diagonal2, j + 1, ships, m, n, point, counter, swap);
                    if (check == 1)
                    {
                        return true;
                    }
                    // unmark this place because it doesn't lead to solution
                    rows[i] = 0;
                    diagonal[j - i + n - 1] = 0;
                    diagonal2[j + i] = 0;
                    ++ships;
                    --counter;
                }

            } // else
        }
        // if ship can't be placed anywhere
        return false;
    }
}

int main()
{
    int z, i, j, k, n, m;
    int swap;
    int ships, counter;
    int** A;
    int* rows;
    int* diagonal;
    int* diagonal2;
    POINT* point;

    scanf("%d", &z);
    for (k = 0; k < z; ++k)
    {
        swap = 0;
        scanf("%d %d %d", &n, &m, &ships);

        int smaller = n < m ? n : m;
        int s = n;
        if (smaller == n)
        {
            int tmp = m;
            m = n;
            n = tmp;
            swap = 1;
        }
        if (ships > smaller)
        {
            printf("NIE\n");
        }
        else
        {
            counter = 0;
            A = (int**)malloc(n * sizeof(int*));
            point = malloc(ships * sizeof(*point));
            for (i = 0; i < n; ++i)
            {
                A[i] = (int*)malloc(m * sizeof(int));
            }
            rows = malloc(n * sizeof(int));
            memset(rows, 0, m * sizeof(int));
            diagonal = malloc((n + m - 1) * sizeof(int));
            diagonal2 = malloc((n + m - 1) * sizeof(int));
            memset(diagonal, 0, (n + m - 1) * sizeof(int));
            memset(diagonal2, 0, (n + m - 1) * sizeof(int));
            i = 0;
            // int Can_place(int **A, int *columns, int *diagonal, int j, int ships, int m, int n, POINT *point)
            int can = Can_place(A, rows, diagonal, diagonal2, i, ships, m, n, point, counter, swap);
            if (can == 0)
            {
                printf("NIE\n");
            }
            else
            {
                printf("TAK\n");
                qsort(point, ships, sizeof(point), cmp);
                for (i = 0; i < ships; ++i)
                {
                    printf("%d %d\n", point[i].x + 1, point[i].y + 1);
                }
                // }
            }
            free(point);
            free(diagonal);
            free(diagonal2);
            for (i = 0; i < n; ++i)
            {
                free(A[i]);
            }
            free(A);
        } // else

    } // z
    return 0;
}