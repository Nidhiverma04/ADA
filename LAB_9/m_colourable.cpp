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
        int i, j;
        cout << "Enter edge (source, destination):  ";
        cin >> i >> j;

        if (i >= 0 && i < n && j >= 0 && j < n) {
            cost[i][j] = 1;
            cost[j][i] = 1;  
        } else {
            cout << "Invalid input! Edge not added." << endl;
            k--;
        }
    }
}

void m_colourable(int j, int curr_col, int** cost, int n, int* colour, int m) {
    if (curr_col == m || j == n)
        return;

    for (int i = 0; i < n; i++) {
        if (cost[j][i] != INT_MAX && i != j && colour[i] == -1) {
            colour[i] = curr_col;
        } else if (colour[i] == -1) {
            colour[i] = colour[j];
        }
    }

    m_colourable(j + 1, curr_col + 1, cost, n, colour, m);
}

int main(){
    int n, edges, m;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> edges;

    int** cost = new int*[n];
    int* near = new int[n];
    cout<<"Enter number of colour: ";
    cin>>m;
    int* colour = new int[n];

    generate_vertices(cost, n, edges);
    for(int i=0;i<n;i++){
        colour[i] = 0;
    }
    m_colourable(0, 1, cost, n, colour, m);

    cout<<"Solution: ";
    for(int i =0;i<n;i++){
        cout<<i<<" - "<<colour[i]<<endl;
    }
}