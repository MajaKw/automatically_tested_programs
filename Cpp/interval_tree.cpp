#include<iostream>
#include<vector>

using namespace std;

class NODE {
public:
    int begin;
    int end;
    int taken_seats;
    NODE() {
        begin = 0;
        end = 0;
        taken_seats = 0;
    }
};

bool add(vector<NODE>& tree, int index, int power_of_2) {
    //    cout << "-------------------- RESERVE ---------------------" << endl;
    int layer = power_of_2;
    int pos = power_of_2 + index - 1;
    if (tree[pos].taken_seats == 1) return false;
    while (layer > 0) {
        ++tree[pos].taken_seats;
        pos >>= 1;
        layer >>= 1;
    }
    return true;
}

bool delet(vector<NODE>& tree, int index, int power_of_2) {
    int layer = power_of_2;
    int pos = power_of_2 + index - 1;
    if (tree[pos].taken_seats == 0) return false;
    while (layer > 0) {
        --tree[pos].taken_seats;
        pos >>= 1;
        layer >>= 1;
    }
    return true;
}

inline bool intersection(vector<NODE>& tree, int left, int right, int pos) {
    if (tree[pos].end > left and tree[pos].end < right and tree[pos].begin < left) return true;
    if (tree[pos].begin < right and tree[pos].begin > left and tree[pos].end > right) return true;
    return false;
}

int sum(vector<NODE>& tree, int left, int right, int pos, int suma) {
    if (tree[pos].begin >= left and tree[pos].end <= right) {
        suma += tree[pos].taken_seats;
        return suma;
    }
    else if (right < tree[pos].begin or tree[pos].end < left) {
        return suma;
    }
    else {
        // recursively  to left child
        suma = sum(tree, left, right, 2 * pos, suma);
        // recursively  to right child
        suma = sum(tree, left, right, 2 * pos + 1, suma);
        return suma;
    }
}

void print(vector<NODE>& tree) {
    int power_of_two = 1;
    for (int i = 1; i < tree.capacity(); ++i) {
        cout << "[" << tree[i].begin << ", " << tree[i].end << "] ";
        if (i == power_of_two) {
            power_of_two <<= 1;
            cout << endl;
        }
    }
}

void fillParents(vector<NODE>& tree, int power_of_2, int n) {
    int layer = power_of_2;
    while (layer > 1) {
        for (int leaf = layer; leaf < 2 * layer; leaf = leaf + 2) {
            int pos = leaf;
            int pre_pos = leaf;
            pos >>= 1;
            tree[pos].begin = tree[pre_pos].begin;
            tree[pos].end = tree[pre_pos + 1].end; if (tree[pre_pos + 1].end == 0) tree[pos].end = tree[pre_pos].end;
            pre_pos = pos;
        }
        layer >>= 1;
    }
    tree[1].begin = 1; tree[1].end = n;
}

int main() {
    int z;
    cin >> z;
    while (z-- > 0) {
        int n, instr;
        cin >> n >> instr;

        // wyliczam pozycje liscia
        int power_of_2 = 1;
        while (power_of_2 < n) power_of_2 <<= 1;
        int capacity = power_of_2 << 1;
        vector<NODE> tree(capacity);
        // numerowanie od 1
        int iter = 0;
        for (int i = power_of_2; i < power_of_2 + n; ++i) {
            ++iter;
            tree[i].begin = iter;
            tree[i].end = iter;
        }

        fillParents(tree, power_of_2, n);
        string command;
        int index_1;
        int index_2;
        bool success;
        for (int i = 0; i < instr; ++i) {
            cin >> command >> index_1;
            if (command == "RESERVE") {
                success = add(tree, index_1, power_of_2);
                if (!success) cout << "ERROR" << endl;
                continue;
            }
            if (command == "CANCEL") {
                success = delet(tree, index_1, power_of_2);
                if (!success) cout << "ERROR" << endl;
                continue;
            }
            if (command == "SUM") {
                cin >> index_2;
                cout << sum(tree, index_1, index_2, 1, 0) << endl;
            }
            if (command == "MAX") {
                cin >> index_2;
                continue;
            }
            if (command == "NXT") {

            }
        }
        tree.clear();
    } // while
}