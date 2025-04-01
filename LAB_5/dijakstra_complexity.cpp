#include <iostream>
#include <climits>
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>
using namespace std;
using namespace std::chrono;

void generate_random_graph(int** cost, int n, int edge_probability = 50) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> weight_dist(1, 100);
    uniform_int_distribution<> prob_dist(1, 100);

    for (int i = 0; i < n; i++) {
        cost[i] = new int[n];
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cost[i][j] = 0;
            } else {
                cost[i][j] = (prob_dist(gen) <= edge_probability ? weight_dist(gen) : INT_MAX);
            }
        }
    }
}

void dijkstra(int source, int** cost, int n, int* dist, int* p) {
    bool* visited = new bool[n]();
    
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
            if (!visited[j] && cost[u][j] != INT_MAX && dist[u] != INT_MAX && 
                dist[j] > dist[u] + cost[u][j]) {
                dist[j] = dist[u] + cost[u][j];
                p[j] = u;
            }
        }
    }
    delete[] visited;
}

int main() {
    ofstream size_file("dijkstra_size.csv");
    ofstream time_file("dijkstra_time.csv");
    

    // Test for various graph sizes
    for (int n = 10; n <= 10000; n = n < 100 ? n + 10 : n * 2) {
        // Allocate memory
        int** cost = new int*[n];
        int* dist = new int[n];
        int* p = new int[n];

        // Generate random graph
        generate_random_graph(cost, n, min(50, 5000/n)); 

        // Time measurement
        auto start = high_resolution_clock::now();
        
       
        int runs = n < 1000 ? 100 : 10;
        for (int i = 0; i < runs; i++) {
            dijkstra(0, cost, n, dist, p); 
        }
        
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;

        // Write to CSV
        size_file << n << "\n";
        time_file << elapsed.count()/runs << "\n";

        cout << "Size: " << n << " Time: " << elapsed.count()/runs << " seconds\n";

        // Clean up
        for (int i = 0; i < n; i++) {
            delete[] cost[i];
        }
        delete[] cost;
        delete[] dist;
        delete[] p;
    }

    size_file.close();
    time_file.close();
    cout << "CSV files generated successfully!\n";

    return 0;
}