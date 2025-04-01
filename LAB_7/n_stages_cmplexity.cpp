#include <iostream>
#include <climits>
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>
using namespace std;
using namespace std::chrono;

void generate_random_graph(int** cost, int n, int edges) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> vertex_dist(0, n-1);
    uniform_int_distribution<> weight_dist(1, 100);

    
    for (int i = 0; i < n; i++) {
        cost[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cost[i][j] = 0;
        }
    }

    
    for (int stage = 0; stage < n-1 && edges > 0; stage++) {
        int edges_in_stage = min(edges, max(1, (int)(n*0.2))); 
        for (int e = 0; e < edges_in_stage && edges > 0; e++) {
            int i = stage;
            int j = vertex_dist(gen);
            while (j <= i) j = vertex_dist(gen); 
            
            if (cost[i][j] == 0) {
                cost[i][j] = weight_dist(gen);
                edges--;
            }
        }
    }
}

int find_stage(int** cost, int n, int stage, int count) {
    if (stage == n-1) {
        return count;
    }

    for (int i = 0; i < n; i++) {
        if (cost[stage][i] != 0) {
            return find_stage(cost, n, stage+1, count+1);
        }
    }

    return count;
}

int main() {
    ofstream size_file("size.csv");
    ofstream time_file("time.csv");

    
    for (int n = 3; n <= 10000; n *= 2) {
        int edges = n * log2(n); 
        
        int** cost = new int*[n];
        generate_random_graph(cost, n, edges);

        auto start = high_resolution_clock::now();
        const int runs = 100;
        int total_stages = 0;
        for (int k = 0; k < runs; k++) {
            total_stages += find_stage(cost, n, 0, 0);
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;

    
        size_file << n << "\n";
        time_file << elapsed.count()/runs << "\n";
        cout << "n=" << n << ", stages=" << total_stages/runs 
             << ", time=" << elapsed.count()/runs << "s\n";

    
        for (int i = 0; i < n; i++) delete[] cost[i];
        delete[] cost;
    }

    size_file.close();
    time_file.close();
    cout << "CSV files generated successfully!\n";
    return 0;
}