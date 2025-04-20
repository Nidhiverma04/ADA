#include <iostream>
#include <climits>
using namespace std;

void print(int** s, int i, int j) {
    if (i == j) {
        cout << "A" << i<<" ";
    } else {
        cout << "( ";
        print(s, i, s[i][j]);
        print(s, s[i][j] + 1, j);
        cout << ") ";
    }
}

void mcm(int* p, int n, int** s, int** m) {
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    for (int l = 2; l < n; l++) { // l = chain length
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of matrices: ";
    cin >> n;
    int* p = new int[n + 1];
    cout << "Enter dimensions (length " << n + 1 << "): ";
    for (int i = 0; i < n + 1; i++) {
        cin >> p[i];
    }

    int** m = new int*[n + 1];
    int** s = new int*[n + 1];
    for (int i = 0; i <= n; i++) {
        m[i] = new int[n + 1];
        s[i] = new int[n + 1];
    }

    mcm(p, n + 1, s, m);

    cout << "Minimum number of scalar multiplications: " << m[1][n] << endl;
    cout << "Optimal Parenthesization: ";
    print(s, 1, n);
    cout << endl;

    for (int i = 0; i <= n; i++) {
        delete[] m[i];
        delete[] s[i];
    }
    delete[] m;
    delete[] s;
    delete[] p;

    return 0;
}
