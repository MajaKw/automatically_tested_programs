#include <stdlib.h>
#include <stdio.h>

int gcd(int a, int b)
{
    if (a == b)
        return a;
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (~a & 1)
    {
        if (b & 1)
            return gcd(a >> 1, b);
        else
            return gcd(a >> 1, b >> 1) << 1;
    }
    if (~b & 1)
        return gcd(a, b >> 1);
    if (a > b)
        return gcd((a - b) >> 1, b);
    return gcd((b - a) >> 1, a);
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