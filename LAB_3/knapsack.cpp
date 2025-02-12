#include <iostream>
#include <random>
#include <algorithm>
#include <unordered_map>
using namespace std;

void generate_values(float** arr, int size) {
    for (int j = 0; j < size; j++) {
        arr[0][j] = rand() % 7 + 1;
        arr[1][j] = rand() % 20 + 1;
        arr[2][j] = float(arr[1][j]) / arr[0][j];
    }
}

int partition(float** arr, int idx, int low, int high) {
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
    float** prof = new float*[2];
    for (int i = 0; i < 2; i++) {
        prof[i] = new float[size]{};
    }
    for (int i = 0; i < size; i++) {
        if (arr[0][i] <= cap) {
            prof[0][i] = 1;
            cap -= arr[0][i];
        } else {
            prof[0][i] = float(cap) / arr[0][i];
            break;
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
    int size = 6, cap = 20;
    float** arr = new float*[3];  
    for (int i = 0; i < 3; i++) {
        arr[i] = new float[size];
    }
    generate_values(arr, size);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    int weightBased = knapsack_solution(size, arr, cap, 0);
    int profitBased = knapsack_solution(size, arr, cap, 1);
    int ratioBased = knapsack_solution(size, arr, cap, 2);
    cout << weightBased << " " << profitBased << " " << ratioBased;
    for (int i = 0; i < 3; i++) delete[] arr[i];
    delete[] arr;
    return 0;
}