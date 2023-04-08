#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int good(char* word, char* key)
{
    int false = 0;
    int true = 1;
    int diff = 0;
    int i, j;
    int len_key = strlen(key);
    int len_word = strlen(word);

    if (len_key != len_word && len_key != len_word + 1 && len_key != len_word - 1)
    {
        return false;
    }
    else
    {
        int smaller = len_key <= len_word ? len_key : len_word;
        j = 0;
        i = 0;
        while (i < len_key && j < len_word)
        {
            word[j] = tolower(word[j]);
            key[i] = tolower(key[i]);

            if (key[i] != word[j])
            {
                if (len_word > len_key)
                {
                    ++j;
                }
                else if (len_word < len_key)
                {
                    ++i;
                }
                else
                {
                    ++i;
                    ++j;
                }
                ++diff;
                if (diff > 1)
                    break;
            }
            else
            {
                ++i;
                ++j;
            }
        }
        if (diff <= 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int main(int n, char* T[])
{
    if (n < 4)
        return 0;

    FILE* in;
    FILE* out;
    in = fopen(T[1], "r");

    char possible[32];
    memset(possible, 0, sizeof(char) * 32);

    int i_pos = 0;
    int line = 1;
    int mode_com = 0;
    int in_word = 0;
    int specials = 0;
    int words = 0;

    int un = 0;
    int overfilled = 0;

    if (in == NULL)
        return 0;

    out = fopen(T[2], "w");
    if (out == NULL)
        return 0;

    char ch;
    while ((ch = getc(in)) != EOF)
    {
        un = 0;
        if (mode_com == 0)
        {
            // litera
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            {
                if (overfilled == 0)
                {
                    possible[i_pos] = ch;
                    ++i_pos;
                    if (in_word == 0)
                        ++in_word;
                    if (i_pos == 32)
                        overfilled = 1;
                }
            }
            else
            {
                // cyfra
                if (ch >= '0' && ch <= '9' && in_word == 1)
                {
                    if (overfilled == 0)
                    {
                        possible[i_pos] = ch;
                        ++i_pos;
                        if (i_pos == 32)
                            overfilled = 1;
                    }
                }
                else
                    // jesli nie jestesmy w slowie, a to cyfra to traktujemy ja jak znak
                {
                    overfilled = 0;
                    int is_good = good(possible, T[3]);
                    if (ch == '/')
                    {
                        ch = getc(in);
                        if (ch == '*')
                        {
                            ++mode_com;
                            continue;
                        }
                        else
                        {
                            ungetc(ch, in);
                            un = 1;
                        }
                    }
                    if (is_good == 1)
                    {
                        fprintf(out, "Linia %d: %s\n", line, possible);
                        ++words;
                        ++specials;
                    }
                    if (is_good == 0 && strlen(possible) != 0)
                    {
                        ++words;
                    }
                    printf("%d %s\n", words, possible);

                    memset(possible, 0, sizeof(char) * 32);
                    i_pos = 0;
                    in_word = 0;
                    if (ch == '\n' && un != 1)
                    {
                        ++line;
                    }
                }
            }
        } // mode_com
        else
        {
            if (ch == '*')
            {
                ch = getc(in);
                if (ch == '/')
                {
                    --mode_com;
                }
                else
                {
                    ungetc(ch, in);
                }
            }
            else if (ch == '/')
            {
                ch = getc(in);
                if (ch == '*')
                {
                    ++mode_com;
                }
                else
                {
                    ungetc(ch, in);
                }
            }
        }
    }
    fprintf(out, "Wyrazy: %d\n", words);
    fprintf(out, "Wyrazy specjalne: %d\n", specials);
    fclose(in);
    fclose(out);
}