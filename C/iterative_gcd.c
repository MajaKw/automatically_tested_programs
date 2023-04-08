#include <stdlib.h>
#include <stdio.h>

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    int j;
    for (j = 0; ((a | b) & 1) == 0; ++j)
    {
        a >>= 1;
        b >>= 1;
    }
    while ((a & 1) == 0)
        a >>= 1;
    do
    {
        while ((b & 1) == 0)
            b >>= 1;
        if (a > b)
        {
            int temp = a;
            a = b;
            b = temp;
        }
        b = (b - a);
    } while (b != 0);
    return a << j;
}
int main()
{
    int z, a, b;
    scanf("%d", &z);
    for (int i = 0; i < z; ++i)
    {
        scanf("%d %d", &a, &b);
        int g = gcd(a, b);
        printf("%d\n", g);
    }
    return 0;
}