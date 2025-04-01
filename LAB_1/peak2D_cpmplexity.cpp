#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <climits>
using namespace std;

int peak_2d(int** arr, int row, int start_col, int col) {
    if (start_col > col)
        return -1;

    int mid = (start_col + col) / 2;
    int maximum = INT_MIN;
    int idx = 0;

    for (int i = 0; i < row; i++) {
        if (maximum < arr[i][mid]) {
            maximum = arr[i][mid];
            idx = i;
        }
    }

    if (mid > 0 && mid < col - 1) {  
        if (maximum > arr[idx][mid + 1] && maximum > arr[idx][mid - 1])
            return maximum;
    }

    if (mid + 1 < col && maximum < arr[idx][mid + 1])
        return peak_2d(arr, row, mid + 1, col);

    if (mid > 0 && maximum < arr[idx][mid - 1])
        return peak_2d(arr, row, start_col, mid - 1);

    return maximum; 
}

int main() {
    ofstream file("size.csv"), f("time.csv");
    srand(time(0));
    for (long long i = 32; i <= 10000; i *= 2) { 
        int** arr = new int*[i]; 
        for (int j = 0; j < i; j++) {
            arr[j] = new int[i];
        }

        for (int l = 0; l < i; l++) {
            for (int m = 0; m < i; m++) {
                arr[l][m] = rand() % 1000;
            }
        }

        clock_t start = clock();
        for (int k = 0; k < 10000; k++) {
            int idx = peak_2d(arr, i, 0, i - 1);
        }
        clock_t end = clock();
        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        file << i << endl;
        f << time_taken / 10000 << endl; 

        for (int j = 0; j < i; j++) {
            delete[] arr[j];
        }
        delete[] arr;
    }

    file.close();
    f.close();
}
