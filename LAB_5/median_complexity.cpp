#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <chrono>
#include <climits>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;


int partition(int arr[], int low, int high) {
   
    int mid = low + (high - low) / 2;
    if (arr[high] < arr[low]) swap(arr[low], arr[high]);
    if (arr[mid] < arr[low]) swap(arr[mid], arr[low]);
    if (arr[high] < arr[mid]) swap(arr[mid], arr[high]);
    
    int pivot = arr[mid];
    swap(arr[mid], arr[high-1]);
    
    int i = low;
    for (int j = low; j < high-1; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high-1]);
    return i;
}

int quickSelect(int arr[], int low, int high, int k) {
    while (true) {
        if (low == high) return arr[low];
        
        int pivotIndex = partition(arr, low, high);
        
        if (pivotIndex == k) {
            return arr[pivotIndex];
        } else if (pivotIndex < k) {
            low = pivotIndex + 1;
        } else {
            high = pivotIndex - 1;
        }
    }
}

double findMedian(int arr[], int n) {
    if (n % 2 != 0) {
        return quickSelect(arr, 0, n - 1, n / 2);
    } else {
        
        int mid1 = n/2 - 1;
        int mid2 = n/2;
        quickSelect(arr, 0, n - 1, mid1);
        
        quickSelect(arr, mid1 + 1, n - 1, mid2);
        return (arr[mid1] + arr[mid2]) / 2.0;
    }
}

int main() {
    ofstream size_file("size.csv"), time_file("time.csv");
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000);
   
    for (int n = 3; n <= 10000; n =static_cast<int>(n * log2(n))) {
        int* arr = new int[n];
        
        
        for (int i = 0; i < n; i++) {
            arr[i] = dist(gen);
        }

        
        findMedian(arr, n);
        
        
        auto start = high_resolution_clock::now();
        
        
        int runs = n < 1000 ? 10000 : 
                  n < 10000 ? 1000 : 
                  n < 100000 ? 100 : 10;
        
        for (int i = 0; i < runs; i++) {
            
            int* temp = new int[n];
            copy(arr, arr + n, temp);
            findMedian(temp, n);
            delete[] temp;
        }
        
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;

        size_file << n << "\n";
        time_file << elapsed.count()/runs << "\n";

        cout << "Size: " << n << " Time: " << elapsed.count()/runs << " seconds\n";

        delete[] arr;
    }

    size_file.close();
    time_file.close();
    cout << "CSV files generated successfully!\n";

    return 0;
}