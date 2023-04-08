#include <iostream>
#include <vector>
#include<algorithm>
#include<utility>

using namespace std;

void print(int* arr, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

pair<int, int> partition(int* arr, int left, int right, int M) {
    int smaller = left; int equal = left;

    for (int i = left; i <= right; ++i) {
        if (arr[i] < M) {
            swap(arr[equal], arr[i]);
            if (equal != smaller) {
                swap(arr[equal], arr[smaller]);
            }
            ++smaller; ++equal;
        }
        else if (arr[i] == M) {
            swap(arr[equal], arr[i]);
            ++equal;
        }
    }
    if (smaller == left) smaller = 0;
    else smaller = smaller - left;

    if (equal == left) equal = 0;
    else equal = equal - left;
    equal = equal - smaller;
    return pair(smaller, equal);
}



int kth(int* bills, int left, int right, int k) {
    // right - koniec przedzialu - element ostatni, NIE za ostatnim
    int n = right - left + 1;
    int sets = n / 5; if (n % 5 != 0) ++sets;
    if (n < 10) {
        sort(bills + left, bills + right + 1);
        return bills[left + k - 1];
    }

    int* medians = new int[sets];
    int j = 0;
    // sort podzbiorow
    for (int i = left; i <= right; i = i + 5) {
        int start = i;
        int end = i + 4;
        if (end > right) end = right;
        sort(bills + start, bills + end + 1);
        medians[j++] = bills[(start + end) / 2]; // dodaje srodkowy element
    }

    int k_medians = sets / 2; if (k_medians == 0) k_medians = 1;
    int M = kth(medians, 0, sets - 1, sets / 2);
    delete[]  medians;
    pair<int, int> S = partition(bills, left, right, M);
    if (S.first >= k) {
        return kth(bills, left, left + S.first, k);
    }
    else if (S.first + S.second >= k) {
        return M;
    }
    else {
        return kth(bills, left + S.first + S.second, right, k - S.first - S.second);
    }

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int z;
    cin >> z;
    while (z-- > 0) {
        int n, k;
        cin >> n >> k;
        int* bills = new int[n];
        for (int i = 0; i < n; ++i) {
            cin >> bills[i];
        }

        int k_th = kth(bills, 0, n - 1, k);

        cout << k_th << endl;
        delete[] bills;
    }
}