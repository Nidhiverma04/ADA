#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_SOLUTIONS = 100; 
bool place(int k, int i, int* x) {
    for (int j = 0; j < k; j++) {
        if (x[j] == i || abs(j - k) == abs(x[j] - i)) {
            return false;
        }
    }
    return true;
}

void print(int* x, int n) {
    cout << "\nSolution:\n";
    for (int p = 0; p < n; p++) {
        for (int q = 0; q < n; q++) {
            cout << (x[p] == q ? "Q" : "_ ");
        }
        cout << endl;
    }
}

void generateMirrors(int* x, int n) {
    int mirrored[n];

    print(x, n);

    // Horizontal mirror (flip rows)
    for (int i = 0; i < n; i++) mirrored[i] = x[n - 1 - i];
    print(mirrored, n);

    // Vertical mirror (flip columns)
    for (int i = 0; i < n; i++) mirrored[i] = n - 1 - x[i];
    print(mirrored, n);

   
    for (int i = 0; i < n; i++) mirrored[x[i]] = i;
    print(mirrored, n);
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
    cout << "Enter the number of queens: ";
    int n;
    cin >> n;
    int x[n];
    int solutions[MAX_SOLUTIONS][100]; 
    int sol_count = 0;

    NQueens(0, n, x, solutions, sol_count);

   
    for (int i = 0; i < sol_count; i++) {
        generateMirrors(solutions[i], n);
    }

    return 0;
}