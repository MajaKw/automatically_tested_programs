#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct node {
    int left, right, distanceParent, inhabitants, sumWay, passersBy;
    node(int left = 0, int right = 0, int inhabitants = 0, int distanceParent = 0) {
        this->left = left; this->right = right; this->distanceParent = distanceParent; this->inhabitants = inhabitants;
        this->sumWay = 0; this->passersBy = 0;
    }
};
class Tree {
public:
    vector <node> tree;
    int vertex;
    bool done = false;

    int passersBy(int i) {
        --i; int l = 0; int r = 0;
        if (tree.at(i).left != 0)
            l = passersBy(tree.at(i).left);
        if (tree.at(i).right != 0)
            r = passersBy(tree.at(i).right);
        tree.at(i).passersBy = l + r;
        return tree.at(i).passersBy + tree.at(i).inhabitants;
    }
    void way(int i, int distance) {
        --i;
        tree.at(i).sumWay = distance + tree.at(i).distanceParent;
        if (tree.at(i).left != 0)
            way(tree.at(i).left, tree.at(i).sumWay);
        if (tree.at(i).right != 0)
            way(tree.at(i).right, tree.at(i).sumWay);
    }
    void printPreOrder(int i, bool passersBy) {
        --i;
        if (i < 0) return;
        if (passersBy) {
            cout << tree.at(i).passersBy << " ";
        }
        else cout << tree.at(i).sumWay << " ";
        printPreOrder(tree.at(i).left, passersBy);
        printPreOrder(tree.at(i).right, passersBy);
    }
    void printInOrder(int i, bool passersBy) {
        --i;
        if (i < 0) return;
        printInOrder(tree.at(i).left, passersBy);
        if (passersBy) {
            cout << tree.at(i).passersBy << " ";
        }
        else cout << tree.at(i).sumWay << " ";
        printInOrder(tree.at(i).right, passersBy);

    }
    void printPostOrder(int i, bool passersBy) {
        --i;
        if (i < 0) return;
        printPostOrder(tree.at(i).left, passersBy);
        printPostOrder(tree.at(i).right, passersBy);
        if (passersBy) {
            cout << tree.at(i).passersBy << " ";
        }
        else cout << tree.at(i).sumWay << " ";
    }
    //preorder
    int district(int i, int all) {

        int l = tree.at(i).left; int r = tree.at(i).right; bool was_l = false; bool was_r = false;
        if (l == 0 && r == 0) return -1; // nie da sie zrobic podzialu
        //dzielimy na 2 dystrykty
        if (l != 0) { --l; was_l = true; }
        if (r != 0) { --r; was_r = true; }
        if (i == 0) {
            int leftSubTree = tree.at(l).passersBy + tree.at(l).inhabitants; int rightSubTree = tree.at(r).passersBy + tree.at(r).inhabitants;

            if (leftSubTree * 2 <= all && rightSubTree * 2 <= all) {
                return ++i;
            }
        }
        else if ((l == 0 && r != 0) || (l != 0 && r == 0)) {
            int subTree = tree.at(i).passersBy;

            if (subTree * 2 <= all && (all - subTree - tree.at(i).inhabitants) * 2 <= all) {
                vertex = ++i;
                return vertex;
            }
        }        
else {
            int leftSubTree = tree.at(l).passersBy + tree.at(l).inhabitants; int rightSubTree = tree.at(r).passersBy + tree.at(r).inhabitants;

            if (leftSubTree * 2 <= all && rightSubTree * 2 <= all && ((all - leftSubTree - rightSubTree - tree.at(i).inhabitants) * 2 <= all)) {

                return ++i;
            }
        }


        if (was_l) ++l;
        if (was_r) ++r;

        return -1;
    }
    int districtPreOrder(int i, int all) {
        if (this->done) { return -1; }
        --i;
        int vertex = -1;

        vertex = district(i, all); //próbuję przydzielić dystrykt w danym wierzholku

        if (vertex != -1) {
            this->vertex = vertex;
            this->done = true;
            return -1;
        }
        if (tree.at(i).left != 0) districtPreOrder(tree.at(i).left, all); // jak mi sie nie uda probuje to samo w lewym
        if (tree.at(i).right != 0) districtPreOrder(tree.at(i).right, all); // a potem w
        if (this->done) { return -1; }
        return -1;
    }
    int districtInOrder(int i, int all) {
        if (this->done) { return -1; }
        --i;
        int vertex = -1;
        if (tree.at(i).left != 0) districtInOrder(tree.at(i).left, all);
        if (this->done) { return -1; } // jak mi sie nie uda probuje to samo w lewym
        vertex = district(i, all);
        if (this->done) { return -1; }
        if (vertex != -1) {
            this->vertex = vertex;
            this->done = true;
            return -1;
        }
        if (tree.at(i).right != 0) districtInOrder(tree.at(i).right, all); // a potem w prawym
        if (this->done) { return-1; }
        return -1;
    }
    int districtPostOrder(int i, int all) {
        if (this->done) { return -1; }
        --i;
        int vertex = -1;

        if (tree.at(i).left != 0) districtPostOrder(tree.at(i).left, all); // jak mi sie nie uda probuje to samo w lewym
        if (this->done) { return -1; }
        if (tree.at(i).right != 0) districtPostOrder(tree.at(i).right, all); // a potem w prawym
        if (this->done) { return -1; }
        vertex = district(i, all);
        if (this->done) { return -1; }
        if (vertex != -1) {
            this->vertex = vertex;
            this->done = true;
            return -1;
        }
        return -1;
    }

};


int main() {
    int z; cin >> z;
    for (int x = 0; x < z; ++x) {
        int n; cin >> n;
        int left, right, distanceParent, inhabitants;
        string order;
        Tree city;
        for (int i = 0; i < n; ++i) {
            cin >> left >> right >> inhabitants >> distanceParent;
            node vertex(left, right, inhabitants, distanceParent);
            city.tree.push_back(vertex);
        }
        cin >> order;
        int all = city.passersBy(1);
        city.way(1, 0);
        int district;
        if (order == "PREORDER") {
            city.printPreOrder(1, false);
            cout << '\n';
            city.printPreOrder(1, true);
            city.districtPreOrder(1, all);
            district = city.vertex;
        }
        if (order == "INORDER") {
            city.printInOrder(1, false);
            cout << '\n';
            city.printInOrder(1, true);
            city.districtInOrder(1, all);
            district = city.vertex;
        }
        if (order == "POSTORDER") {
            city.printPostOrder(1, false);
            cout << '\n';
            city.printPostOrder(1, true);
            city.districtPostOrder(1, all);
            district = city.vertex;
        }
        cout << "\n";

        cout << district << endl;
    } // for zestawy
}