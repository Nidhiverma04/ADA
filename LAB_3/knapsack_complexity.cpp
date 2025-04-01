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
    for (int j = 0; j < size; j++) {
        arr[0][j] = rand() % 7 + 1;
        arr[1][j] = rand() % 20 + 1;
        arr[2][j] = float(arr[1][j]) / arr[0][j];
    }
}

int partition(float** arr, int idx, int low, int high) {
    int pivot_idx = low + rand() % (high - low + 1);
    swap(arr[idx][pivot_idx], arr[idx][high]); 
    float pivot = arr[idx][high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[idx][j] >= pivot) {
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

float** knapsack(float** arr, int cap, int size) {
    if (cap <= 0 || size == 0) return nullptr; 
    float** prof = new float*[2];
    for (int i = 0; i < 2; i++) prof[i] = new float[size]();
    for (int i = 0; i < size && cap > 0; i++) {  
        if (arr[0][i] <= cap) {
            prof[0][i] = 1;
            cap -= arr[0][i];
        } else {
            prof[0][i] = static_cast<float>(cap) / arr[0][i];
            cap = 0;  
        }
    }
    return prof;
}

int knapsack_solution(int size, float** arr, int cap, int sortIdx) {
    quickSort(arr, sortIdx, 0, size - 1);
    float** profit = knapsack(arr, cap, size);
    int amt = 0;
    for (int i = 0; i < size; i++) {
        amt += profit[0][i] * arr[1][i];
    }
    for (int i = 0; i < 2; i++) delete[] profit[i];
    delete[] profit;
    return amt;
}

int main() {
    ofstream file, f;
    file.open("size.csv");
    f.open("time.csv");
    for(int i = 2; i<=25000; i= i*2){

        int cap = i * (rand() % 10 + 1); 

        float** arr = new float*[3];  
        for (int idx = 0; idx < 3; idx++) {
            arr[idx] = new float[i];
        }

        generate_values(arr, i);
       
        auto start = std::chrono::high_resolution_clock::now();
        for(int k = 0;k<100;k++){
            int ratioBased = knapsack_solution(i, arr, cap, 2);
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


