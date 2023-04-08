#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    long long z;
    cin >> z;
    while (z-- > 0) {
        // --- in ---
        long long v, e;
        cin >> v >> e;
        ++v;
        // --------------------initialize---------------------------
        long long vertices = v;
        vector<vector<long long>> adjacent(vertices);
        vector<long long> time(vertices);
        vector<long long> degree_in(vertices);
        vector<long long> top_sort_graph(2 * vertices);
        vector<long long> in_path(vertices);
        vector<long long> out_path(vertices);
        adjacent[0].push_back(0);time[0] = 0;
        degree_in[0] = 1;

        // --------------------------------------------------------
        long long t, v1, v2;
        char comparison;
        for (long long i = 1; i < v; ++i) {
            cin >> t;
            time[i] = t;
            degree_in[i] = 0;
        }
        for (long long i = 0; i < e; ++i) {
            long long x;
            cin >> v1 >> comparison >> v2;
            adjacent[v1].push_back(v2);
            ++degree_in[v2];
        }

        // --- out ---
        long long query, t_extension; long long longest_path;

        // ------------------------topSort---------------------------

        queue<long long> que;
        bool cycle;
        for (long long i = 1; i < vertices; ++i) if (degree_in[i] == 0) que.push(i);
        long long count = 0;
        while (!que.empty()) {
            long long vertex = que.front();
            que.pop();
            ++count;
            top_sort_graph.push_back(vertex); // dodaje wierzhlek do porzadku topologicznego
            for (long long& adj : adjacent[vertex]) {
                --degree_in[adj]; // usuwam krawedz z grafu laczaca z vertex
                if (degree_in[adj] == 0) que.push(adj);
            }
        }
        if (count < vertices - 1) cycle = true; //jest cykl
        else cycle = false;

        // --------------------------------------------------------
        if (cycle) cout << "CYKL\n";
        else {
            // -------------------longestPath----------------------
            in_path[1] = 0; out_path[vertices - 1] = 0;
            for (long long& vertex : top_sort_graph) {
                for (long long& adj : adjacent[vertex]) {
                    if (in_path[adj] < in_path[vertex] + time[vertex])
                        in_path[adj] = in_path[vertex] + time[vertex];
                }
            }
            // from
            long long index = top_sort_graph.size() - 1;
            while (index != 0) {
                long long vertex = top_sort_graph[index--];
                for (long long& adj : adjacent[vertex]) {
                    if (out_path[adj] + time[adj] > out_path[vertex])
                        out_path[vertex] = out_path[adj] + time[adj];
                }
            }
            // longest path
            longest_path = 0;
            for (long long i = 0; i < vertices; ++i) {
                long long curr_path = in_path[i] + out_path[i] + time[i];
                if (curr_path > longest_path) longest_path = curr_path;
            }
            // ----------------------------------------------------
            cout << "OK " << longest_path << "\n";
        }

        cin >> query;
        for (long long i = 0; i < query; ++i) {
            cin >> v1 >> t_extension;
            if (!cycle) {
                // ------------------willExtend--------------------
                long long will_extend;
                long long new_time = in_path[v1] + time[v1] + out_path[v1] + t_extension;
                if (new_time > longest_path) will_extend = (new_time - longest_path);
                else  will_extend = -1;
                if (will_extend == -1) cout << "TAK\n";
                else cout << "NIE " << will_extend << "\n";
            }
        }
    }
}
