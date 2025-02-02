#include<iostream>
#include<ctime>
#include<random>
#include<fstream>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low, j = high;

    while (i < j) {
        while (i <= high && arr[i] <= pivot) i++;
        while (j >= low && arr[j] > pivot) j--;
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[low], arr[j]);
    return j;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

int main() {
    ofstream file, f;
    file.open("time.csv");
    f.open("size.csv");

    for(int n = 13;n<90000; n = n*log2(n)){
        int arr[n];

        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
        clock_t start = clock();
        for(int i = 0;i<10;i++){
            quickSort(arr, 0, n - 1);
        }
        clock_t end = clock();
        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        file<<time_taken/10<<", ";
        f<<n<<", ";
        cout<<n<<" ";
    }

    cout<<"\ndone at end";
    return 0;
}
