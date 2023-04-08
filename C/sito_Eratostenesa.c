#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int i, j, k, x, n, a, temp, wynik, number, s, potega;
    int *p, *d;
    //dzielnik = malloc(8000000*sizeof(int));
    p = malloc(8000000 * sizeof(int));
    d = malloc(8000000 * sizeof(int));
    p[0] = 0;
    d[0] = 1;
    for (i = 1; i < 8000000; ++i)
    {
        p[i] = 1;
    }
    for (i = 1; i < 8000000; ++i)
    {
        if (p[i] == 1)
        {
            d[i] = i + 1;
            for (k = 1; i + (i + 1) * k < 8000000; ++k)
            {
                x = i + (i + 1) * k;
                if (p[x] == 1)
                {
                    p[x] = 0;
                    d[x] = i + 1;
                }
            }
        }
    }
    scanf("%d", &number);
    for (j = 0; j < number; ++j)
    {
        scanf("%d", &a);
        temp = 1;
        s = 1;
        wynik = 1;
        do
        {
            temp = a;
            a = a / d[a - 1];
            s = 1 + d[temp - 1];
            potega = d[temp - 1];
            while (d[a - 1] == d[temp - 1] && a != 1)
            {
                potega = d[temp - 1] * potega;
                s += potega;
                temp = a;
                a = a / d[a - 1];
            }
            wynik = wynik * s;
        } while (a != 1);
        printf("%d \n", wynik);
    }
    free(p);
    free(d);
}