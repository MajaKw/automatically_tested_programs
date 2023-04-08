#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{

    int n, i , j;
    scanf("%d", &n);
    int *arr;
    arr = malloc(n*sizeof(int));
    for(i=0; i<n; ++i){
        scanf("%d", &arr[i]);
    }
    for(i=0; i<n; ++i){
        int r = 0;
        for(j=2; j<=sqrt(arr[i]); ++j){
            if(arr[i]%j == 0){
                ++r;
                break;
            }
        }

        if(r>0){
            printf("%d jest zlozona", arr[i]);
            printf("\n");
            }else{
            printf("%d jest  pierwsza", arr[i]);
            printf("\n");
            }
    }
    free(arr);
    return 0;

}
