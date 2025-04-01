#include<iostream>
#include<ctime>
#include<cmath>
#include<fstream>
using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    ofstream file("time.csv"), f("size.csv");

    for (int n = 13; n < 90000; n = n * log2(n)) {
        int arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }

        clock_t start = clock();
        for (int i = 0; i < 100; i++) {
            heapSort(arr, n);
        }
        clock_t end = clock();

        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        file << time_taken / 100 <<endl;
        f << n <<endl;
    }
}


