#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
} POINT;

typedef struct
{
    int salary;
    char* name;
} PERSON;

void* Scan_number(int n)
{
    int* number = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; ++i)
    {
        scanf("%d", number + i);
    }
    return (void*)number;
}

void* Scan_point(int n)
{
    POINT* point = malloc(n * sizeof(*point));
    int i;
    for (i = 0; i < n; ++i)
    {
        scanf("%d %d", &(point + i)->x, &(point + i)->y);
    }
    return (void*)point;
}
void* Scan_person(int n)
{
    PERSON* person = malloc(n * sizeof(*person));
    int i;
    for (i = 0; i < n; ++i)
    {
        (person + i)->name = (char*)malloc(17 * sizeof(char));
    }
    for (i = 0; i < n; ++i)
    {
        scanf("%s %d", (person + i)->name, &(person + i)->salary);
    }
    return (void*)person;
}

void Print_number(int n, void* tab)
{
    int* arr = (int*)tab;
    int i;
    for (i = 0; i < n; ++i)
    {
        if (i == n - 1)
        {
            printf("%d\n", *(arr + i));
        }
        else
            printf("%d, ", *(arr + i));
    }
    free(arr);
}
void Print_point(int n, void* tab)
{
    POINT* point = (POINT*)tab;
    int i;
    for (i = 0; i < n; ++i)
    {
        if (i == n - 1)
        {
            printf("%d %d\n", (point + i)->x, (point + i)->y);
        }
        else
            printf("%d %d, ", (point + i)->x, (point + i)->y);
    }
    free(point);
}
void Print_person(int n, void* tab)
{
    PERSON* person = (PERSON*)tab;
    int i;
    for (i = 0; i < n; ++i)
    {
        if (i == n - 1)
        {
            printf("%s %d\n", (person + i)->name, (person + i)->salary);
        }
        else
            printf("%s %d, ", (person + i)->name, (person + i)->salary);
    }
    for (i = 0; i < n; i++)
        free((person + i)->name);
    free(person);
}

int Compare1(const void* x, const void* y)
{ //jesli jest mniejsza to przestaw czyli ustaw return na 1 - rosnąco
    int* a = (int*)x;
    int* b = (int*)y;
    if (*a < *b)
    {
        return 1;
    }
    else
        return 0;
}
int Compare0(const void* x, const void* y)
{
    //jesli jest wieksza to przestaw czyli ustaw return na 1 - malejąco
    int* a = (int*)x;
    int* b = (int*)y;
    if (*a > *b)
    {
        return 1;
    }
    else
        return 0;
}
int Compare3(const void* x, const void* y)
{
    int* a = (int*)x;
    int* b = (int*)y;
    if (abs(*a) < abs(*b))
    {
        return 1;
    }
    else if (abs(*a) == abs(*b))
    {
        if (*a < *b)
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}
int Compare2(const void* x, const void* y)
{
    int* a = (int*)x;
    int* b = (int*)y;
    if (abs(*a) > abs(*b))
    {
        return 1;
    }
    else if (abs(*a) == abs(*b))
    {
        if (*a > *b)
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}
int Compare5(const void* x, const void* y)
{
    POINT* point1 = (POINT*)x;
    POINT* point2 = (POINT*)y;
    if (point1->x < point2->x)
    {
        return 1;
    }
    else if (point1->x > point2->x)
    {
        return 0;
    }
    else if (point1->y < point2->y)
    {
        return 1;
    }
    else
        return 0;
}

int Compare4(const void* x, const void* y)
{
    POINT* point1 = (POINT*)x;
    POINT* point2 = (POINT*)y;
    if (point1->x > point2->x)
    {
        return 1;
    }
    else if (point1->x < point2->x)
    {
        return 0;
    }
    else if (point1->y > point2->y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Compare7(const void* x, const void* y)
{
    POINT* point1 = (POINT*)x;
    POINT* point2 = (POINT*)y;
    if (point1->y < point2->y)
    {
        return 1;
    }
    else if (point1->y > point2->y)
    {
        return 0;
    }
    else if (point1->x < point2->x)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Compare6(const void* x, const void* y)
{
    POINT* point1 = (POINT*)x;
    POINT* point2 = (POINT*)y;
    if (point1->y > point2->y)
    {
        return 1;
    }
    else if (point1->y < point2->y)
    {
        return 0;
    }
    else if (point1->x > point2->x)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Compare8(const void* x, const void* y)
{
    PERSON* person1 = (PERSON*)x;
    PERSON* person2 = (PERSON*)y;
    if (person1->salary > person2->salary)
    {
        return 1;
    }
    else if (person1->salary < person2->salary)
    {
        return 0;
    }
    else
    {
        int first = strcmp(person1->name, person2->name);
        if (first > 0)
        {
            return 1;
        }
        else
            return 0;
    }
    return 0;
}

int Compare9(const void* x, const void* y)
{
    PERSON* person1 = (PERSON*)x;
    PERSON* person2 = (PERSON*)y;
    if (person1->salary < person2->salary)
    {
        return 1;
    }
    else if (person1->salary > person2->salary)
    {
        return 0;
    }
    else
    {
        int first = strcmp(person1->name, person2->name);
        if (first < 0)
        {
            return 1;
        }
        else
            return 0;
    }
    return 0;
}

void Bubble_sort(void* arr, int n, int size, int Compare(const void*, const void*))
{
    int count = 0;
    int j;
    int swap;
    do
    {
        swap = 0;
        ++count;
        for (j = 0; j < n - count; ++j)
        {
            int comp = Compare(arr + j * size, arr + (j + 1) * size);
            if (comp != 0)
            {
                char temp[size];
                swap = 1;
                memcpy(temp, arr + size * j, size);
                memcpy(arr + size * j, arr + size * (j + 1), size);
                memcpy(arr + size * (j + 1), temp, size);
            }
        }
    } while (swap == 1);
}

void (*Print[3])(int, void*) = { Print_number, Print_point, Print_person };

void* (*Scan[3])(int) = { Scan_number, Scan_point, Scan_person };
int (*Compare[10])(const void*, const void*) = { Compare0, Compare1, Compare2, Compare3, Compare4,
                                                  Compare5, Compare6, Compare7, Compare8, Compare9 };

int main()
{

    int n, which_sort, z, i;
    scanf("%d", &z);
    for (i = 0; i < z; ++i)
    {
        scanf("%d %d", &n, &which_sort);
        void* arr = (*Scan[which_sort / 4])(n);
        int* size = malloc(3 * sizeof(int));
        *size = sizeof(int);
        *(size + 1) = sizeof(POINT);
        *(size + 2) = sizeof(PERSON);

        Bubble_sort(arr, n, *(size + which_sort / 4), (*Compare[which_sort]));

        (*Print[which_sort / 4])(n, arr);
    }

    return 0;
}