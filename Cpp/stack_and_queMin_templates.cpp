#include <iostream>

using namespace std;

// ###################       STACK    ########################

template<typename T>
class myPair {
public:
    T first;
    T second;
};

template <typename T, class Cmp>
class stackMin {
private:
    int size;
    int peak;
    T* minimum;
    T* arr;
public:
    stackMin(int a = 4) {
        size = a;
        peak = -1;
        minimum = new T[size];
        arr = new T[size];
    }
    ~stackMin() {
        // cout << "DESTRUKTOR STACK" << endl;
        delete[] minimum;
        delete[] arr;
    }

    bool empty() {
        return peak < 0 ? true : false;
    }

    T top() {
        return arr[peak];
    }

    void push(T item) {
        //stos pełny -> zwieksz obie tablice
        if (peak >= size - 1) {
            T* new_arr = new T[2 * size];
            T* new_minimum = new T[2 * size];
            for (int i = 0; i < size; ++i) {
                new_arr[i] = arr[i];
                new_minimum[i] = minimum[i];
            }
            size = 2 * size;
            delete[] arr;
            delete[] minimum;
            arr = new_arr;
            minimum = new_minimum;
        }
        if (this->empty()) {
            ++peak;
            arr[peak] = item;
            minimum[peak] = item;
        }
        else {
            T top_value = minimum[peak];
            ++peak;
            arr[peak] = item;
            Cmp object;
            if (object(item, top_value)) {
                minimum[peak] = item;
            }
            else
                minimum[peak] = top_value;
        }
    }

    void clear() {
        peak = -1;
    }

    bool pop() {
        if (this->empty()) {
            return false;
        }
        else {
            --peak;
            return true;
        }
    }

    T min() {
        return minimum[peak];
    }
};


template <typename T, class Cmp>
void solveStack(stackMin<T, Cmp>& S, int n) {
    for (int i = 0; i < n; ++i) {
        string instruction;
        cin >> instruction;

        if (instruction == "push") {
            // cout << "push" << endl;

            T item;
            cin >> item;
            S.push(item);
            continue;
        }
        if (instruction == "pop") {
            // cout << "pop" << endl;

            if (S.empty()) {
                cout << "ERROR" << endl;
                S.pop();
            }
            else {
                cout << S.top() << endl;
                S.pop();
            }
            continue;
        }
        if (instruction == "top") {
            // cout << "top" << endl;


            if (S.empty()) {
                cout << "EMPTY" << endl;
            }
            else {
                cout << S.top() << endl;
            }
            continue;
        }
        if (instruction == "min") {
            // cout << "min" << endl;


            if (S.empty()) {
                cout << "EMPTY" << endl;
            }
            else {
                cout << S.min() << endl;
            }
            continue;
        }
        if (instruction == "clear") {
            // cout << "clear" << endl;

            S.clear();
            continue;
        }
        if (instruction == "empty") {
            // cout << "push" << endl;

            if (S.empty()) {
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }
            continue;
        }
    } // for
}

// ###################     QUEUE   ########################
template<typename T>
class queue {
public:
    T* arr;
    int size;
    int rear;
    int first;


    queue() {
        rear = -1;
        first = -1;
        size = 4;
        arr = new T[size];
    }

    queue(int s) {
        rear = -1;
        first = -1;
        size = s;
        arr = new T[size];
    }
    ~queue() {
        delete[] arr;
    }

    void push(T item) {
        int i, j;
        if (this->full()) {
            T* new_arr = new T[2 * size];
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
            size = 2 * size;
            delete[] arr;
            arr = new_arr;
        }
        if (first == -1) {
            first = 0;
        }
        rear = (rear + 1) % size;

        arr[rear] = item;
    }

    void pop_back() {
        if (first == rear) {
            // z kolejki zostal zdjety ostatni element
            first = -1;
            rear = -1;
        }
        else {
            if (rear == 0) {
                rear = size - 1;
            }
            else
                --rear;
        }
    }

    void pop_front() {
        if (first == rear) {
            // z kolejki zostal zdjety ostatni element
            first = -1;
            rear = -1;
        }
        else {
            first = (first + 1) % size;
        }
    }

    T front() {
        return arr[first];
    }

    T back() {
        return arr[rear];
    }

    bool empty() {
        if (first == -1) { return true; }
        else return false;
    }

    void clear() {
        rear = -1;
        first = -1;
    }

    bool full() {
        if (first == rear + 1) {
            return true;
        }
        if (first == 0 && rear == size - 1) {
            return true;
        }
        return false;
    }

    void resize(int s) {
        size = s;
        T* new_arr = new T[size];
        delete[] arr;
        arr = new_arr;
    }
};



// ###################     QUEUE  MIN  ########################

template<typename T, class Cmp>
class queueMin {
    queue <T> Q;
    queue <T> D;

public:
    queueMin(int s = 4) {
        if (s != 4) {
            Q.resize(s);
        }
    }
    void enqueue(T item) {
        Q.push(item);
        Cmp object;
        bool check;
        if (D.empty()) {
            check = false;
        }
        else
            check = object(item, D.back());


        while (!D.empty() && check) {
            D.pop_back();
            if (D.empty()) {
                check = false;
            }
            else
                check = object(item, D.back());
        }
        D.push(item);
    }

    bool dequeue() {
        if (Q.empty()) {
            return false;
        }
        else {
            if (D.front() == Q.front())
                D.pop_front();
            Q.pop_front();
            return true;
        }
    }

    T front() {
        return Q.front();
    }

    T min() {
        return D.front();
    }

    bool empty() {
        return Q.empty();
    }

    void clear() {
        Q.clear();
        D.clear();
    }

    void print() {
        int i = Q.first;
        cout << "size: " << Q.size << endl;
        cout << "first: " << Q.first << endl;
        cout << "rear: " << Q.rear << endl;
    }
};

template <typename T, class Cmp>
void solveQueue(queueMin<T, Cmp>& S, int n) {
    for (int i = 0; i < n; ++i) {
        string instruction;
        cin >> instruction;

        if (instruction == "enqueue") {

            T item;
            cin >> item;
            S.enqueue(item);
            continue;
        }
        if (instruction == "dequeue") {

            if (S.empty()) {
                cout << "ERROR" << endl;
            }
            else {
                cout << S.front() << endl;
                S.dequeue();
            }
            continue;
        }
        if (instruction == "front") {

            if (S.empty()) {
                cout << "EMPTY" << endl;
            }
            else
                cout << S.front() << endl;
            continue;
        }
        if (instruction == "min") {

            if (S.empty()) {
                cout << "EMPTY" << endl;
            }
            else
                cout << S.min() << endl;
            continue;
        }
        if (instruction == "clear") {

            S.clear();
            continue;
        }
        if (instruction == "empty") {

            if (S.empty()) {
                cout << "YES" << endl;
            }
            else
                cout << "NO" << endl;
        }


    }
}

