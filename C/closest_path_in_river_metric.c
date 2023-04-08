#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int x;
    int y;
    char* name;
} HOUSE;

int Compare(const void* a, const void* b)
{
    HOUSE* house1 = (HOUSE*)a;
    HOUSE* house2 = (HOUSE*)b;

    if (house1->x < house2->x)
    {
        return -1;
    }
    else if (house1->x > house2->x)
    {
        return 1;
    }
    else
        return 0;
}

int main()
{

    int z, j;
    scanf("%d", &z);
    for (j = 0; j < z; ++j)
    {

        int n, i;

        scanf("%d", &n);
        HOUSE* house = malloc(n * sizeof(*house));

        for (i = 0; i < n; ++i)
        {
            (house + i)->name = (char*)malloc(11 * sizeof(char));
            scanf("%d %d %s", &(house + i)->x, &(house + i)->y, (house + i)->name);
        }

        qsort(house, n, sizeof(*house), Compare);

        int height, height1, height2, lenght, lenght1, lenght2, sum, sum1, sum2, min, nearest_prev;
        if (house->y < 0)
            house->y = -(house->y);
        lenght = (house + 1)->x - house->x;
        if ((house + 1)->y < 0)
            (house + 1)->y = -(house + 1)->y;
        height = house->y + (house + 1)->y;
        min = height + lenght;
        int result1 = 0;
        int result2 = 1;
        nearest_prev = 1;

        if (n > 2)
        {
            //znajdz minimum dla pierwszego
            for (i = 1; i < n; ++i)
            {
                lenght = (house + i)->x - house->x;
                if ((house + i)->y < 0)
                    (house + i)->y = -(house + i)->y;
                height = house->y + (house + i)->y;
                sum = height + lenght;
                if (sum < min)
                {
                    nearest_prev = i;
                    min = sum;
                }
            }
            result1 = 0;
            result2 = nearest_prev;

            //idz po kolei po domkach sprawdzajac czy domek sprawdzajac czy blizej jest do poprzedniego domku czy do domku najblizszego poprzedniemu
            // 2 - blizej do poprzedniego, 1 - blizej do najblizszego poprzedniemu
            for (i = 1; i < n; ++i)
            {
                if (nearest_prev == i)
                {
                    nearest_prev = i - 1;
                }
                else
                {
                    lenght1 = abs((house + i)->x - (house + nearest_prev)->x);
                    lenght2 = abs((house + i)->x - (house + i - 1)->x);
                    height1 = (house + i)->y + (house + nearest_prev)->y;
                    height2 = (house + i)->y + (house + i - 1)->y;
                    sum1 = height1 + lenght1;
                    sum2 = height2 + lenght2;

                    if (sum1 <= sum2)
                    {
                        //tu domek najblizszy domkowi k-1 jest najblizej
                        if (sum1 < min)
                        {
                            result1 = nearest_prev;
                            result2 = i;
                            min = sum1;
                        }
                    }
                    else if (sum2 < sum1)
                    {
                        // tu domek k-1 byl najblizej
                        if (sum2 < min)
                        {
                            result1 = i - 1;
                            result2 = i;
                            min = sum2;
                        }
                        nearest_prev = i - 1;
                    }
                }
            }
        }
        printf("%d\n", min);
        printf("%s %s\n", (house + result1)->name, (house + result2)->name);

        for (i = 0; i < n; i++)
            free((house + i)->name);
        free(house);

    } //z

    return 0;
}