#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// accumulator ma byc shirt int
// GDB
unsigned short int szukaj_adr(char* adrs, char** adresowanie)
{
    unsigned short int adr, i;
    for (i = 0; i < 4; ++i)
    {
        if (strcmp(adresowanie[i], adrs) == 0)
        {
            adr = i;
        }
    }
    return adr;
}

unsigned short int Znak(short int liczba)
{
    unsigned short int temp = 0;
    if (liczba < 0)
    {
        ++temp;
        temp <<= 15;
    }
    return temp;
}

unsigned short int Rozkaz(unsigned short int r)
{
    unsigned short int temp = r;
    temp <<= 11;
    return temp;
}

unsigned short int Adresowanie(unsigned short int a)
{
    unsigned short int temp = a;
    temp <<= 9;
    return temp;
}

unsigned short int Liczba(short int liczba)
{
    unsigned short int temp;
    if (liczba < 0)
    {
        temp = (-1) * liczba;
        temp = ~temp + 1;
        temp = temp - ((temp >> 9) << 9);
    }
    else
        temp = liczba;
    return temp;
}

void NUL(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
}
void STOP(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
}
void LOAD(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *AC = *OP;
}
void STORE(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    M[*OP] = *AC;
}
void JUMP(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *PC = *OP - 1;
}
void JNEG(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    if (*AC < 0) {
        *PC = *OP - 1;
    }
}
void JZERO(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    if (*AC == 0)
        *PC = *OP - 1;
}
void Nic(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
}
void ADD(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *AC = *AC + *OP;
}
void SUB(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *AC = *AC - *OP;
}
void SHL(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *AC <<= *OP;
}
void SHR(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *AC >>= *OP;
}
void AND(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *AC = *AC & *OP;
}
void OR(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *AC = *AC | *OP;
}
void NOT(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *AC = ~(*AC);
}
void XOR(short int* IR, short int* PC, short int* AC, short int* OP, unsigned short int* M)
{
    *AC = *AC ^ *OP;
}

void (*f[16])(short int*, short int*, short int*, short int*, unsigned short int*) = { NUL, STOP, LOAD, STORE, JUMP, JNEG, JZERO, Nic, ADD,
                                                                   SUB, SHL, SHR, AND, OR, NOT, XOR };

int szukaj_kom(char* kom, char** komenda)
{
    int nr_kom, i;
    for (i = 0; i < 16; ++i)
    {
        if (strcmp(kom, komenda[i]) == 0)
        {
            nr_kom = i;
        }
    }
    return nr_kom;
}

