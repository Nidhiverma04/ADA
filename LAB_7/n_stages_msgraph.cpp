#include <iostream>
#include <climits>
using namespace std;

void generate_vertices(int** cost, int n, int edges) {
    for (int i = 0; i < n; i++)
        cost[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = 0;
        }
    }

    for (int k = 0; k < edges; k++) {
        int i, j, w;
        cout << "Enter edge (source, destination) and weight: ";
        cin >> i >> j >> w;

        if (i >= 0 && i < n && j >= 0 && j < n && w >= 0) {
            cost[i][j] = w; 
        } else {
            cout << "Invalid input! Edge not added." << endl;
            k--;
        }
    }
}

int find_stage(int** cost, int n, int stage, int count){
    if(stage == n-1){
        return count;
    }

    for(int i=0;i<n;i++){
        if(cost[stage][i] != 0){
            return find_stage(cost, n, stage+1, count+1);
        }
    }

    return count;
}

int main() {
    int n, edges;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> edges;

    int** cost = new int*[n];
    generate_vertices(cost, n, edges);

    int no_stages = find_stage(cost, n, 0, 0);
    cout<<"No. of stages : "<<no_stages;

}