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

void generate_random_graph(int** cost, int n, int edge_count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> weight_dist(1, 100);
    
    // Initialize cost matrix
    for (int i = 0; i < n; i++) {
        cost[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cost[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    // Generate a connected graph (minimum spanning tree first)
    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 0);
    shuffle(vertices.begin(), vertices.end(), gen);

    // Create spanning tree edges
    for (int i = 1; i < n; i++) {
        int j = uniform_int_distribution<>(0, i-1)(gen);
        int w = weight_dist(gen);
        cost[vertices[i]][vertices[j]] = w;
        cost[vertices[j]][vertices[i]] = w;
    }

    // Add remaining random edges
    int edges_added = n-1;
    while (edges_added < edge_count) {
        int u = uniform_int_distribution<>(0, n-1)(gen);
        int v = uniform_int_distribution<>(0, n-1)(gen);
        if (u != v && cost[u][v] == INT_MAX) {
            int w = weight_dist(gen);
            cost[u][v] = w;
            cost[v][u] = w;
            edges_added++;
        }
    }
}

int** prims(int** cost, int n) {
    int* near = new int[n];
    int** t = new int*[n-1];
    for (int i = 0; i < n-1; i++) {
        t[i] = new int[2];
    }

    // Initialize near array
    int minCost = INT_MAX;
    int k, l;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (cost[i][j] < minCost) {
                minCost = cost[i][j];
                k = i;
                l = j;
            }
        }
    }

    // First edge in MST
    t[0][0] = k;
    t[0][1] = l;
    int totalCost = minCost;

    // Initialize near array
    for (int i = 0; i < n; i++) {
        near[i] = (cost[i][k] < cost[i][l]) ? k : l;
    }
    near[k] = near[l] = -1;

    // Find remaining n-2 edges
    for (int i = 1; i < n-1; i++) {
        // Find minimum cost edge
        int minEdge = INT_MAX;
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (near[j] != -1 && cost[j][near[j]] < minEdge) {
                minEdge = cost[j][near[j]];
                u = j;
            }
        }

        // Add edge to MST
        t[i][0] = u;
        t[i][1] = near[u];
        totalCost += minEdge;
        near[u] = -1;

        // Update near array
        for (int v = 0; v < n; v++) {
            if (near[v] != -1 && cost[v][u] < cost[v][near[v]]) {
                near[v] = u;
            }
        }
    }

    delete[] near;
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
        generate_random_graph(cost, n, edge_count);

        // Benchmark
        auto start = high_resolution_clock::now();
        const int runs = 10;
        for (int k = 0; k < runs; k++) {
            int** tree = prims(cost, n);
            if (tree == nullptr) {
                cerr << "Error: No spanning tree found for n=" << n << endl;
                break;
            }
            for (int i = 0; i < n-1; i++) delete[] tree[i];
            delete[] tree;
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;

        // Write results
        size_file << edge_count << "\n";
        vert_file << n << "\n";
        time_file << elapsed.count()/runs << "\n";
        cout << "n=" << n << ", edges=" << edge_count 
             << ", time=" << elapsed.count()/runs << "s\n";

        // Clean up
        for (int i = 0; i < n; i++) delete[] cost[i];
        delete[] cost;
    }

    size_file.close();
    time_file.close();
    vert_file.close();
    cout << "CSV files generated successfully!\n";
    return 0;
}