int main()
{

    int z, j;
    scanf("%d", &z);

    char** komenda = (char**)malloc(16 * sizeof(char*));
    int i;

    for (i = 0; i < 16; ++i)
    {
        komenda[i] = (char*)malloc(10 * sizeof(char));
    }

    strcpy(komenda[0], "NULL");
    strcpy(komenda[1], "STOP");
    strcpy(komenda[2], "LOAD");
    strcpy(komenda[3], "STORE");
    strcpy(komenda[4], "JUMP");
    strcpy(komenda[5], "JNEG");
    strcpy(komenda[6], "JZERO");
    strcpy(komenda[7], "0");
    strcpy(komenda[8], "ADD");
    strcpy(komenda[9], "SUB");
    strcpy(komenda[10], "SHL");
    strcpy(komenda[11], "SHR");
    strcpy(komenda[12], "AND");
    strcpy(komenda[13], "OR");
    strcpy(komenda[14], "NOT");
    strcpy(komenda[15], "XOR");

    char** adresowanie = (char**)malloc(4 * sizeof(char*));
    for (i = 0; i < 4; ++i)
    {
        adresowanie[i] = (char*)malloc(2 * sizeof(char));
    }

    strcpy(adresowanie[0], ".");
    strcpy(adresowanie[1], "@");
    strcpy(adresowanie[2], "*");
    strcpy(adresowanie[3], "+");


    for (j = 0; j < z; ++j)
    {
        unsigned short int M[513] = { 0 };

        int licz_op = 0;
        int ile_wynik = 0;
        short int IR = 0;
        short int OP = 0;
        short int AC = 0;
        short int PC = 0;
        unsigned short int liczba, il_roz, linia, adrs;
        scanf("%hd %d", &il_roz, &ile_wynik);
        int wynik[513] = { 0 };
        //wynik = malloc(ile_wynik*sizeof(int));
        char nic;

        for (i = 0; i < il_roz; ++i)
        {
            char* rozkaz = malloc(10 * sizeof(char));
            char* adr = malloc(2 * sizeof(char));

            scanf("%hd %c %s", &linia, &nic, &rozkaz[0]);
            if (rozkaz[0] < 'A')
            {
                liczba = (unsigned short int)atoi(rozkaz);
                strcpy(adr, ".");
                if (liczba < 0) {
                    M[linia] = 32768 + Liczba(liczba);
                }
                else M[linia] = liczba;

            }
            else
            {
                scanf("%s %hd", &adr[0], &liczba);
                M[linia] = Znak(liczba) + Rozkaz(szukaj_kom(rozkaz, komenda)) + Adresowanie(szukaj_adr(adr, adresowanie)) + Liczba(liczba);


            }
            char c;
            do
            {
                c = getc(stdin);
            } while (c != '\n' && c != EOF);


            //**********zakodowanie wczytywanych operacji************
            // M[linia] = Znak(liczba) + Rozkaz(szukaj_kom(rozkaz, komenda)) + Adresowanie(szukaj_adr(adr, adresowanie)) + Liczba(liczba);


            free(adr);
            free(rozkaz);
        }

        for (i = 0; i < ile_wynik; ++i)
        {
            scanf("%d", &wynik[i]);
        }

        for (PC = 0; PC < il_roz; ++PC)
        {
            //**************ROZKODOWANIE************************
            // pom - zmienna do odejmowania 1 z przodu
            IR = M[PC];

            unsigned short int pom = (M[PC] >> 15) << 15; // czyli 2^16
            unsigned short int roz = (M[PC] - pom) >> 11;
            short int l;
            //teraz pom jest tym co trzeba uciac od przodu zeby dostac adresowanie
            pom = (M[PC] >> 11) << 11;
            adrs = (M[PC] - pom) >> 9;
            //pom jest tym co trzeva uciac od przodu zeby dostac liczbe
            pom = (M[PC] >> 9) << 9;
            //jesli liczba jest DODATNIA
            if (roz == 1) {
                break;
            }

            unsigned short int znak = ((unsigned short int)IR >> 15) & 1;

            if (znak == 0)
            {
                l = M[PC] - pom;
            }
            else
            {
                //jesli liczba jest ujemna
                l = ~(M[PC] - 1);
                pom = (l >> 9) << 9;
                l = (-1) * (l - pom);
            }

            //**********OP**********
            if (adrs == 0)
            {
                OP = l;
            }
            else if (adrs == 1)
            {

                znak = (M[l] >> 15) & 1;
                if (znak == 1) {

                    unsigned short int w = ~(M[l] - 1);

                    OP = (-1) * (w - ((w >> 9) << 9));
                }
                else OP = M[l];
            }
            else if (adrs == 2)
            {
                znak = (M[M[l]] >> 15) & 1;
                if (znak == 1) {
                    unsigned short int w = ~(M[M[l]] - 1);
                    OP = (-1) * (w - ((w >> 9) << 9));
                }
                else
                    OP = (short int)M[M[l]];
            }
            else {
                znak = (M[AC + l] >> 15) & 1;
                if (znak == 1) {
                    unsigned short int w = ~(M[AC + l] - 1);
                    OP = (-1) * (w - ((w >> 9) << 9));
                }
                else OP = M[AC + l];
                OP = (short int)M[AC + l];
            }

            (*f[roz])(&IR, &PC, &AC, &OP, M);


        } // for i < licz_op

        for (i = 0; i < ile_wynik - 1; ++i)
        {
            printf("%hd ", (short int)M[wynik[i]]);
        }
        printf("%hd\n", (short int)M[wynik[ile_wynik - 1]]);


    } //z
    for (int i = 0; i < 16; ++i)
        free(komenda[i]);
    free(komenda);
    for (int i = 0; i < 4; ++i)
        free(adresowanie[i]);
    free(adresowanie);

    return 0;
}

// public test

// 48
// 18 1
// 0: LOAD . 1
// 1: STORE . 200
// 2: LOAD . 0
// 3: STORE . 300
// 4: LOAD @ 100
// 5: SUB @ 200
// 6: JNEG . 15
// 7: LOAD @ 200
// 8: LOAD + 100
// 9: ADD @ 300
// 10: STORE . 300
// 11: LOAD @ 200
// 12: ADD . 1
// 13: STORE . 200
// 14: JUMP . 4
// 15: STOP . 0
// 100: 1
// 200: 10
// 300

