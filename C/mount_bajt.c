#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>

int main() {
    int n, d, i, j, b, e, number, mid, prev, next, nearest, sets, right, left, styczna1, styczna2, x, y, k;
    int* wspt;
    double l, r, delta, temp, s1, s2;

    int Left(int* wsp, int styczna1, int b, int e) {

        int left;
        int mid = (b + e) / 2;

        if (wspt[b] < styczna1) {
            do {
                mid = (b + e) / 2;
                if (wspt[mid] < styczna1) {
                    left = mid;
                    b = mid + 1;
                }
                else {
                    e = mid - 1;
                }
            } while (b <= e);
        }        
else left = b - 1;

        return left;
    }

    int Right(int* wsp, int styczna2, int b, int e) {

        int mid = (b + e) / 2;
        int right;
        if (wspt[e] > styczna2) {
            do {
                mid = (b + e) / 2;
                if (wspt[mid] > styczna2) {
                    right = mid;
                    e = mid - 1;
                }
                else {
                    b = mid + 1;
                }

            } while (b <= e);
        }
        else right = e + 1;


        return right;
    }



    scanf("%d", &sets);
    for (j = 0; j < sets; ++j) {

        scanf("%d", &n);
        //scanf("%d", &n);
        wspt = malloc(n * sizeof(int));
        for (i = 0; i < n; ++i) {
            scanf("%d", &wspt[i]);
        }


        scanf("%d", &d);

        for (i = 0; i < d; ++i) {
            scanf("%d %d %d", &x, &y, &k);
            b = 0;
            e = n - 1;
            //znajdz indeks pierwszej liczby wiekszej badz rownej od a;
            if (b == 0 && e == 0) {
                next = e;
                if (e == 0) {
                    prev = 0;
                }                
else {
                    prev = next - 1;
                }
            }
            else {

                if (wspt[e] * x >= y) {
                    do {
                        mid = (b + e) / 2;
                        if (wspt[mid] * x < y) {
                            b = mid + 1;
                        }
                        else {
                            next = mid;
                            e = mid - 1;
                        }

                    } while (b <= e);
                }
                else next = e;

                b = 0;
                if (wspt[b] * x < y && next != 0) {
                    prev = next - 1;
                }
                else prev = 0;
            }

            l = (abs(wspt[prev] * x - y)) * sqrt((long double)(wspt[next] * wspt[next] + 1));
            r = (abs(wspt[next] * x - y)) * sqrt((long double)(wspt[prev] * wspt[prev] + 1));
            if (l <= r) {
                nearest = prev;
            }
            else nearest = next;

            //1. kiedy wszystkie proste wpadaja w okrag



            if (x <= k && y <= k) {
                right = n;
                left = -1;
            }
            else {

                if (k == 0) {
                    if (nearest * x != y) {
                        number = 0;
                    }
                    else {
                        styczna1 = wspt[nearest];
                        styczna2 = wspt[nearest];

                    }
                }
                else {

                    //2. kiedy dol kola jest pod osia x

                    double x2 = (double)(x * x);
                    double y2 = (double)(y * y);
                    double k2 = (double)(k * k);
                    double xy2 = (double)(2 * x * y);
                    double delta = (double)(x2 + y2 - k2);
                    double deltasqrt = 2 * (double)(k)*sqrt(delta);
                    double a2 = 2 * (x2 - k2);
                    if (a2 == 0) {
                        styczna1 = ceil((y2 - k2) / xy2);
                        styczna2 = -1;
                    }
                    else {

                        s1 = (double)(xy2 - deltasqrt) / (2 * (x2 - k2));
                        s2 = (double)(xy2 + deltasqrt) / (2 * (x2 - k2));
                        temp = s1;
                        if (x > k) {
                            if (s1 > s2) {
                                s1 = s2;
                                s2 = temp;
                            }
                        }
                        else {
                            if (x <= k && y > k) {
                                if (s2 > s1) {
                                    s1 = s2;
                                }
                            }

                        }
                        styczna1 = (int)(ceil(s1));
                        styczna2 = (int)(floor(s2));
                    }
                }
                if (y <= k && x > k) {

                    b = next;
                    e = n - 1;
                    left = -1;

                    right = Right(wspt, styczna2, b, e);
                }                
else {
                    //3. okrag przecina/styka tylko do osi y
                    if (x <= k && y > k) {
                        b = 0;
                        e = n - 1;
                        right = n;

                        left = Left(wspt, styczna1, b, e);
                    }
                    else {
                        if (x > k && y > k) {

                            b = 0;
                            e = prev;
                            left = Left(wspt, styczna1, b, e);

                            b = next;
                            e = n - 1;
                            right = Right(wspt, styczna2, b, e);
                        }

                    }
                }
            }





            number = right - left - 1;

            printf("%d %d\n", nearest, number);
        }//for modrzewie

        free(wspt);
    }//for zestawy
    return 0;
}