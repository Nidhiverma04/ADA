#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std::chrono;
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

    for (int i = 2; i <= 25000; i*=2) {
        int* arr = new int[i]; 
        for (int l = 0; l < i; l++) {
            arr[l] = rand()%10000;
        }

        auto start = high_resolution_clock::now();
        for (int k = 0; k < 100; k++) {
            int* tempArr = new int[i];
            copy(arr, arr + i, tempArr);
            insertionSort(tempArr, i);
            delete[] tempArr;
        }
        auto end = high_resolution_clock::now();

        auto dur = duration_cast<nanoseconds>(end - start)/100;
        file << i <<", ";
        f << dur.count()<<", ";

        delete[] arr;  
    }

    file.close();
    f.close();
    cout << "done";
}



// clock_t start = clock();
// insertionSort(arr);
// clock_t end = clock();

// double time_taken = double(end - start) / CLOCKS_PER_SEC;
