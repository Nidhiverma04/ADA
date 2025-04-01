#include <iostream>
#include <climits>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace std::chrono;

struct edgeInfo {
    int s, d, wt;
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
        int j = uniform_int_distribution<>(0, i - 1)(gen);
        int w = weight_dist(gen);
        cost[vertices[i]][vertices[j]] = w;
        cost[vertices[j]][vertices[i]] = w;
        edges[i - 1] = {vertices[i], vertices[j], w};
    }

    int edges_added = n - 1;
    while (edges_added < edge_count) {
        int u = uniform_int_distribution<>(0, n - 1)(gen);
        int v = uniform_int_distribution<>(0, n - 1)(gen);
        if (u != v && cost[u][v] == INT_MAX) {
            int w = weight_dist(gen);
            cost[u][v] = w;
            cost[v][u] = w;
            edges[edges_added] = {u, v, w};
            edges_added++;
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

void forward_subst(int** cost, int n, int* f_dist, edgeInfo* edge, int edges) {
    int* dist = new int[n];
    f_dist[n - 1] = 0;

    for (int j = n - 2; j >= 0; j--) {
        int r = find_min_vertex(j, cost, f_dist, edge, edges);
        if (r != -1) {
            f_dist[j] = cost[j][r] + f_dist[r];
            dist[j] = r;
        } else {
            f_dist[j] = INT_MAX;
        }
    }
    delete[] dist;
}

int main() {
    ofstream size_file("size.csv");
    ofstream time_file("time.csv");
    ofstream vert_file("vertices.csv");

    random_device rd;
    mt19937 gen(rd());

    for (int n = 10; n <= 10000; n *= 2) {
        int max_possible_edges = n * (n - 1) / 2;
        int edge_count = uniform_int_distribution<>(n - 1, min(max_possible_edges, 5 * n))(gen);

        int** cost = new int*[n];
        edgeInfo* edges = new edgeInfo[edge_count];
        int* f_dist = new int[n];

        generate_random_graph(cost, edges, n, edge_count);

        auto start = high_resolution_clock::now();
        const int runs = 10;
        for (int k = 0; k < runs; k++) {
            forward_subst(cost, n, f_dist, edges, edge_count);
        }
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;

        size_file << edge_count << "\n";
        vert_file << n << endl;
        time_file << elapsed.count() / runs << "\n";

        cout << "n=" << n << ", edges=" << edge_count
             << ", time=" << elapsed.count() / runs << "s\n";

        for (int i = 0; i < n; i++) delete[] cost[i];
        delete[] cost;
        delete[] edges;
        delete[] f_dist;
    }

    size_file.close();
    time_file.close();
    vert_file.close();
    cout << "CSV files generated successfully!\n";
    return 0;
}
