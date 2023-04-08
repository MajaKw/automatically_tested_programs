#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
} MOVE;

int Can_find(int** A, int** T, MOVE* move, MOVE is, int n, int m, int treasure, int steps, int r)
{
    int true = 1;
    int false = 0;
    int i;
    int t = 0;
    if (is.x >= n || is.x < 1)
    {
        return false;
    }
    else if (is.y >= m || is.y < 1)
    {
        return false;
    }
    else if (A[is.x][is.y] == 2)
    {
        return false;
    }
    else
    {
        if (A[is.x][is.y] == 1)
        {
            --treasure;
            t = 1;
        }
        A[is.x][is.y] = 2;
        T[is.x][is.y] = steps;
        ++steps;
    }
    if (treasure == 0)
    {
        return true;
    }
    for (i = 0; i < r; ++i)
    {
        MOVE temp;
        temp.x = move[i].x + is.x;
        temp.y = move[i].y + is.y;
        int check = Can_find(A, T, move, temp, n, m, treasure, steps, r);
        if (check == 1)
            return true;
    }

    if (t == 1)
    {
        A[is.x][is.y] = 1;
        ++treasure;
    }
    else
    {
        A[is.x][is.y] = 0;
    }
    T[is.x][is.y] = 0;
    --steps;
    return false;
}

int main()
{

    int** A;
    int** result;
    int i, j, k, z, n, m, r;
    MOVE* move;
    MOVE start;
    int treasure, steps;

    scanf("%d", &z);

    for (k = 0; k < z; ++k)
    {
        steps = 1;
        treasure = 0;
        scanf("%d", &r);
        move = malloc(r * sizeof(*move));
        for (i = 0; i < r; ++i)
        {
            scanf("%d %d", &move[i].x, &move[i].y);
        }
        scanf("%d %d %d %d", &n, &m, &start.x, &start.y);
        ++n;
        ++m;
        A = (int**)malloc(n * sizeof(int*));
        result = (int**)malloc(n * sizeof(int*));
        A[0] = (int*)malloc(m * sizeof(int));
        result[0] = (int*)malloc(m * sizeof(int));

        for (i = 1; i < n; ++i)
        {
            A[i] = (int*)malloc(m * sizeof(int));
            result[i] = (int*)malloc(m * sizeof(int));
            for (j = 1; j < m; ++j)
            {
                scanf("%d", &A[i][j]);
                result[i][j] = 0;

                if (A[i][j] == 1)
                    ++treasure;
            }
        }
        if (start.x >= n || start.x < 1 || start.y >= m || start.y < 1)
        {
            printf("NIE\n");
        }
        else {
            int can = Can_find(A, result, move, start, n, m, treasure, steps, r);
            if (can == 0)
            {
                printf("NIE\n");
            }
            else
            {
                printf("TAK\n");
                for (i = 1; i < n; ++i)
                {
                    for (j = 1; j < m; ++j)
                    {
                        printf("%d ", result[i][j]);
                    }
                    printf("\n");
                }
            }
        }
        free(move);
        for (int i = 0; i < n; ++i)
        {
            free(result[i]);
            free(A[i]);
        }
        free(result);
        free(A);
    } //for z
    return 0;
}