// 48
// 7 1
// 0: LOAD @ 10
// 1: JNEG . 4
// 2: ADD @ 10
// 3: STORE . 20
// 4: STOP . 0
// 10: -5
// 20: 20
// 20
// 7 1
// 0: LOAD @ 10
// 1: SUB . 5
// 2: JZERO . 4
// 3: STORE . 20
// 4: STOP . 0
// 10: 5
// 20: 20
// 20
// 11 1
// 0: LOAD @ 100
// 1: JZERO . 5
// 2: SHL . 1
// 3: STORE . 200
// 4: STOP . 0
// 5: ADD @ 200
// 6: SHR . 2
// 7: STORE . 200
// 8: STOP . 0
// 100: 5
// 200: 20
// 200
// 11 1
// 0: LOAD @ 100
// 1: JZERO . 5
// 2: SHL . 1
// 3: STORE . 200
// 4: STOP . 0
// 5: ADD @ 200
// 6: SHR . 2
// 7: STORE . 200
// 8: STOP . 0
// 100: 0
// 200: 20
// 200
// 11 2
// 0: LOAD @ 100
// 1: SUB . 1
// 2: STORE . 100
// 3: JNEG . 8
// 4: LOAD @ 200
// 5: ADD . 2
// 6: STORE . 200
// 7: JUMP . 0
// 8: STOP . 0
// 100: 5
// 200: 20
// 100 200
// 14 1
// 0: LOAD @ 100
// 1: SUB . 5
// 2: JZERO . 7
// 3: JNEG . 10
// 4: ADD @ 200
// 5: STORE . 100
// 6: STOP . 0
// 7: ADD . 1
// 8: STORE . 100
// 9: STOP . 0
// 10: ADD . 2
// 11: JUMP . 3
// 100: 5
// 200: 20
// 100
// 14 1
// 0: LOAD @ 100
// 1: SUB . 5
// 2: JZERO . 7
// 3: JNEG . 10
// 4: ADD @ 200
// 5: STORE . 100
// 6: STOP . 0
// 7: ADD . 1
// 8: STORE . 100
// 9: STOP . 0
// 10: ADD . 2
// 11: JUMP . 3
// 100: 0
// 200: 20
// 100
// 8 1
// 0: LOAD @ 100
// 1: ADD @ 200
// 2: ADD @ 300
// 3: STORE . 400
// 4: STOP . 0
// 100: 13
// 200: 23
// 300: 33
// 400
// 8 1
// 0: LOAD @ 100
// 1: ADD @ 200
// 2: ADD @ 300
// 3: STORE . 400
// 4: STOP . 0
// 100: 110
// 200: 220
// 300: 133
// 400
// 13 1
// 0: LOAD . 0
// 1: STORE . 102
// 2: LOAD @ 101
// 3: SUB . 1
// 4: JNEG . 10
// 5: STORE . 101
// 6: LOAD @ 100
// 7: ADD @ 102
// 8: STORE . 102
// 9: JUMP . 2
// 10: STOP . 0
// 100: 2
// 101: 1
// 102
// 13 1
// 0: LOAD . 0
// 1: STORE . 102
// 2: LOAD @ 101
// 3: SUB . 1
// 4: JNEG . 10
// 5: STORE . 101
// 6: LOAD @ 100
// 7: ADD @ 102
// 8: STORE . 102
// 9: JUMP . 2
// 10: STOP . 0
// 100: 0
// 101: 2
// 102
// 13 1
// 0: LOAD . 0
// 1: STORE . 102
// 2: LOAD @ 101
// 3: SUB . 1
// 4: JNEG . 10
// 5: STORE . 101
// 6: LOAD @ 100
// 7: ADD @ 102
// 8: STORE . 102
// 9: JUMP . 2
// 10: STOP . 0
// 100: 2
// 101: 0
// 102
// 13 1
// 0: LOAD . 0
// 1: STORE . 102
// 2: LOAD @ 101
// 3: SUB . 1
// 4: JNEG . 10
// 5: STORE . 101
// 6: LOAD @ 100
// 7: ADD @ 102
// 8: STORE . 102
// 9: JUMP . 2
// 10: STOP . 0
// 100: 2
// 101: 3
// 102
// 13 1
// 0: LOAD . 0
// 1: STORE . 102
// 2: LOAD @ 101
// 3: SUB . 1
// 4: JNEG . 10
// 5: STORE . 101
// 6: LOAD @ 100
// 7: ADD @ 102
// 8: STORE . 102
// 9: JUMP . 2
// 10: STOP . 0
// 100: 20
// 101: 5
// 102
// 20 2
// 0: LOAD . 0
// 1: STORE . 300
// 2: STORE . 400
// 3: LOAD @ 100
// 4: JZERO . 17
// 5: JNEG . 12
// 6: SUB @ 200
// 7: STORE . 100
// 8: LOAD @ 300
// 9: ADD . 1
// 10: STORE . 300
// 11: JUMP . 3
// 12: ADD @ 200
// 13: STORE . 400
// 14: LOAD @ 300
// 15: SUB . 1
// 16: STORE . 300
// 17: STOP . 0
// 100: 2
// 200: 1
// 300 400
// 20 2
// 0: LOAD . 0
// 1: STORE . 300
// 2: STORE . 400
// 3: LOAD @ 100
// 4: JZERO . 17
// 5: JNEG . 12
// 6: SUB @ 200
// 7: STORE . 100
// 8: LOAD @ 300
// 9: ADD . 1
// 10: STORE . 300
// 11: JUMP . 3
// 12: ADD @ 200
// 13: STORE . 400
// 14: LOAD @ 300
// 15: SUB . 1
// 16: STORE . 300
// 17: STOP . 0
// 100: 24
// 200: 3
// 300 400
// 20 2
// 0: LOAD . 0
// 1: STORE . 300
// 2: STORE . 400
// 3: LOAD @ 100
// 4: JZERO . 17
// 5: JNEG . 12
// 6: SUB @ 200
// 7: STORE . 100
// 8: LOAD @ 300
// 9: ADD . 1
// 10: STORE . 300
// 11: JUMP . 3
// 12: ADD @ 200
// 13: STORE . 400
// 14: LOAD @ 300
// 15: SUB . 1
// 16: STORE . 300
// 17: STOP . 0
// 100: 30
// 200: 7
// 300 400
// 20 2
// 0: LOAD . 0
// 1: STORE . 300
// 2: STORE . 400
// 3: LOAD @ 100
// 4: JZERO . 17
// 5: JNEG . 12
// 6: SUB @ 200
// 7: STORE . 100
// 8: LOAD @ 300
// 9: ADD . 1
// 10: STORE . 300
// 11: JUMP . 3
// 12: ADD @ 200
// 13: STORE . 400
// 14: LOAD @ 300
// 15: SUB . 1
// 16: STORE . 300
// 17: STOP . 0
// 100: 33
// 200: 6
// 300 400
// 20 2
// 0: LOAD . 0
// 1: STORE . 300
// 2: STORE . 400
// 3: LOAD @ 100
// 4: JZERO . 17
// 5: JNEG . 12
// 6: SUB @ 200
// 7: STORE . 100
// 8: LOAD @ 300
// 9: ADD . 1
// 10: STORE . 300
// 11: JUMP . 3
// 12: ADD @ 200
// 13: STORE . 400
// 14: LOAD @ 300
// 15: SUB . 1
// 16: STORE . 300
// 17: STOP . 0
// 100: 0
// 200: 7
// 300 400
// 19 1
// 0: LOAD . 0
// 1: STORE . 300
// 2: LOAD @ 200
// 3: JZERO . 16
// 4: AND . 1
// 5: JZERO . 9
// 6: LOAD @ 100
// 7: ADD @ 300
// 8: STORE . 300
// 9: LOAD @ 100
// 10: ADD @ 100
// 11: STORE . 100
// 12: LOAD @ 200
// 13: SHR . 1
// 14: STORE . 200
// 15: JUMP . 3
// 16: STOP . 0
// 100: 2
// 200: 1
// 300
// 19 1
// 0: LOAD . 0
// 1: STORE . 300
// 2: LOAD @ 200
// 3: JZERO . 16
// 4: AND . 1
// 5: JZERO . 9
// 6: LOAD @ 100
// 7: ADD @ 300
// 8: STORE . 300
// 9: LOAD @ 100
// 10: ADD @ 100
// 11: STORE . 100
// 12: LOAD @ 200
// 13: SHR . 1
// 14: STORE . 200
// 15: JUMP . 3
// 16: STOP . 0
// 100: 0
// 200: 1
// 300
// 19 1
// 0: LOAD . 0
// 1: STORE . 300
// 2: LOAD @ 200
// 3: JZERO . 16
// 4: AND . 1
// 5: JZERO . 9
// 6: LOAD @ 100
// 7: ADD @ 300
// 8: STORE . 300
// 9: LOAD @ 100
// 10: ADD @ 100
// 11: STORE . 100
// 12: LOAD @ 200
// 13: SHR . 1
// 14: STORE . 200
// 15: JUMP . 3
// 16: STOP . 0
// 100: 5
// 200: 0
// 300
// 19 1
// 0: LOAD . 0
// 1: STORE . 300
// 2: LOAD @ 200
// 3: JZERO . 16
// 4: AND . 1
// 5: JZERO . 9
// 6: LOAD @ 100
// 7: ADD @ 300
// 8: STORE . 300
// 9: LOAD @ 100
// 10: ADD @ 100
// 11: STORE . 100
// 12: LOAD @ 200
// 13: SHR . 1
// 14: STORE . 200
// 15: JUMP . 3
// 16: STOP . 0
// 100: 3
// 200: 8
// 300
// 19 1
// 0: LOAD . 0
// 1: STORE . 300
// 2: LOAD @ 200
// 3: JZERO . 16
// 4: AND . 1
// 5: JZERO . 9
// 6: LOAD @ 100
// 7: ADD @ 300
// 8: STORE . 300
// 9: LOAD @ 100
// 10: ADD @ 100
// 11: STORE . 100
// 12: LOAD @ 200
// 13: SHR . 1
// 14: STORE . 200
// 15: JUMP . 3
// 16: STOP . 0
// 100: 8
// 200: 3
// 300
// 19 1
// 0: LOAD . 0
// 1: STORE . 300
// 2: LOAD @ 200
// 3: JZERO . 16
// 4: AND . 1
// 5: JZERO . 9
// 6: LOAD @ 100
// 7: ADD @ 300
// 8: STORE . 300
// 9: LOAD @ 100
// 10: ADD @ 100
// 11: STORE . 100
// 12: LOAD @ 200
// 13: SHR . 1
// 14: STORE . 200
// 15: JUMP . 3
// 16: STOP . 0
// 100: 5
// 200: 7
// 300
// 19 1
// 0: LOAD . 0
// 1: STORE . 300
// 2: LOAD @ 200
// 3: JZERO . 16
// 4: AND . 1
// 5: JZERO . 9
// 6: LOAD @ 100
// 7: ADD @ 300
// 8: STORE . 300
// 9: LOAD @ 100
// 10: ADD @ 100
// 11: STORE . 100
// 12: LOAD @ 200
// 13: SHR . 1
// 14: STORE . 200
// 15: JUMP . 3
// 16: STOP . 0
// 100: 5
// 200: 10
// 300
// 17 1
// 0: LOAD @ 20
// 1: SUB . 10
// 2: JNEG @ 21
// 3: LOAD @ 20
// 4: ADD * 22
// 5: STORE @ 25
// 6: STOP . 0
// 7: LOAD @ 20
// 8: ADD . 5
// 9: STORE @ 25
// 10: JUMP @ 24
// 20: 20
// 21: 7
// 22: 23
// 23: 5
// 24: 1
// 25: 20
// 20
// 17 1
// 0: LOAD @ 20
// 1: SUB . 10
// 2: JNEG @ 21
// 3: LOAD @ 20
// 4: ADD * 22
// 5: STORE @ 25
// 6: STOP . 0
// 7: LOAD @ 20
// 8: ADD . 5
// 9: STORE @ 25
// 10: JUMP @ 24
// 20: 10
// 21: 7
// 22: 23
// 23: 5
// 24: 1
// 25: 20
// 20
// 17 1
// 0: LOAD @ 20
// 1: SUB . 10
// 2: JNEG @ 21
// 3: LOAD @ 20
// 4: ADD * 22
// 5: STORE @ 25
// 6: STOP . 0
// 7: LOAD @ 20
// 8: ADD . 5
// 9: STORE @ 25
// 10: JUMP @ 24
// 20: 3
// 21: 7
// 22: 23
// 23: 5
// 24: 1
// 25: 20
// 20
// 22 1
// 0: LOAD . 1
// 1: STORE . 200
// 2: LOAD . 0
// 3: STORE . 300
// 4: LOAD @ 100
// 5: SUB @ 200
// 6: JNEG . 15
// 7: LOAD @ 200
// 8: LOAD + 100
// 9: ADD @ 300
// 10: STORE . 300
// 11: LOAD @ 200
// 12: ADD . 1
// 13: STORE . 200
// 14: JUMP . 4
// 15: STOP . 0
// 100: 5
// 101: 1
// 102: 2
// 103: 3
// 104: 4
// 105: 50
// 300
// 22 1
// 0: LOAD . 1
// 1: STORE . 200
// 2: LOAD . 0
// 3: STORE . 300
// 4: LOAD @ 100
// 5: SUB @ 200
// 6: JNEG . 15
// 7: LOAD @ 200
// 8: LOAD + 100
// 9: ADD @ 300
// 10: STORE . 300
// 11: LOAD @ 200
// 12: ADD . 1
// 13: STORE . 200
// 14: JUMP . 4
// 15: STOP . 0
// 100: 4
// 101: 10
// 102: 20
// 103: 30
// 104: 40
// 105: 50
// 300