#include <iostream>
#include <climits>

using namespace std;

#define INF INT_MAX

void generate_vertices(int** cost, int n, int edges) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = (i == j) ? 0 : INF;
        }
    }

    cout << "Enter edges (source, destination, weight):\n";
    for (int k = 0; k < edges; k++) {
        int i, j, w;
        cin >> i >> j >> w;

        if (i >= 0 && i < n && j >= 0 && j < n && w >= 0) {
            cost[i][j] = w;
            cost[j][i] = w;  
        } else {
            cout << "Invalid input! Edge not added.\n";
            k--;
        }
    }
}

int tsp(int pos, int visited_mask, int n, int** cost, int** dp, int** path) {
    if (visited_mask == (1 << n) - 1)  // All cities visited
        return cost[pos][0]; 

    if (dp[pos][visited_mask] != -1) 
        return dp[pos][visited_mask];

    int minCost = INF, bestCity = -1;

    for (int city = 0; city < n; city++) {
        if ((visited_mask & (1 << city)) == 0 && cost[pos][city] != INF) {
            int newMask = visited_mask | (1 << city);
            int newCost = cost[pos][city] + tsp(city, newMask, n, cost, dp, path);
            
            if (newCost < minCost) {
                minCost = newCost;
                bestCity = city;
            }
        }
    }

    path[pos][visited_mask] = bestCity;
    return dp[pos][visited_mask] = minCost;
}

void printPath(int n, int** path) {
    int pos = 0, visited_mask = 1;
    cout << "Optimal Path: " << pos;

    for (int i = 1; i < n; i++) {
        int nextCity = path[pos][visited_mask];
        if (nextCity == -1) break;
        cout << " --> " << nextCity;
        visited_mask |= (1 << nextCity);
        pos = nextCity;
    }

    cout << " --> 0\n";  
}

int main() {
    int n, edges;
    cout << "Enter number of cities: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> edges;

    int** cost = new int*[n];
    for (int i = 0; i < n; i++) {
        cost[i] = new int[n];
    }

    generate_vertices(cost, n, edges);

    int** dp = new int*[n];
    int** path = new int*[n];

    for (int i = 0; i < n; i++) {
        dp[i] = new int[1 << n];
        path[i] = new int[1 << n];
        for (int j = 0; j < (1 << n); j++) {
            dp[i][j] = -1;
            path[i][j] = -1;
        }
    }

    int minCost = tsp(0, 1, n, cost, dp, path);

    if (minCost == INF) {
        cout << "No valid tour exists.\n";
    } else {
        cout << "Minimum cost of travelling: " << minCost << endl;
        printPath(n, path);
    }

    for (int i = 0; i < n; i++) {
        delete[] cost[i];
        delete[] dp[i];
        delete[] path[i];
    }
    delete[] cost;
    delete[] dp;
    delete[] path;

    return 0;
}
