#include <iostream>
#include <algorithm>
#include <ctime>
#include<fstream>

using namespace std;

void knapsack(int n, int c) {
    int** det = new int*[n];
    for (int i = 0; i < n; i++) {
        det[i] = new int[2];
        det[i][0] = rand() % 10 + 1; // Storage (Weight)
        det[i][1] = rand() % 100;    // Profit (Value)
    }

    int** profit = new int*[n + 1];
    for (int i = 0; i <= n; i++) {
        profit[i] = new int[c + 1];
    }

   
    for (int i = 0; i <= c; i++) {
        profit[0][i] = 0;
    }
    for (int i = 0; i <= n; i++) {
        profit[i][0] = 0;
    }

  
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= c; j++) {
            if (j >= det[i - 1][0]) {
                profit[i][j] = max(profit[i - 1][j], profit[i - 1][j - det[i - 1][0]] + det[i - 1][1]);
            } else {
                profit[i][j] = profit[i - 1][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        delete[] det[i];
    }
    delete[] det;

    for (int i = 0; i <= n; i++) {
        delete[] profit[i];
    }
    delete[] profit;
}

int main() {
    srand(time(0));
    ofstream f("size.csv");
    ofstream f2("time.csv");
    cout << "n\tc\tTime (ms)\n";

    for (int n = 5; n <= 50000; n *= 2) { 
        int c = n * 2; 
        clock_t start = clock();
        knapsack(n, c);
        clock_t end = clock();
        double elapsed_time = 1000.0 * (end - start) / CLOCKS_PER_SEC;
        f << n <<endl;
        f2 << elapsed_time<<endl;
        cout << n << "\t" << c << "\t" << elapsed_time << " ms\n";
    }

    return 0;
}
