#include <iostream>
#include <chrono>
#include <fstream>
using namespace std::chrono;
using namespace std;
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
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
    for (int i = 2; i <= 50000; i*=2) {
        int* arr = new int[i]; 
        for (int l = 0; l < i; l++) arr[l] = l;
        auto start = high_resolution_clock::now();
        for (int k = 0; k < 150; k++) {
            int* tempArr = new int[i];
            copy(arr, arr + i, tempArr);
            insertionSort(tempArr, i);
            delete[] tempArr;
        }
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<nanoseconds>(end - start)/150;
        file << i <<endl;
        f << dur.count()<<endl;  
    }
    file.close();f.close();
}



// clock_t start = clock();
// insertionSort(arr);
// clock_t end = clock();

// double time_taken = double(end - start) / CLOCKS_PER_SEC;
