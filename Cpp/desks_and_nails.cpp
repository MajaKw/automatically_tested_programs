#include <iostream>
#include <cstring>

using namespace std;

class DESKA {
public:
    int b;
    int e;
    DESKA(int a = 0, int b = 0) {
        b = a;
        e = b;
    }
};

int main() {
    ios_base::sync_with_stdio(false);

    int z;
    cin >> z;
    while (z--) {

        int d, g;
        int range = 0;
        cin >> d >> g;
        DESKA* deska = new DESKA[d];
        int* wszystkie = new int[g];
        // pos[nr_deski][begin/end]
        for (int i = 0; i < d; ++i) {
            cin >> deska[i].b >> deska[i].e;
            // roznica w zadaniu numery sa od 1, tab zaczyna sie od 0
            --deska[i].b;
            --deska[i].e;
            if (deska[i].e > range) range = deska[i].e;
        }

        for (int i = 0; i < g; ++i) {
            cin >> wszystkie[i];
            --wszystkie[i];
        }

        int begin = 0;
        int end = g;
        int mid;
        int result = -1;
        ++range;
        int* prefix = new int[range];
        int* gwozdzie = new int[range];

        while (begin <= end) {
            mid = (begin + end) / 2;
            memset(gwozdzie, 0, range * sizeof(int));
            memset(prefix, 0, range * sizeof(int));
            // zaznaczam, na tablicy gwozdzi do danej pozycji, ktory wystapil
            for (int i = 0; i < mid; ++i) {
                if (wszystkie[i] < range)
                    gwozdzie[wszystkie[i]] = 1;
            }

            // inicjalizacja tablicy prefixow
            int count = 0;
            for (int i = 0; i < range; ++i) {
                if (gwozdzie[i] == 1)
                    ++count;
                prefix[i] = count;
            }

            int nie = 0;

            // analizowanie deseke po kolei
            for (int i = 0; i < d; ++i) {
                //special case 1: deska na jedno pole
                if (deska[i].b == deska[i].e) {
                    if (gwozdzie[deska[i].b] == 0) {
                        nie = 1;
                        break;
                    }
                }
                else {
                    //special case 2: deska na calą tablicę

                    if (deska[i].b == 0 && deska[i].e == range - 1) {

                        if (prefix[deska[i].e] == 0) {
                            nie = 1;
                            break;
                        }
                    }
                    else {
                        //special case 3: deska do ostatniego pola tablicy

                        if (deska[i].e == range - 1) {
                            if (prefix[deska[i].b - 1] == prefix[deska[i].e]) {
                                nie = 1;
                                break;
                            }
                        }
                        else {
                            //normalny case: deska nie sięga do ostatniego pola tablicy

                            if (prefix[deska[i].b] == prefix[deska[i].e + 1] && gwozdzie[deska[i].b] != 1) {
                                nie = 1;
                                break;
                            }                            
else {
                                //zaraz potem jest gwozdz
                                if (gwozdzie[deska[i].b] != 1 && gwozdzie[deska[i].e + 1] == 1 && (prefix[deska[i].e + 1] - prefix[deska[i].b] == 1)) {
                                    nie = 1;
                                    break;
                                }
                            }
                        }
                    }
                }//else
            } //for deski
            if (nie == 1) {
                // za mały prefix
                begin = mid + 1;
            }
            else {
                end = mid - 1;
                result = mid;
            }
        }// while BS
        if (result == -1) {
            cout << "ERROR" << endl;
        }        
else
            cout << result << endl;


        delete[] deska;
        delete[] wszystkie;
        delete[] gwozdzie;
        delete[] prefix;

    } // while z--
} // main

// 14 19
// 18 24
// 11 15
// 6 23
// 4 4
// 4 21
// 7 14
// 12 15
// 16 6 27 4 30 14 14 19 19 24 31 15