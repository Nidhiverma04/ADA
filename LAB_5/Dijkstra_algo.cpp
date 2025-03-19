#include <iostream>
#include <climits>
using namespace std;

void generate_vertices(int** cost, int n) {
    for (int i = 0; i < n; i++)
        cost[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = (i == j) ? 0 : INT_MAX; 
        }
    }

    cout << "Enter number of edges: ";
    int edges;
    cin >> edges;

    for (int k = 0; k < edges; k++) {
        int i, j, w;
        cout << "Enter i, j: ";
        cin >> i >> j;
        cout << "Enter weight: ";
        cin >> w;
        if (i >= 0 && i < n && j >= 0 && j < n && w >= 0) {
            cost[i][j] = w;
        } else {
            cout << "Invalid input! Edge not added." << endl;
        }
    }
}

void dijkstra(int source, int** cost, int n, int* dist, int* p) {
    bool visited[n] = {false};

    for (int i = 0; i < n; i++) {
        dist[i] = cost[source][i];
        p[i] = (dist[i] != INT_MAX) ? source : -1;
    }

    dist[source] = 0;
    visited[source] = true;

    for (int count = 0; count < n - 1; count++) {
        int u = -1, minDist = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && cost[u][j] != INT_MAX && dist[u] != INT_MAX && dist[j] > dist[u] + cost[u][j]) {
                dist[j] = dist[u] + cost[u][j];
                p[j] = u;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Distance to " << i << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << endl;
        cout << "Path: ";
        if (dist[i] != INT_MAX) {
            int temp = i;
            while (temp != source) {
                cout << temp << " <- ";
                temp = p[temp];
            }
            cout << source << endl;
        } else {
            cout << "No path" << endl;
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    int** cost = new int*[n];
    generate_vertices(cost, n);

    int source;
    cout << "Enter source: ";
    cin >> source;

    int* dist = new int[n];
    int* p = new int[n]; 

    dijkstra(source, cost, n, dist, p);

    for (int i = 0; i < n; i++) {
        delete[] cost[i];
    }
    delete[] cost;
    delete[] dist;
    delete[] p;

    return 0;
}