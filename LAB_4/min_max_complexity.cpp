#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include<chrono>
#include <climits>

using namespace std;
using namespace std::chrono;

void max_min(int* arr, int i, int j, int& maximum, int& minimum) {
    if (i == j) {  
        maximum = max(maximum, arr[i]);
        minimum = min(minimum, arr[i]);
        return;
    } 
    else if (i == j - 1) { 
        if (arr[i] > arr[j]) {
            maximum = max(maximum, arr[i]);
            minimum = min(minimum, arr[j]);
        } else {
            maximum = max(maximum, arr[j]);  
            minimum = min(minimum, arr[i]);  
        }
        return;
    } 
    else {  
        int mid = (i + j) / 2;
        int maximum1 = INT32_MIN, minimum1 = INT32_MAX;  

        max_min(arr, i, mid, maximum, minimum);
        max_min(arr, mid + 1, j, maximum1, minimum1);

        maximum = max(maximum, maximum1);
        minimum = min(minimum, minimum1);
    }
}

int main() {
    ofstream file("size.csv"), f("time.csv");
    srand(time(0));
    

    for (int i = 3; i <= 5000; i = i * log2(i)) {  
        int size = i;
        int* arr = new int[size];

        for (int j = 0; j < size; j++) {  
            arr[j] = rand() % 50;
        }

        auto start = std::chrono::high_resolution_clock::now();
        for (int k = 0; k < 100000; k++) {
            int maximum = INT32_MIN, minimum = INT32_MAX;
            max_min(arr, 0, size - 1, maximum, minimum);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken = std::chrono::duration<double>(end - start).count();

        file << i << endl;
        f << time_taken / 100000 << endl;

        delete[] arr;  
    }

    file.close();
    f.close();
}
