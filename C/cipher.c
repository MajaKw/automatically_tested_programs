#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){

    int BitCount(int n){
        int count = 0;
        while (n){
            count += 1 & n;
            n >>= 1;
        }
        return count;
    }



    int z, k;
    scanf("%d", &z);
    for(k=0; k<z; ++k){
         int i, v;

    int* val = malloc(27*sizeof(int));


    for(i = 0; i < 27; ++i){
        scanf("%d", &v);
        val[i] = v;
    }

    int task, l;
    scanf("%d", &task);

    for(l=0; l<task; ++l){
        char napis [3001];
     int bits = 0;
        char polecenie [10];
        scanf("%s", polecenie);
        if(strcmp("KODUJ", polecenie) == 0){

        scanf("%s", napis);

        int len = strlen(napis);
        int temp;
        int count = 5;
        int ile = (int)ceil((double)len*0.3125);
        int* sum = malloc(ile*sizeof(int));
        memset(sum, 0, ile*sizeof(int));
        int waste = 0;
        //ktora to liczba
        int j = 0;

        for(i = 0; i<len; ++i){

            if(napis[i] != '.'){
                temp = val[napis[i] - 'A'];
            }else temp = val[26];

            if(count < 5 && waste != 0){

                int pom;
                pom = (temp >> (5 - waste)) << (5 - waste);
                count += 5;
                sum[j] += (pom ^ temp) << (16 - count + waste);
                count += 5;
                if(napis[i+1] == '\0'){
                        break;
                    }
                continue;
            }else if(count <= 15){
                if(waste == 0){
                    sum[j] += temp << 16 - count;
                }else{
                    sum[j] += temp << (16 - count + waste);
                }
                    count += 5;
                    if(napis[i+1] == '\0'){
                        break;
                    }
                    continue;

                }else{
                    int i2 = i;
                    ++ waste;
                    if (waste == 5){
                        count = 5;
                         waste = 0;
                         ++i;
                    }
                    if(waste != 0){
                    sum[j] += temp >> (5 - waste);
                    count = 0;
                    } else sum[j] += temp;
                    --i;
                    ++j;
                    if(napis[i+1] == '\0'){
                        break;
                    }

                    //cofnij i zeby powtorzyc na tej samej literze



                }

         }


        for(j=0; j<len; ++j){
            if(napis[j] == '.'){
                bits += BitCount(val[26]);
            }else   bits += BitCount(val[napis[j] - 'A']);
        }

        printf("%d %d", len, bits);
         for(j=0; j<ile; ++j){
             printf(" %d", sum[j]);
         }printf("\n");

        free(sum);
        }else if (strcmp("DEKODUJ", polecenie) == 0){}

        }//task
        free(val);
    }// z

    return 0;
}