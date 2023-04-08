#include <iostream>
#include <string>

using namespace std;

class vector
{
private:
    string* tab;
    int capacity;
    int size;

public:
    vector(int max = 4, int first = 0, string c = "")
    {
        capacity = max;
        size = first;
        tab = new string[capacity];
        for (int i = 0; i < size; ++i)
        {
            tab[i] = c;
        }
    }
    vector(const vector& A)
    {
        capacity = A.capacity;
        size = A.size;
        tab = new string[capacity];
        for (int i = 0; i < size; ++i)
        {
            tab[i] = A.tab[i];
        }
    }
    ~vector()
    {
        delete[] tab;
    }
    void add(string x)
    {

        if (size == capacity)
        {

            this->x2();
        }
        tab[size] = x;
        ++size;
    }
    void x2()
    {
        capacity = 2 * capacity;
        string* new_tab = new string[capacity];
        for (int i = 0; i < size; ++i)
        {
            new_tab[i] = tab[i];
        }
        delete[] tab;
        tab = new_tab;
    }
    int getSize()
    {
        return size;
    }
    void clear()
    {
        size = 0;
    }

    string& operator[](int index)
    {
        if (index > size - 1)
        {
            return tab[size - 1];
        }
        else
            return tab[index];
    }
    void operator=(const vector& A)
    {
        if (capacity != A.capacity)
        {
            capacity = A.capacity;
            string* new_tab = new string[capacity];
            for (int i = 0; i < A.size; ++i)
            {
                new_tab[i] = A.tab[i];
            }
            delete[] tab;
            tab = new_tab;
            size = A.size;
        }
        else
        {
            for (int i = 0; i < A.size; ++i)
            {
                tab[i] = A.tab[i];
            }
            size = A.size;
        }
    }

    // niepusty vector
    operator bool()
    {
        return (size != 0);
    }
    // pusty
    bool operator!()
    {
        return (size == 0);
    }
    void resize(int s)
    {
        if (s < size)
        {
            size = s;
        }
        else
        {
            this->x2();
            for (int i = size; i < s; ++i)
            {
                tab[i] = "";
            }
            size = s;
        }
    }
    void insert(int index, string x)
    {
        if (index <= size)
        {
            if (capacity == size)
            {
                this->x2();
            }
            if (index == size)
            {
                tab[size] = x;
                ++size;
            }
            else
            {
                for (int i = size; i > index; --i)
                {
                    tab[i] = tab[i - 1];
                }
                tab[index] = x;
                ++size;
            }
        }
    }
    void erase(int index)
    {
        if (index < size)
        {
            if (index == size - 1)
            {
                --size;
            }
            else
            {
                for (int i = index; i < size - 1; ++i)
                {
                    tab[i] = tab[i + 1];
                }
                --size;
            }
        }
    }

    friend ostream& operator<<(ostream& out, const vector& A);
    friend istream& operator>>(istream& in, const vector& A);
};

ostream& operator<<(ostream& out, const vector& A)
{
    for (int i = 0; i < A.size; ++i)
    {
        out << A.tab[i] << " ";
    }
    return out;
}
istream& operator>>(istream& in, const vector& A)
{
    for (int i = 0; i < A.size; ++i)
    {
        in >> A.tab[i];
    }
    return in;
}

