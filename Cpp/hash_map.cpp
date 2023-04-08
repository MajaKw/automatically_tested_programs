#include <iostream>
#include <cstring>

using namespace std;

string toString(char* arr) {
    string str = "";
    for (int i = 0; i < 8; ++i) {
        str += arr[i];
    }
    return str;
}

class CAR {
public:
    char licensePlate[8];
    int penaltyPoints;

    CAR() {
        penaltyPoints = -2;
    }

    inline void toCharArray(const string& license) {
        for (int i = 0; i < 8; ++i) {
            licensePlate[i] = license[i];
        }
    }
};

class REGISTER {
public:
    CAR* car;
    int add; int del;
    int capacity = 8;
    const short int JUMP = 1;

    // states
    // 1 takenv -> cos
    // 0 used earlier -> -1
    // -1 never used -> -2

    REGISTER() {
        add = 0; del = 0;
        car = new CAR[capacity];
    }
    ~REGISTER() {
        delete[] car;
    }

    int hashMethod(const string& license) {
        long unsigned int hashCode = 1; int coefficient = 7; // 17 bylo za duze, jak bedzie problem to zrobic generator liczb pierwszych do liter
        for (int i = 0; i < 8; ++i) {
            if (license[i] > 64) {
                hashCode += coefficient * (license[i] - 64 + 10); // letter, tak by mialy inne biz digits
            }
            else hashCode += coefficient * (license[i] - 48); // digit
            coefficient *= coefficient;
        }
        int hashResult = hashCode % capacity;
        return hashResult;
    }

    void resize() {
        int COEFFICIENT = 8;
        del = 0;
        add = 0;
        CAR* new_car = new CAR[COEFFICIENT * capacity];
        int temp_capacity = capacity;
        capacity = COEFFICIENT * capacity;
        for (int i = 0; i < temp_capacity; ++i) {
            if (car[i].penaltyPoints != -1 && car[i].penaltyPoints != -2) {
                specialInsertToResize(car[i].licensePlate, car[i].penaltyPoints, new_car);
                ++add;
            }
        }
        delete[] car;
        car = new_car;
    }

    void specialInsertToResize(const string& license, int points, CAR* myCar) {
        int curr = hashMethod(license);
        while (myCar[curr].penaltyPoints != -2) {
            // check if this number already occured, but it is a copy so it is not possible
            curr = (curr + JUMP) % capacity;
        }
        myCar[curr].penaltyPoints = points;
        myCar[curr].toCharArray(license);
    }

    void insert(const string& license, int points) {

        if ((add - del) * 4 > 3 * capacity) resize();
        int curr = hashMethod(license);
        while (car[curr].penaltyPoints != -2) {
            // check if this number already occured
            if ((car[curr].penaltyPoints != -1 && car[curr].penaltyPoints != -2) && license == toString(car[curr].licensePlate)) {
                car[curr].penaltyPoints += points; // tu juz istnial wiec byl nieujemny
                return;
            }
            curr = (curr + JUMP) % capacity;
        }
        if (car[curr].penaltyPoints == -1) --del;
        ++add;
        // initalize car
        car[curr].penaltyPoints = points;
        car[curr].toCharArray(license);
    }

    CAR delet(const string& license) {
        int curr = hashMethod(license);
        while (car[curr].penaltyPoints != -2) {
            if ((car[curr].penaltyPoints != -1 && car[curr].penaltyPoints != -2) && license == toString(car[curr].licensePlate)) {
                ++del;
                CAR temp = car[curr];
                car[curr].penaltyPoints = -1; // used before
                return temp;
            }
            curr = (curr + JUMP) % capacity;
        }

        string err = "ERROR";
        throw err;
    }

    int find(const string& license) {
        int curr = hashMethod(license);
        while (car[curr].penaltyPoints != -2) {
            if ((car[curr].penaltyPoints != -1 && car[curr].penaltyPoints != -2) && license == toString(car[curr].licensePlate)) {
                return car[curr].penaltyPoints;
            }
            curr = (curr + JUMP) % capacity;
        }
        return 0;
    }
};


int main() {
    ios_base::sync_with_stdio(false);

    int n, z;
    cin >> z;
    while (z-- > 0) {

        string command, license;
        int points;

        cin >> n;
        REGISTER regst;
        for (int i = 0; i < n; ++i) {

            cin >> command >> license;
            if (command == "INSERT") {
                cin >> points;
                regst.insert(license, points);
                continue;
            }
            if (command == "DELETE") {
                try {
                    CAR temp;
                    temp = regst.delet(license);
                    cout << toString(temp.licensePlate) << " " << temp.penaltyPoints << endl;
                }
                catch (string error) {
                    cout << error << endl;
                }
                continue;
            }
            if (command == "FIND") {
                int temp = regst.find(license);
                cout << temp << endl;
            }

        }
    }// while z
}
