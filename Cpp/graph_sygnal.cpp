#include<iostream>
#include<utility>
#include<vector>
#include<queue>

using namespace std;

class node {
public:
    int time = -1;
    vector<int> adjacent;
};

void BST(vector<node>& graph, int capacity, int curr) {
    vector<bool> visited;
    visited.resize(capacity, false);
    visited[0] = true;
    visited[curr] = true;
    queue<int> que[2];
    int layer_one = 0;
    int layer_two = 1;// or 1
    que[layer_one].push(curr);
    int time = 1;
    while (!que[layer_one].empty()) {
        while (!que[layer_one].empty()) {
            curr = que[layer_one].front(); que[layer_one].pop();
            for (auto adj : graph[curr].adjacent) {
                if (!visited[adj]) {
                    visited[adj] = true;
                    graph[adj].time = time;
                    que[layer_two].push(adj);
                }
            }
        }
        ++time;
        layer_one = layer_two;
        if (layer_one == 0) layer_two = 1; else layer_two = 0;
    }
}


void printAdjacency(vector<node>& graph, int  curr) {
    for (int i = curr; i < graph.size(); ++i) {
        cout << "nr: " << i << endl;
        for (int j = 0; j < graph[i].adjacent.size(); ++j) {
            cout << graph[i].adjacent[j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int z;
    cin >> z;
    while (z-- > 0) {

        int v, e;
        cin >> v >> e;
        int v1, v2, time;
        char code;
        int artfficial_vertices = v + 1;
        vector<node> graph(v + 1);
        graph[0].adjacent.push_back(0); // zajmuje jakos 0 miejsce
        int graph_size = v + 1;

        int add = artfficial_vertices;
        for (int i = 0; i < e; ++i) {
            cin >> v1 >> v2 >> code;
            if (code == '_') {
                graph[v1].adjacent.push_back(v2);
                graph[v2].adjacent.push_back(v1);
            }
            else if (code == '#') {
                if (add >= graph_size) {
                    graph.resize(2 * graph_size);
                    graph_size = 2 * graph_size;
                }

                graph[v1].adjacent.push_back(artfficial_vertices);
                graph[artfficial_vertices].adjacent.push_back(v1);
                graph[artfficial_vertices].adjacent.push_back(v2);
                graph[v2].adjacent.push_back(artfficial_vertices);

                ++artfficial_vertices;
                ++add;
            }
        }
        BST(graph, artfficial_vertices, 1);

        for (int i = 1; i <= v; ++i) {
            if (graph[i].time == -1 && i != 1) cout << "!\n";
            else if (i == 1) cout << "0\n";
            else cout << graph[i].time << endl;
        }
    }
}