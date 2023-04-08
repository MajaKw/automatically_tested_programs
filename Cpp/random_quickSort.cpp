#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

int partition(vector<pair<long long, long long>>& sloths, int left, int right) {
    swap(sloths[left + rand() % (right - left)], sloths[left]);
    long long pivot = sloths[left].second;
    int i = left - 1;
    int j = right + 1;

    while (true) {
        while (sloths[++i].second < pivot);
        while (sloths[--j].second > pivot);

        if (i >= j) break;
        swap(sloths[i], sloths[j]);
    }
    return j;
}

void quicksort(vector<pair<long long, long long>>& sloths, int left, int right) {
    if (left >= right) return;

    int j = partition(sloths, left, right);
    quicksort(sloths, left, j);
    quicksort(sloths, j + 1, right);

}
pair<long long, long long> lazy_days(vector<pair<long long, long long>>& sloths, int n) {
    int day_position = n - 1;
    long long free_days = 0;
    // i - termin position
    for (int i = n - 1; i > 0; --i) {
        long long work = sloths[i].second - sloths[day_position].first - sloths[i - 1].second;
        if (work > 0) {
            free_days += work;
            --day_position;
        }
        else {
            sloths[i - 1].second = sloths[i].second - sloths[day_position].first;
            --day_position;
        }
        if (sloths[i - 1].second < 0) return pair<long long, long long>(-1, -1);
    }
    if (sloths[0].second - sloths[0].first < 0) return pair<long long, long long>(-1, -1);
    else return pair<long long, long long>(sloths[0].second - sloths[0].first, free_days);
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int z;
    cin >> z;
    while (z-- > 0) {

        int n;
        cin >> n;
        vector<pair<long long, long long>> sloths(n);

        for (int i = 0; i < n; ++i) {
            // first - days, second - termin
            cin >> sloths[i].first >> sloths[i].second;
        }

        quicksort(sloths, 0, n - 1);

        for (long long i = 0; i < n; ++i)
            cout << sloths[i].second << " ";
        cout << endl;
        pair<long long, long long> result = lazy_days(sloths, n);
        if (result.first == -1) cout << "ERROR\n";
        else cout << result.first << " " << result.second << "\n";
    }
}
