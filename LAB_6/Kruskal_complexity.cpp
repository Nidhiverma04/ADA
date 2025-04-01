#include <iostream>
#include <climits>
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
using namespace std::chrono;

struct edgeInfo {
    int s;
    int d;
    int wt;
};

void generate_random_graph(int** cost, edgeInfo* edges, int n, int edge_count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> weight_dist(1, 100);

    for (int i = 0; i < n; i++) {
        cost[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cost[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

   
    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 0);
    shuffle(vertices.begin(), vertices.end(), gen);

  
    for (int i = 1; i < n; i++) {
        int j = uniform_int_distribution<>(0, i-1)(gen);
        int w = weight_dist(gen);
        cost[vertices[i]][vertices[j]] = w;
        cost[vertices[j]][vertices[i]] = w;
        edges[i-1] = {vertices[i], vertices[j], w};
    }

   
    int edges_added = n-1;
    while (edges_added < edge_count) {
        int u = uniform_int_distribution<>(0, n-1)(gen);
        int v = uniform_int_distribution<>(0, n-1)(gen);
        if (u != v && cost[u][v] == INT_MAX) {
            int w = weight_dist(gen);
            cost[u][v] = w;
            cost[v][u] = w;
            edges[edges_added] = {u, v, w};
            edges_added++;
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

    while (count < n - 1 && edges > 0) { 
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
        return nullptr;
    }

    return t;
}

int main() {
    ofstream size_file("size.csv");
    ofstream time_file("time.csv");
    ofstream vert_file("vertices.csv");

    random_device rd;
    mt19937 gen(rd());
    
    for (int n = 10; n <= 10000; n *= 2) {
        
        int max_possible_edges = n*(n-1)/2;
        int edge_count = uniform_int_distribution<>(n-1, min(max_possible_edges, 5*n))(gen);
        
        int** cost = new int*[n];
        edgeInfo* edges = new edgeInfo[edge_count];
        int* parent = new int[n];

       
        generate_random_graph(cost, edges, n, edge_count);

       
        auto start = high_resolution_clock::now();
        const int runs = 10;
        for (int k = 0; k < runs; k++) {
           
            edgeInfo* edges_copy = new edgeInfo[edge_count];
            copy(edges, edges + edge_count, edges_copy);
            
            int** tree = kruskals(edges_copy, cost, parent, n, edge_count);
            delete[] edges_copy;
            if (tree == nullptr) {
                cerr << "Error: No spanning tree found for n=" << n << endl;
                break;
            }
            
            for (int i = 0; i < n-1; i++) delete[] tree[i];
            delete[] tree;
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;

       
        size_file << edge_count << "\n";
        vert_file << n<<endl;
        time_file << elapsed.count()/runs << "\n";
        cout << "n=" << n << ", edges=" << edge_count 
             << ", time=" << elapsed.count()/runs << "s\n";

       
        for (int i = 0; i < n; i++) delete[] cost[i];
        delete[] cost;
        delete[] edges;
        delete[] parent;
    }

    size_file.close();
    time_file.close();
    cout << "CSV files generated successfully!\n";
    return 0;
}