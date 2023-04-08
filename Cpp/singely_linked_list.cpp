#include <iostream>
#include <cstring>
#include <cstddef>
using namespace std;

class monkey
{
private:
    string name;
    monkey* next;

public:
    monkey()
    {
        name = "";
        next = NULL;
    }
    monkey(string n)
    {
        name = n;
        next = NULL;
    }
    ~monkey()
    {
    }

    friend class list;
};

class list
{
private:
    monkey* head;

public:
    list()
    {
        head = NULL;
    }
    list(monkey* m)
    {
        head = m;
    }
    ~list()
    {
        while (head != NULL)
        {
            monkey* temp = head->next;
            delete head;
            head = temp;
        }
    }

    void front(string name)
    {
        monkey* young = new monkey(name);
        if (head == NULL)
        {
            head = young;
        }
        else
            young->next = head;
        head = young;
    }
    void back(string name)
    {
        monkey* young = new monkey(name);
        if (head == NULL)
        {
            head = young;
        }
        else
        {
            monkey* temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = young;
        }
    }

    void add(string name, int i)
    {
        int counter = 1;
        monkey* temp = head;
        monkey* prev;
        monkey* young = new monkey(name);

        if (head == NULL)
        {
            head = young;
            return;
        }
        else
        {
            if (i == 1)
            {
                young->next = head;
                head = young;
                return;
            }
            else
            {
                while (temp->next != NULL && counter < i - 1)
                {
                    temp = temp->next;
                    ++counter;
                }
                // jesli lista krotsza niz i dodaj malpke na koniec
                if (temp->next == NULL && counter < i - 1)
                {
                    temp->next = young;
                    return;
                }
                else
                {
                    prev = temp;
                    young->next = prev->next;
                    prev->next = young;
                }
            }
        }
    }

    void del(string name)
    {
        monkey* temp = head;
        if (head == NULL)
        {
            cout << "BLAD " << name << endl;
            return;
        }
        else if (head->name == name)
        {
            monkey* a = head->next;
            delete head;
            head = a;
            return;
        }
        else
        {
            while (temp->next != NULL && temp->next->name != name)
            {
                temp = temp->next;
            }
            if (temp->next == NULL)
            {
                cout << "BLAD " << name << endl;
                return;
            }
            else
            {
                monkey* a = temp->next->next;
                delete temp->next;
                temp->next = a;
            }
        }
    }

    // prev zawsze zwraca nie nulla np, pierwszy el
    monkey* prev(monkey* start, int i, int counter)
    {
        monkey* temp = start;
        while (temp->next != NULL && counter < i - 1)
        {
            temp = temp->next;
            ++counter;
        }
        return temp;
    }

    void change(int i, int j)
    {
        int counter = 1;

        if (i < j)
        {
            if (i == 1)
            {
                // search j
                monkey* temp = prev(head, j, 1);
                // j poza zakresem
                if (temp->next == NULL)
                {
                    temp->next = head;
                    head = head->next;
                    temp->next->next = NULL;
                    return;
                }
                // j ok
                else
                {
                    temp = temp->next;
                    monkey* help = temp->next;
                    temp->next = head;
                    head = head->next;
                    temp->next->next = help;
                    return;
                }
            }
            else
            {
                // search i.prev
                monkey* i_prev = prev(head, i, 1);
                // i poza zakresem
                if (i_prev->next == NULL)
                {
                    cout << "BLAD " << i << endl;
                    return;
                }
                else
                {
                    monkey* j_prev = prev(i_prev, j, i - 1);
                    // i ok j ok
                    if (j_prev->next != NULL)
                    {
                        monkey* j_next = j_prev->next->next;
                        monkey* i_next = i_prev->next->next;
                        j_prev->next->next = i_prev->next;
                        i_prev->next->next = j_next;
                        i_prev->next = i_next;
                        return;
                    }
                    else
                        // j poza zakresem
                    {
                        j_prev->next = i_prev->next;
                        i_prev->next = i_prev->next->next;
                        j_prev->next->next = NULL;
                        return;
                    }
                }
            }
        }
        else if (j < i)
        {
            if (j == 1)
            {
                monkey* i_prev = prev(head, i, 1);
                // i poza zakresem
                if (i_prev->next == NULL)
                {
                    cout << "BLAD " << i << endl;
                    return;
                }
                else
                    // i ok
                {
                    monkey* i_next = i_prev->next->next;
                    i_prev->next->next = head;
                    head = i_prev->next;
                    i_prev->next = i_next;
                    return;
                }
            }
            else
            {
                monkey* j_prev = prev(head, j, 1);
                // j poza zakresem
                if (j_prev->next == NULL)
                {
                    cout << "BLAD " << i << endl;
                    return;
                }
                else
                {
                    monkey* i_prev = prev(j_prev, i, j - 1);
                    if (i_prev->next == NULL)
                    {
                        cout << "BLAD " << i << endl;
                        return;
                    }
                    else
                    {
                        monkey* i_rly = i_prev->next;
                        monkey* i_next = i_prev->next->next;
                        i_prev->next->next = j_prev->next;
                        j_prev->next = i_rly;
                        i_prev->next = i_next;
                        return;
                    }
                }
            }
        }
        else if (i == j) {
            monkey* i_prev = prev(head, i, 1);
            if (i_prev->next == NULL) cout << "BLAD " << i << endl;
        }
    }
    void print()
    {
        // return;
        if (head == NULL)
        {
            cout << "PUSTY" << endl;
        }
        else
        {

            monkey* temp = head;
            do
            {
                cout << temp->name << " ";
                temp = temp->next;
            } while (temp != NULL);
            cout << endl;
        }
    }
    void clean()
    {
        while (head != NULL)
        {
            monkey* temp = head->next;
            delete head;
            head = temp;
        }
    }
    void reverse()
    {
        if (head != NULL && head->next != NULL)
        {
            monkey* prev = NULL;
            monkey* curr = head;
            monkey* next = NULL;
            while (curr != NULL)
            {
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            head = prev;
        }
    }
};
