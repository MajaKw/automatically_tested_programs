#include <iostream>
// #include <vector>

using namespace std;

struct node {
    int left;
    int right;

    node(int left = 0, int right = 0) {
        this->left = left;
        this->right = right;
    }
};

class vector
{
private:
    node* tab;
    int capacity;
    int size;

public:
    ~vector() {
        delete[] tab;
    }
    vector(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        tab = new node[capacity];
    }
    void push_back(node x)
    {
        tab[size] = x;
        ++size;
    }
    node* at(int i) {
        return (tab + i);
    }

};

void dwyerPrint(vector& tree, int start) {
    int curr = start; int prev = -1;
    while (curr != -1) {

        cout << curr << " ";

        int i = curr; int left;
        do {
            left = tree.at(i)->left;
            tree.at(i)->left = tree.at(i)->right;
            tree.at(i)->right = prev;
            prev = left;
        } while (left == 0);

        curr = left;
        prev = i;

    }
}

int main() {

    int z; cin >> z;
    for (int x = 0; x < z; ++x) {
        int n;
        int root, left, right;
        cin >> n >> root;
        vector tree(n + 1);
        node zero_problem(-1, -1);
        tree.push_back(zero_problem);
        for (int i = 0; i < n; ++i) {
            cin >> left >> right;
            node vertex(left, right);
            tree.push_back(vertex);
        }
        dwyerPrint(tree, root);

        cout << endl;

    } // zestawy
}