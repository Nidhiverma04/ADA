#include <iostream>
#include <climits>
using namespace std;

struct edgeInfo {
    int s;
    int d;
    int wt;
};

void generate_vertices(int** cost, edgeInfo* edge, int n, int edges) {
    for (int i = 0; i < n; i++)
        cost[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    for (int k = 0; k < edges; k++) {
        int i, j, w;
        cout << "Enter edge (source, destination) and weight: ";
        cin >> i >> j >> w;

        if (i >= 0 && i < n && j >= 0 && j < n && w >= 0) {
            cost[i][j] = w;
            edge[k].s = i;
            edge[k].d = j;
            edge[k].wt = w;
        } else {
            cout << "Invalid input! Edge not added." << endl;
            k--;
        }
    }
}

int find_min_vertex(int j, int** cost, int* b_dist, edgeInfo* edge, int size) {
    int mincost = INT_MAX, r = -1;

    for (int i = 0; i < size; i++) {
        if (edge[i].d == j && cost[edge[i].s][j] != INT_MAX) {
            int total_cost = edge[i].wt + b_dist[edge[i].s];
            if (total_cost < mincost) {
                mincost = total_cost;
                r = edge[i].s;
            }
        }
    }

    return r;
}

void backward_subst(int** cost, int n, int k, int* b_dist, edgeInfo* edge, int edges) {
    int* dist = new int[n];
    for (int i = 0; i < n; i++) {
        b_dist[i] = INT_MAX;
    }
    b_dist[0] = 0;

    cout << "Starting backward approach...\n";

    for (int j = 1; j < n; j++) {
        int r = find_min_vertex(j, cost, b_dist, edge, edges);

        if (r != -1) {
            b_dist[j] = cost[r][j] + b_dist[r];
            dist[j] = r;
        }

        cout << "Updated distance for node " << j << "\n";
    }

    cout << "Shortest Path : " << endl;
    int path_vertex = n - 1;
    cout << path_vertex;
    while (path_vertex != 0) {
        cout << " <-- " << dist[path_vertex];
        path_vertex = dist[path_vertex];
    }
}

int main() {
    int n, edges, k;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> edges;
    cout << "Enter number of stages: ";
    cin >> k;

    edgeInfo* edge = new edgeInfo[edges];
    int** cost = new int*[n];
    int* b_dist = new int[n];

    generate_vertices(cost, edge, n, edges);
    backward_subst(cost, n, k, b_dist, edge, edges);

    return 0;
}
