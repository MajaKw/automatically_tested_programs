#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

int good(string word, string key)
{
    int f = 0;
    int t = 1;
    int diff = 0;
    int i, j;
    int len_key = key.length();
    int len_word = word.length();

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
            word.at(j) = tolower(word.at(j));
            key.at(i) = tolower(key.at(i));

            if (key.at(i) != word.at(j))
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
            return t;
        }
        else
        {
            return f;
        }
    }
}

int main(int n, char** T)
{

    if (n < 4)
        return 0;

    fstream in;
    fstream out;
    in.open(T[1], ios::in);

    char possible[32];
    char ch;

    int i_pos = 0;
    int line = 1;
    int mode_com = 0;
    int in_word = 0;
    int specials = 0;
    int words = 0;
    int un = 0;
    int overfilled = 0;

    string key = T[3];
    memset(possible, 0, sizeof(char) * 32);

    if (!in.good())
        return 0;

    out.open(T[2], ios::out);
    if (!out.good())
        return 0;

    while (!in.eof())
    {
        un = 0;
        if (mode_com == 0)
        {
            // litera
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            {
                if (overfilled == 0)
                {
                    possible[i_pos] = tolower(ch);
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
                    int is_good = good(possible, key);
                    char temp = ch;
                    if (ch == '/')
                    {

                        in.get(ch);
                        if (ch == '*')
                        {
                            ++mode_com;
                            in.get(ch);
                            continue;
                        }
                        else
                        {
                            in.putback(ch);
                            un = 1;
                        }
                    }
                    if (is_good == 1)
                    {
                        out << "Linia " << line << ":  " << possible << endl;
                        ++words;
                        ++specials;
                    }
                    if (is_good == 0 && strlen(possible) != 0)
                    {
                        ++words;
                    }

                    memset(possible, 0, sizeof(char) * 32);
                    i_pos = 0;
                    in_word = 0;
                    if (temp == '\n' && un != 1)
                    {
                        ++line;
                    }
                }
            }
        } // mode_com
        else
        {

            char temp = ch;
            if (temp == '*')
            {
                in.get(ch);

                if (ch == '/')
                {
                    --mode_com;
                    in.get(ch);
                    continue;
                }
                else
                {
                    in.putback(ch);
                }
            }
            else if (temp == '/')
            {
                in.get(ch);

                if (ch == '*')
                {
                    ++mode_com;
                    in.get(ch);
                    continue;
                }
                else
                {
                    in.putback(ch);
                }
            }
        }
        in.get(ch);
    }
    out << "Wyrazy: " << words << endl;
    out << "Wyrazy specjalne: " << specials << endl;
    in.close();
    out.close();
}