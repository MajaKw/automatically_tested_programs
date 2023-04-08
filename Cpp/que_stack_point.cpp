#include <iostream>
#include <stdlib.h>
// using namespace std;
class point
{
private:
    int x;
    int y;

public:
    point();
    point(int, int);
    int getX();
    int getY();
    void print();
};

class queue
{
public:
    point* arr;
    int size;
    int rear;
    int first;

    queue();
    queue(int);
    ~queue();
    void enqueue(point&);
    point dequeue();
    point front();
    bool empty();
    bool full();
    void clear();
    void resize(int n);
};
class stack
{
public:
    long long int* arr;
    int size;
    int peak;
    stack();
    stack(int);
    ~stack();
    void push(long long int&);
    long long int pop();
    long long int top();
    bool empty();
    bool full();
    void clear();
    void resize(int);
};
queue::queue()
{
    size = 15;
    rear = -1;
    first = -1;
    arr = new point[size];
}
queue::queue(int s)
{
    rear = -1;
    first = -1;
    size = s;
    arr = new point[size];
}
queue ::~queue()
{
    delete[] arr;
}

void queue::enqueue(point& x)
{
    if (!(*this).full())
    {
        //pierwszy element dodany do kolejki
        if (first == -1)
        {
            first = 0;
        }
        rear = (rear + 1) % size;

        arr[rear] = x;
    }
}
point queue::dequeue()
{
    if ((*this).empty())
    {
        point a;
        return a;
    }
    else
    {
        point a = arr[first];
        if (first == rear)
        {
            // z kolejki zostal zdjety ostatni element
            first = -1;
            rear = -1;
        }
        else
        {
            first = (first + 1) % size;
        }
        return a;
    }
}
point queue::front()
{
    if (first != -1)
    {
        point a = arr[first];
        return a;
    }
    else
    {
        point a;
        return a;
    }
}
bool queue::empty()
{
    // cout<< first << " " << last <<endl;
    if (first == -1)
    {
        return true;
    }
    else
        return false;
}
bool queue::full()
{
    if (first == rear + 1)
    {
        return true;
    }
    if (first == 0 && rear == size - 1)
    {
        return true;
    }
    return false;
}
void queue::clear()
{
    rear = -1;
    first = -1;
}
void queue::resize(int n)
{
    int i, j;
    if (n > size)
    {
        // if is empty then just create
        point* new_arr = new point[n];
        if (first != -1)
        {
            i = 0;
            j = first;

            do
            {
                if (j == size)
                    j = 0;
                new_arr[i] = arr[j];
                ++j;
                ++i;
            } while (j != rear + 1);

            first = 0;
            rear = i - 1;
        }
        size = n;
        delete[] arr;
        arr = new_arr;
    }
}

stack::stack()
{
    peak = -1;
    size = 15;
    arr = new long long int[size];
}
stack::stack(int n)
{
    peak = -1;
    size = n;
    arr = new long long int[size];
}
stack ::~stack()
{
    delete[] arr;
}

void stack::push(long long int& x)
{
    if (peak < size - 1)
    {
        ++peak;
        arr[peak] = x;
    }
}
long long int stack::pop()
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
long long int stack::top()
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

int point::getX()
{
    return x;
}
int point::getY()
{
    return y;
}
void point::print()
{
    std::cout << x << " " << y << std::endl;
}
point::point()
{
    x = 0;
    y = 0;
}
point::point(int a, int b)
{
    x = a;
    y = b;
}
