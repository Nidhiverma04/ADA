#include <iostream>
#include<ctime>
#include <iomanip>
using namespace std;

int binarySearch(int arr[], int x, int n) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;  
        if (arr[mid] == x) {
            return mid;
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;  
}

double measureTime(int n) {
    int* arr = new int[n];  
    for (int i = 0; i < n; ++i) {
        arr[i] = i;  
    }
    int x = INT32_MAX;  

    clock_t start = clock();
    for(int i=0;i<2000;i++){
        binarySearch(arr, x, n);
    }
    clock_t end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;

    delete[] arr;
    cout<<setprecision(30)<<  time_taken/2000<<", ";
    return time_taken/2000;
}

int main() {
    int sizes[25];
    double times[25];
    int n = 2;
    for (int i = 0; i < 25; ++i) {
        n *= 2;
        sizes[i] = n;
        times[i] = measureTime(n);
    }

    cout << "\nSizes for plotting: ";
    for (int i = 0; i < 25; ++i) {
        cout << sizes[i] << ", ";
    }
    cout << "\nTimes for plotting: ";
    for (int i = 0; i < 25; ++i) {
        cout << times[i] << ", ";
    }
    cout << endl;

    return 0;
}