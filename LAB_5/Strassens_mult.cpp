#include <iostream>
#include <random>
#include<ctime>
using namespace std;

void matrix_mult(int** a, int** b, int sr1, int er1, int sc1, int ec1, int sr2, int er2, int sc2, int ec2, int** ans) {
    if (er1 - sr1 < 2 && ec2 - sc2 < 2) {

        int P = (a[sr1][sc1] + a[sr1 + 1][sc1 + 1]) * (a[sr1 + 1][sc1 + 1] + b[sr2][sc2 + 1]);
        int Q = (a[sr1 + 1][sc1] + a[sr1 + 1][sc1 + 1]) *  b[sr2][sc2];
        int R = a[sr1][sc1] * (b[sr2][sc2 + 1] - b[sr2][sc2 + 1]);
        int S = a[sr1 + 1][sc1 + 1] * (b[sr2 + 1][sc2] - b[sr2][sc2 + 1]);
        int T = (a[sr1][sc1] + a[sr1][sc1 + 1]) * b[sr2 + 1][sc2 + 1];
        int U = (a[sr1 + 1][sc1] - a[sr1][sc1]) * ( b[sr2][sc2] + b[sr2][sc2 + 1]);
        int V = (a[sr1][sc1 + 1] - a[sr1 + 1][sc1 + 1]) * (b[sr2+1][sc2] +  b[sr2 + 1][sc2 + 1]);
        cout<<"done\n";

        ans[sr1][sc2] += (P + S - T + V); 
        ans[sr1][sc2 + 1] +=( R + T);
        ans[sr1 + 1][sc2] += (Q + S);
        ans[sr1 + 1][sc2 + 1] += (P + R - Q + U);

        return;
    }
    
}

int main() {
    cout << "Enter size: ";
    int size;
    cin >> size;

    srand(time(0));

    int** arr = new int*[size];
    int** b = new int*[size];
    int** ans = new int*[size];

    for (int i = 0; i < size; i++) {
        arr[i] = new int[size];
        b[i] = new int[size];
        ans[i] = new int[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = rand() % 10;
            b[i][j] = rand() % 20;
            ans[i][j] = 0;
        }
    }

    matrix_mult(arr, b, 0, size - 1, 0, size - 1, 0, size - 1, 0, size - 1, ans);

    cout << "\nStrassen's Matrix Multiplication Result: \n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nStandard Matrix Multiplication Result: \n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int v = 0;
            for (int k = 0; k < size; k++) {
                v += arr[i][k] * b[k][j];
            }
            cout << v << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < size; i++) {
        delete[] arr[i];
        delete[] b[i];
        delete[] ans[i];
    }
    delete[] arr;
    delete[] b;
    delete[] ans;

    return 0;
}
