#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>

using namespace std::chrono;
using namespace std;

void magicSquare(int** arr, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = 0;

    int row = 0, col = n / 2;
    for (int i = 1; i <= n * n; i++) {
        arr[row][col] = i;

        int new_r = row - 1;
        int new_col = col - 1;

        if (new_r < 0) new_r = n - 1;
        if (new_col < 0) new_col = n - 1;

        if (arr[new_r][new_col] != 0) {
            row += 1;  
        } else {
            row = new_r;
            col = new_col;
        }
    }
}

int main() {
    ofstream file, f;
    file.open("time.csv");
    f.open("size.csv");

    int idx = 0, id = 0;
    for (int i = 2; i <= 25000; i*=2) {
        int s = i+1;
        int** arr = new int* [s];
        for (int j = 0; j <s; j++) {
            arr[j] = new int[s];
        }

        auto start = high_resolution_clock::now();
        for (int q = 0; q < 5; q++) {
            magicSquare(arr, s);
        }
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<microseconds>(end - start)/5;
        file << dur.count() <<", ";
        f << s <<", ";

        for (int j = 0; j < s; j++) {
            delete[] arr[j];
        }
        delete[] arr;
    }

    file.close();
    f.close();
    return 0;
}
