#include <iostream>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <ctime>
using namespace std;

void generate_values(float** arr, int size) {
    srand(time(0));
    for (int j = 0; j < size; j++) {
        arr[0][j] = rand() % 10 + 1;  
        arr[1][j] = arr[0][j] + rand() % 10 + 1; 
        arr[2][j] = arr[1][j] - arr[0][j];
    }
}

int partition(float** arr, int idx, int low, int high) {
    float pivot = arr[idx][high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[idx][j] <= pivot) {
            i++;
            swap(arr[0][i], arr[0][j]);
            swap(arr[1][i], arr[1][j]);
            swap(arr[2][i], arr[2][j]);
        }
    }
    swap(arr[0][i + 1], arr[0][high]);
    swap(arr[1][i + 1], arr[1][high]);
    swap(arr[2][i + 1], arr[2][high]);
    return i + 1;
}

void quickSort(float** arr, int idx, int low, int high) {
    if (low < high) {
        int p = partition(arr, idx, low, high);
        quickSort(arr, idx, low, p - 1);
        quickSort(arr, idx, p + 1, high);
    }
}

int activity_selection(int size, float** arr, int sortIdx) {
    quickSort(arr, sortIdx, 0, size - 1);  

    int count = 1, lastEndTime = arr[1][0]; 
    for (int i = 1; i < size; i++) {
        if (arr[0][i] >= lastEndTime) {  
            count++;
            lastEndTime = arr[1][i];
        }
    }
    return count;
}

int main() {
    cout << left << setw(10) << "Size" << setw(10) << "Start" << setw(10) << "End" << setw(10) << "Duration" << endl;
    cout << string(40, '-') << endl;
    for(int size = 2; size<=100000; size*=2){
        float** arr = new float*[3];  
    for (int i = 0; i < 3; i++) {
        arr[i] = new float[size];
    }

    generate_values(arr, size);

    int startTimeBased = activity_selection(size, arr, 0);
    int endTimeBased = activity_selection(size, arr, 1);
    int durationBased = activity_selection(size, arr, 2);
    cout << left << setw(10) << size << setw(10) <<startTimeBased << setw(10) << endTimeBased << setw(10) <<durationBased<<endl;
    for (int i = 0; i < 3; i++) delete[] arr[i];
    delete[] arr;
    }
    return 0;
}