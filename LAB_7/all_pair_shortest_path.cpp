#include <iostream>
#include <climits>
#include<iomanip>
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

void all_pair(int n, int** cost, int** &a) { 
    a = new int*[n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = cost[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][k] != INT_MAX && a[k][j] != INT_MAX && a[i][j] > a[i][k] + a[k][j]) {
                    a[i][j] = a[i][k] + a[k][j];
                }
            }
        }
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
    
    generate_vertices(cost, edge, n, edges);

    int** ans = nullptr;
    all_pair(n, cost, ans);

    cout << "Shortest path matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ans[i][j] == INT_MAX)
                cout <<setw(5)<< "INF ";
            else
                cout << setw(5)<<ans[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] cost[i];
        delete[] ans[i];
    }
    delete[] cost;
    delete[] ans;
    delete[] edge;

    return 0;
}
