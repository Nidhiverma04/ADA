#include<iostream>
#include<random>
#include<climits>
using namespace std;

class node{
    public:
    int val;
    node* next;

    node(int v){
        val = v;
        next = nullptr;
    }
};

void generate_vertices(int** cost, int n){
    for(int i =0;i<n;i++)
        cost[i] = new int[n];
    
    
    for(int i=0;i<n;i++){
        for(int j = 0;j<n;j++){
            cost[i][j] = 0;
        }
    }

    cout<<"Enter number of edges : ";
    int edges;
    cin>>edges;
    int i,j,w;
    for(int k=0;k<edges;k++){
        cout<<"Enter i, j: ";
        cin>>i>>j;
        cout<<"Enter weight : ";
        cin>>w;
        cost[i][j] = w;
    }

    return;
}

void dijkstra(int source, int** cost, int n, int* dist, node* path[], int* p) {
    bool flag[n] = {false};
    for (int i = 0; i < n; i++) {
        dist[i] = (cost[source][i] == 0 && i != source) ? INT_MAX : cost[source][i];
        flag[i] = false;
        path[i] = new node(source);
    }

    flag[source] = true;
    dist[source] = 0;
    p[source] = 0;

    for (int count = 0; count < n - 1; count++) { 
        int u = -1, minDist = INT_MAX;
        for (int i = 0; i < n; i++) { 
            if (!flag[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break; 
        flag[u] = true;

        for (int j = 0; j < n; j++) {
            if (!flag[j] && cost[u][j] && dist[u] != INT_MAX && dist[j] > dist[u] + cost[u][j]) {
                dist[j] = dist[u] + cost[u][j];

                p[j] = u;
                delete path[j]; 
                path[j] = new node(source);
                node* temp = path[j];
                for (node* p = path[u]; p != nullptr; p = p->next) {
                    temp->next = new node(p->val);
                    temp = temp->next;
                }
                temp->next = new node(j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Dist of " << i << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << endl;
        cout << "Path: ";
        for (node* temp = path[i]; temp != nullptr; temp = temp->next) {
            cout << temp->val << " -> ";
        }
        cout << "END" << endl<<endl;
    }
}

int main(){
    int n ;
    cout<<"Enter number of vertices : ";
    cin>>n;
    int** cost = new int*[n];
    generate_vertices(cost, n);

    int source;
    cout<<"Enter source : ";
    cin>>source;

    int* dist = new int[n];
    for(int i=0;i<n;i++){
        dist[i] = INT32_MAX;
    }
    dist[source] = 0;
    node* path[n];

    for (int i = 0; i < n; i++) {
        path[i] = nullptr; 
    }

    int* p = new int[n];
    dijkstra(source, cost, n, dist, path, p);

    int i = n-1;
    while( p[i]!=0){
        cout<<p[i]<<" ";
        i = p[i];
    }

    for (int i = 0; i < n; i++) {
        delete[] cost[i];
    }

    delete[] cost;
    delete[] dist;

}