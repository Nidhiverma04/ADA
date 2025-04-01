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
            cost[j][i] = w;
            edge[k].s = i;
            edge[k].d = j;
            edge[k].wt = w;
        } else {
            cout << "Invalid input! Edge not added." << endl;
            k--;
        }
    }
}

int find(int i, int* p) {
    if (p[i] < 0)
        return i;
    return p[i] = find(p[i], p);
}

void unions(int i, int j, int* p) {
    int pi = find(i, p);
    int pj = find(j, p);
    if (pi != pj) {
        if (p[pi] < p[pj]) {
            p[pi] += p[pj];
            p[pj] = pi;
        } else {
            p[pj] += p[pi];
            p[pi] = pj;
        }
    }
}

void Heapify(edgeInfo* edge, int n, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < n && edge[left].wt < edge[smallest].wt)  smallest = left;
    if (right < n && edge[right].wt < edge[smallest].wt)  smallest = right;
    if (smallest != idx) {
        swap(edge[idx], edge[smallest]);
        Heapify(edge, n, smallest);
    }
}

void buildHeap(edgeInfo* edge, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(edge, n, i);
    }
}

int** kruskals(edgeInfo* edge, int** cost, int* p, int n, int edges) {
    for (int i = 0; i < n; i++)
        p[i] = -1;

    buildHeap(edge, edges); // nlogn

    int** t = new int*[n - 1];
    for (int i = 0; i < n - 1; i++)
        t[i] = new int[2];

    int count = 0, minCost = 0;

    while (count < n - 1 && edges > 0) { //
        edgeInfo minEdge = edge[0];
        edge[0] = edge[edges - 1];
        edges--;
        Heapify(edge, edges, 0);

        int parent_u = find(minEdge.s, p);
        int parent_v = find(minEdge.d, p);

        if (parent_u != parent_v) {
            t[count][0] = minEdge.s;
            t[count][1] = minEdge.d;
            minCost += minEdge.wt;
            unions(parent_u, parent_v, p);
            count++;
        }
    }

    if (count != n - 1) {
        cout << "MST cannot be formed." << endl;
        return nullptr;
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
    edgeInfo* edge = new edgeInfo[edges];
    int* parent = new int[n];

    generate_vertices(cost, edge, n, edges);

    int** tree = kruskals(edge, cost, parent, n, edges);
    if (tree) {
        cout << "Edges in the MST:\n";
        for (int i = 0; i < n - 1; i++)
            cout << tree[i][0] << " - " << tree[i][1] << endl;
    }

    return 0;
}
