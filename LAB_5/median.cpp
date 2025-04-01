#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    swap(arr[i], arr[high]);
    return i;
}

int quickSelect(int arr[], int low, int high, int k) {
    if (low == high)
        return arr[low];

    int pivotIndex = partition(arr, low, high);

    if (pivotIndex == k)
        return arr[pivotIndex];
    else if (pivotIndex < k)
        return quickSelect(arr, pivotIndex + 1, high, k);
    else
        return quickSelect(arr, low, pivotIndex - 1, k);
}

double findMedian(int arr[], int n) {
    if (n % 2 != 0) 
        return quickSelect(arr, 0, n - 1, n / 2);
    else {
        int mid1 = quickSelect(arr, 0, n - 1, n / 2 - 1);
        int mid2 = quickSelect(arr, 0, n - 1, n / 2);
        return (mid1 + mid2) / 2.0;
    }
}

int main() {
    srand(time(0));
    int n;
    cout<<"Enter size : ";
    cin>>n;
    int arr[n];

    for(int i=0;i<n;i++){
        arr[i] = rand()%100 +1;
        cout<<arr[i]<<", ";
    }
    cout << "\nMedian: " << findMedian(arr, n) << endl;
    return 0;
}
