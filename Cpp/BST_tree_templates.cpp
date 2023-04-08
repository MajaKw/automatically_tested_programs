#include<iomanip>
#include<iostream>
using namespace std;

template <class T1, class T2>
class node;

template <class T1, class T2>
ostream& operator<< (ostream& out, const node<T1, T2>& item);

template <class T1, class T2>
class node {
public:
    node <T1, T2>* left;
    node <T1, T2>* right;
    T1 key; T2 value;
    node() {
        left = nullptr;
        right = nullptr;
    }
    node(T1 k) {
        key = k;
        left = nullptr;
        right = nullptr;
    }
    node(T1 k, T2 v) {
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
    }
    T2 GetName() {
        return value;
    }

    friend ostream& operator<< <> (ostream& out, const node<T1, T2>& item);
};

template <class T1, class T2>
ostream& operator<< (ostream& out, const node<T1, T2>& item) {
    out << setw(9) << setfill('0') << item.key << " " << item.value << endl;
    return out;
}

template <class T1, class T2>
class map {
public:
    node <T1, T2>* root;
    map() {
        root = nullptr;
    }

    int test(T1 a, T1 b) {
        return -1;
    }
    node<T1, T2>* select(int k) {
        return nullptr;
    }

    node<T1, T2>* find(T1 key) {
        if (root == nullptr) return nullptr;
        node <T1, T2>* curr = root;
        while (curr != nullptr) {
            if (key < curr->key) {
                curr = curr->left;
            }
            else if (key > curr->key) {
                curr = curr->right;
            }
            else return curr;
        }
        return nullptr;
    }

    T2& operator[] (T1 key) {
        if (root == nullptr) {
            node <T1, T2>* add = new node <T1, T2>(key);
            root = add;
            return add->value;
        }
        node <T1, T2>* curr = root;
        node <T1, T2>* prev;
        while (curr != nullptr) {
            prev = curr;
            if (key < curr->key) {
                curr = curr->left;
            }            
else if (key > curr->key) {
                curr = curr->right;
            }
            else return curr->value;
        }
        node <T1, T2>* add = new node <T1, T2>(key);
        if (key < prev->key) {
            prev->left = add;
        }
        else {
            prev->right = add;
        }
        return add->value;
    }

    node<T1, T2>* recursiveDelete(node<T1, T2>* vertex, T1 data) {
        if (vertex == nullptr) {
            return nullptr;
        }
        T1 key_vertex = vertex->key;
        if (data < key_vertex) vertex->left = recursiveDelete(vertex->left, data);
        if (data > key_vertex) vertex->right = recursiveDelete(vertex->right, data);

        if (key_vertex == data) {
            int arity = children(vertex);
            if (arity == 0) {
                if (vertex == root) root = nullptr;
                delete vertex;
                return nullptr;
            }
            if (arity == 1) {
                bool hasLeftChild = false; bool hasRightChild = false;
                if (vertex->left) hasLeftChild = true; if (vertex->right) hasRightChild = true;
                if (hasLeftChild) {
                    node<T1, T2>* left_child = vertex->left;
                    if (vertex == root) root = left_child;
                    delete vertex;
                    return left_child;
                }
                if (hasRightChild) {
                    node<T1, T2>* right_child = vertex->right;
                    if (vertex == root) root = right_child;
                    delete vertex;
                    return right_child;
                }
            }
            if (arity == 2) {
                node<T1, T2>* max_value = findMaxValue(vertex);
                // initiallize using max_value
                vertex->key = max_value->key;
                vertex->value = max_value->value;
                data = vertex->key;
                vertex->left = recursiveDelete(vertex->left, data);
            }
        }
        return vertex;
    }

    inline node<T1, T2>* findMaxValue(node<T1, T2>* vertex) {
        node<T1, T2>* max_value = vertex->left;
        while (max_value->right) max_value = max_value->right;
        return max_value;
    }

    bool delet(T1 key) {
        node<T1, T2>* temp = find(key);
        if (temp == nullptr) return false;
        recursiveDelete(root, key);
        return true;
    }

    void inorder(node <T1, T2>* start) {
        if (start->left != nullptr) inorder(start->left);
        cout << setw(9) << setfill('0') << start->key << " " << start->value << endl;
        if (start->right != nullptr) inorder(start->right);
    }

    void print() {
        if (root == nullptr) {
            cout << "EMPTY" << endl;
        }
        else
            inorder(root);
    }

    inline int children(node<T1, T2>* found) {
        int arity;
        if (found->left == nullptr && found->right == nullptr) {
            arity = 0;
        }
        else if (found->left == nullptr || found->right == nullptr) {
            arity = 1;
        }
        else arity = 2;
        return arity;
    }

    void recursiveClean(node<T1, T2>* item) {
        if (item == nullptr) return;
        if (item->left) recursiveClean(item->left);
        if (item->right) recursiveClean(item->right);

        delete item;
    }

    void clean() {
        recursiveClean(root);
        root = nullptr;
    }

};
