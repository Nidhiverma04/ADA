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

int find_min_vertex(int j, int** cost, int* f_dist, edgeInfo* edge, int size) {
    int mincost = INT_MAX, r = -1;

    for (int i = 0; i < size; i++) {
        if (edge[i].s == j && cost[j][edge[i].d] != INT_MAX) {
            int total_cost = edge[i].wt + f_dist[edge[i].d];
            if (total_cost < mincost) {
                mincost = total_cost;
                r = edge[i].d;
            }
        }
    }

    return r;
}

void forward_subst(int** cost, int n, int k, int* f_dist, edgeInfo* edge, int edges){
    int* dist = new int[n];
    f_dist[n-1] = 0;
    cout<<"made declarations\n";
    
    for(int j = n-2;j>=0;j--){
            int r = find_min_vertex(j, cost, f_dist, edge, edges);

            if(r!=-1){
                f_dist[j] = cost[j][r] + f_dist[r];
                dist[j] = r;
            }
            cout<<"found r = "<<r<<"\n";
            cout<<"Updations done\n";
    }

    cout<<"Path : "<<endl;
    int path_vertex = 0;
    cout << path_vertex;
    while (path_vertex != n - 1) {
        cout << " --> " << dist[path_vertex];
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
    int* f_dist = new int[n];
    for(int i =0;i<n;i++){
        f_dist[i] = 0;
    }
    generate_vertices(cost, edge, n, edges);

    forward_subst(cost, n, k, f_dist, edge, edges);

}