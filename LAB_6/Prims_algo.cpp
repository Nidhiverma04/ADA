#include <iostream>
#include <climits>
using namespace std;

void generate_vertices(int** cost, int n, int edges) {
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
            cost[j][i] = w;  
        } else {
            cout << "Invalid input! Edge not added." << endl;
            k--;
        }
    }
}

int min_edge_vertex(int** cost, int* near, int n) {
    int minCost = INT_MAX;
    int u = -1;

    for (int i = 0; i < n; i++) {
        if (near[i] != 0 && cost[i][near[i]] < minCost) {
            minCost = cost[i][near[i]];
            u = i;
        }
    }

    return u;
}

int** prims(int** cost, int* near, int n) {
    int minwt = INT_MAX;
    int k = -1, l = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (cost[i][j] != 0 && cost[i][j] < minwt) {
                minwt = cost[i][j];
                k = i;
                l = j;
            }
        }
    }

    
    for (int i = 0; i < n; i++) {
        if (cost[i][k] < cost[i][l]) {
            near[i] = k;
        } else {
            near[i] = l;
        }
    }

    near[k] = 0;
    near[l] = 0;

    int** t = new int*[n - 1];
    for (int i = 0; i < n - 1; i++)
        t[i] = new int[2];

    t[0][0] = k;
    t[0][1] = l;

    int minCost = cost[k][l];

    for (int i = 1; i < n - 1; i++) {
        int u = min_edge_vertex(cost, near, n);

        t[i][0] = u;
        t[i][1] = near[u];
        minCost += cost[u][near[u]];

        near[u] = 0;  

        for (int v = 0; v < n; v++) {
            if (near[v] != 0 && cost[v][u] < cost[v][near[v]]) {
                near[v] = u;
            }
        }
    }

    cout << "Minimum Cost of MST: " << minCost << endl;
    return t;
}

int main() {
    int n, edges;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> edges;

    int** cost = new int*[n];
    int* near = new int[n];

    generate_vertices(cost, n, edges);

    int** tree = prims(cost, near, n);

    cout << "Edges in the MST:\n";
    for (int i = 0; i < n - 1; i++) {
        cout << tree[i][0] << " - " << tree[i][1] << endl;
    }
}


