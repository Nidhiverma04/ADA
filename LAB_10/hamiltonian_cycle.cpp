#include <iostream>
using namespace std;

void write(int* path, int n) {
    for (int i = 0; i < n; i++) {
        cout << path[i] + 1 << (i == n - 1 ? " -> " : " -> ");
    }
    cout << path[0] + 1 << endl;
}

void nextVal(int k, int* x, int** cost, int n) {
    while (1) {
        if (x[k] + 1 == n) {
            x[k] = -1;
        } else {
            x[k] = x[k] + 1;
        }
        if (x[k] == -1) return;

        if (k == 0 || cost[x[k - 1]][x[k]] != 0) {
            int i = 0;
            while (i < k) {
                if (x[i] == x[k]) break;
                i++;
            }
            if (i == k) {
                if ((k == n - 1 && cost[x[k]][x[0]] != 0) || k < n - 1)
                    return;
            }
        }
    }
}

void backtrack(int k, int* x, int** cost, int n) {
    do {
        nextVal(k, x, cost, n);
        if (x[k] == -1) return;
        if (k == n - 1) {
            write(x, n);
        } else {
            backtrack(k + 1, x, cost, n);
        }
    } while (true);
}

int main() {
    int n = 6;
    int** cost = new int*[n];
    int* x = new int[n];
    for (int i = 0; i < n; i++) {
        x[i] = -1;
        cost[i] = new int[n];
    }

    int matrix[6][6] = {
        {0, 1, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0},
        {1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1},
        {0, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 0}
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = matrix[i][j];

    backtrack(0, x, cost, n);

    for (int i = 0; i < n; i++) delete[] cost[i];
    delete[] cost;
    delete[] x;

    return 0;
}
