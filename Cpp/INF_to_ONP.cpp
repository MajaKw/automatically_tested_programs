#include <iostream>
#include <string>

using namespace std;

class stack
{
public:
    char* arr;
    int size;
    int peak;
    stack();
    stack(int);
    ~stack();
    void push(char&);
    char pop();
    char top();
    bool empty();
    bool full();
    void clear();
    void resize(int);
};
stack::stack()
{
    peak = -1;
    size = 15;
    arr = new char[size];
}
stack::stack(int n)
{
    peak = -1;
    size = n;
    arr = new char[size];
}
stack ::~stack()
{
    delete[] arr;
}

void stack::push(char& x)
{
    if (peak < size - 1)
    {
        ++peak;
        arr[peak] = x;
    }
}

char stack::pop()
{
    if (peak < 0)
    {
        return 0;
    }
    else
    {
        char a = arr[peak];
        --peak;
        return a;
    }
}
char stack::top()
{
    if (peak < 0)
    {
        return 0;
    }
    else
    {
        char a = arr[peak];
        return a;
    }
}
bool stack::empty()
{
    if (peak < 0)
    {
        return true;
    }
    else
        return false;
}
bool stack::full()
{
    if (peak >= size - 1)
    {
        return true;
    }
    else
        return false;
}
void stack::clear()
{
    peak = -1;
}
void stack::resize(int n)
{
    if (n >= size)
    {
        char* new_arr = new char[n];
        if (n > size)
        {
            for (int i = 0; i < size; ++i)
            {
                new_arr[i] = arr[i];
            }
            size = n;
            delete[] arr;
            arr = new_arr;
        }
    }
}

int priority(char c)
{
    int priority;
    if (c == '+' || c == '-')
    {
        priority = 1;
    }
    else if (c == '*' || c == '/')
    {
        priority = 2;
    }
    else if (c == '^')
    {
        priority = 3;
    }
    else if (c == '(')
    {
        priority = 0;
    }
    return priority;
}

class Lstack
{
public:
    long long int* arr;
    int size;
    int peak;
    Lstack();
    Lstack(int);
    ~Lstack();
    void push(long long int&);
    long long int pop();
    long long int top();
    bool empty();
    bool full();
    void clear();
    void resize(int);
};
Lstack::Lstack()
{
    peak = -1;
    size = 15;
    arr = new long long int[size];
}
Lstack::Lstack(int n)
{
    peak = -1;
    size = n;
    arr = new long long int[size];
}
Lstack ::~Lstack()
{
    delete[] arr;
}

void Lstack::push(long long int& x)
{
    if (peak < size - 1)
    {
        ++peak;
        arr[peak] = x;
    }
}
long long int Lstack::pop()
{
    if (peak < 0)
    {
        return 0;
    }
    else
    {
        long long int a = arr[peak];
        --peak;
        return a;
    }
}
long long int Lstack::top()
{
    if (peak < 0)
    {
        return 0;
    }
    else
    {
        long long int a = arr[peak];
        return a;
    }
}
bool Lstack::empty()
{
    if (peak < 0)
    {
        return true;
    }
    else
        return false;
}
bool Lstack::full()
{
    if (peak >= size - 1)
    {
        return true;
    }
    else
        return false;
}
void Lstack::clear()
{
    peak = -1;
}
void Lstack::resize(int n)
{
    if (n >= size)
    {
        long long int* new_arr = new long long int[n];
        if (n > size)
        {
            for (int i = 0; i < size; ++i)
            {
                new_arr[i] = arr[i];
            }
            size = n;
            delete[] arr;
            arr = new_arr;
        }
    }
}

long long int Pow(long long int x, long long int y)
{
    int value = x;
    for (int i = 1; i < y; ++i)
    {
        value = value * x;
    }
    return value;
}

int main()
{

    int z, n;
    cin >> z;

    for (int k = 0; k < z; ++k)
    {
        int a[26];

        for (int i = 0; i < 26; ++i)
        {
            cin >> a[i];
        }
        cin >> n;
        stack s(100000);
        Lstack result(100000);
        getchar();

        for (int w = 0; w < n; ++w)
        {
            // ************************* INF to ONP *****************************************
            char* out = new char[100001];

            int i = 0;
            int wynik = 0;

            char ch;
            int top_prio = -1;
            do
            {
                ch = getchar();
                if (ch != '\n' && ch != EOF)
                {
                    if (int(ch) >= 97 && ch != '^')
                    {
                        out[i++] = ch;
                    }
                    else
                    {

                        if (ch == '(')
                        {
                            s.push(ch);
                            top_prio = priority(s.top());
                        }
                        else if (ch == ')')
                        {
                            do
                            {
                                if (s.top() == '(')
                                {
                                    s.pop();
                                }
                                else
                                    out[i++] = s.pop();
                            } while (!s.empty() && s.top() != '(');
                            s.pop();
                            if (s.empty())
                            {
                                top_prio = -1;
                            }
                            else
                                top_prio = priority(s.top());
                        }
                        else
                        {
                            int prio = priority(ch);
                            if (prio > top_prio)
                            {
                                s.push(ch);
                                top_prio = priority(s.top());
                            }
                            else if (prio <= top_prio)
                            {
                                while (!s.empty() && prio <= top_prio)
                                {
                                    out[i++] = s.pop();
                                    if (s.empty())
                                    {
                                        top_prio = -1;
                                    }
                                    else
                                        top_prio = priority(s.top());
                                }
                                s.push(ch);
                                top_prio = priority(s.top());
                            }
                        }
                    }
                }
                else
                {
                    while (!s.empty())
                    {
                        out[i++] = s.pop();
                    }
                }


            } while (ch != EOF && ch != '\n');
            out[i] = 0;

            cout << out << endl;

            //**************************************** VALUE *********************************************

            int j = 0;
            long long int value = 0;

            do
            {
                if ((int)(out[j]) >= 97 && out[j] != '^')
                {
                    long long int temp = (long long int)a[(int)(out[j++]) - 97];
                    result.push(temp);
                }
                else
                {
                    long long int x, y;
                    y = result.pop();
                    x = result.pop();
                    if (out[j] == '+')
                    {
                        value = x + y;
                    }
                    else if (out[j] == '-')
                    {
                        value = x - y;
                    }
                    else if (out[j] == '*')
                    {
                        value = x * y;
                    }
                    else if (out[j] == '/')
                    {
                        if (y == 0)
                        {
                            value = 0;
                        }
                        else
                            value = x / y;
                    }
                    else if (out[j] == '^')
                    {
                        if (y <= 0)
                        {
                            value = 1;
                        }
                        else
                        {
                            value = Pow(x, y);
                        }
                    }

                    ++j;
                    result.push(value);
                }
            } while (j != i);
            cout << result.top() << endl;
            result.clear();
            s.clear();
            delete[] out;
        } // w
    }     // z
}