#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    ofstream file, f;
    file.open("size.csv");
    f.open("time.csv");


    for (int i = 300; i <= 30000; i += 5) {
        int* arr = new (nothrow) int[i]; // Safe memory allocation
        if (!arr) {
            cout << "Memory allocation failed for size: " << i << endl;
            break;
        }

        for (int l = 0; l < i; l++) {
            arr[l] = l;
        }

        clock_t start = clock();
        for (int k = 0; k < 100; k++) {
            insertionSort(arr, i);
        }
        clock_t end = clock();

        double time_taken = double(end - start) / (100.0 * CLOCKS_PER_SEC);

        // Avoid trailing commas
        if (i > 300) {
            file << ", ";
            f << ", ";
        }
        file << i;
        f << time_taken;

        delete[] arr;  // Free allocated memory

        // Print progress every 1000 steps
        if (i % 1000 == 0) {
            cout << "Processed size: " << i << endl;
        }
    }

    file.close();
    f.close();
    cout << "done" << endl;
    return 0;
}
