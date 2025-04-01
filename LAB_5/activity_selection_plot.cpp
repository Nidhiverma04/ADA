#include <iostream>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include<ctime>
#include<chrono>
#include<cmath>
using namespace std;
using namespace std::chrono;
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
    ofstream file, f;
    file.open("size.csv");
    f.open("time.csv");
    for(int i = 12; i<=10000; i= i*log2(i)){

        float** arr = new float*[3];  
        for (int idx = 0; idx < 3; idx++) {
            arr[idx] = new float[i];
        }

        generate_values(arr, i);
       
        auto start = std::chrono::high_resolution_clock::now();
        for(int k = 0;k<100;k++){
            int ratioBased = activity_selection(i, arr, 1);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken = std::chrono::duration<double>(end - start).count();

        file << i <<endl;
        f <<time_taken/100<<endl; 
    
        for (int i = 0; i < 3; i++) delete[] arr[i];
        delete[] arr;
    }
    f.close();
    file.close();
    cout<<"done";
    return 0;
}


