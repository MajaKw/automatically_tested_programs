#include <iostream>
#include <vector>

using namespace std;

void print(vector<int>& soldiers, int begin, int end) {
    for (int i = begin; i <= end; ++i)
        cout << soldiers[i] << " ";
    cout << endl;
}

long long merge(vector<int>& arr, int begin_left, int end_left, int begin_right, int end_right, int toes, int curr) {
    long long inversions = 0;
    int result_size = end_right - begin_left + 1;
    vector<int> result(result_size);
    int l = begin_left; int r = begin_right;
    curr = 0;
    int left = end_left;
    int right = end_right;
    while (right >= begin_right) {
        while (left >= begin_left and arr[left] + toes < arr[right]) --left;
        inversions += end_left - left;
        --right;
    }
    while (l <= end_left and r <= end_right) {
        if (arr[l] > arr[r]) result[curr++] = arr[l++];
        else result[curr++] = arr[r++];
    }

    while (l <= end_left) result[curr++] = arr[l++];
    while (r <= end_right) result[curr++] = arr[r++];

    int curr_arr = begin_left;
    for (int i = 0; i < curr; ++i) {
        arr[curr_arr] = result[i];
        ++curr_arr;
    }
    return inversions;

}

long long mergeSort(vector<int>& arr, int begin, int end, int toes, int curr) {
    long long  inversions = 0;
    if (end - begin + 1 < 2) {
        return inversions;
    }
    int mid = (begin + end) / 2;
    int begin_left = begin;
    int end_left = mid;
    int begin_right = mid + 1;
    int end_right = end;

    inversions += mergeSort(arr, begin_left, end_left, toes, curr);
    inversions += mergeSort(arr, begin_right, end_right, toes, curr);
    inversions += merge(arr, begin_left, end_left, begin_right, end_right, toes, curr);

    return inversions;
}




int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int z;
    cin >> z;
    while (z-- > 0) {
        int n, toes;
        cin >> n >> toes;
        vector<int> soldiers(n);
        for (int i = 0; i < n; ++i) {
            cin >> soldiers[i];
        }
        long long inversions;
        int curr = 0;
        inversions = mergeSort(soldiers, 0, n - 1, toes, curr);
        print(soldiers, 0, n - 1);
        cout << inversions << endl;
    }
}