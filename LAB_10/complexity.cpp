#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

const int MAX_SOLUTIONS = 100;

bool place(int k, int i, int* x) {
    for (int j = 0; j < k; j++) {
        if (x[j] == i || abs(j - k) == abs(x[j] - i)) {
            return false;
        }
    }
    return true;
}


void generateMirrors(int* x, int n) {
    int mirrored[n];

    // print(x, n); // Original

    // Horizontal Mirror
    for (int i = 0; i < n; i++) mirrored[i] = x[n - 1 - i];
    // print(mirrored, n);

    // Vertical Mirror
    for (int i = 0; i < n; i++) mirrored[i] = n - 1 - x[i];
    // print(mirrored, n);

    // Diagonal Mirror
    for (int i = 0; i < n; i++) mirrored[x[i]] = i;
    // print(mirrored, n);
}

void NQueens(int k, int n, int* x, int solutions[][100], int& sol_count) {
    for (int i = 0; i < n; i++) {
        if (place(k, i, x)) {
            x[k] = i;
            if (k == n - 1) {
                for (int j = 0; j < n; j++) {
                    solutions[sol_count][j] = x[j];
                }
                sol_count++;
            } else {
                NQueens(k + 1, n, x, solutions, sol_count);
            }
        }
    }
}

int main() {
    ofstream file("mirror_time.csv");
    file << "n,time\n";

    for (int n = 4; n <= 12; n++) {
        int x[n];
        int solutions[MAX_SOLUTIONS][100];
        int sol_count = 0;

        auto start = high_resolution_clock::now();
        NQueens(0, n, x, solutions, sol_count);
        auto end = high_resolution_clock::now();

        duration<double> elapsed = end - start;
        file << n << "," << elapsed.count() << "\n";
        cout << "n = " << n << ", time = " << elapsed.count() << " s\n";

        // Print solutions and their mirrors (not timed)
        for (int i = 0; i < sol_count; i++) {
            generateMirrors(solutions[i], n);
        }
    }

    file.close();
    return 0;
}
