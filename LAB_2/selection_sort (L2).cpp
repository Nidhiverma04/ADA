#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include<ctime>

using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int idx = i;
        for(int j = i+1;j<n;j++){
            if(arr[i]>arr[j]){
                idx = j;
            }
        } 
        swap(arr[i], arr[idx]);  
    }
}

int main() {
    ofstream file, f;
    file.open("size.csv");
    f.open("time.csv");

    for (int i = 3; i <= 25000; i*=2) {
        int* arr = new int[i]; 
        for (int l = 0; l < i; l++) {
            arr[l] = i-l;
        }

        clock_t start = clock();
        for (int k = 0; k < 100; k++) {
            int* tempArr = new int[i];
            copy(arr, arr + i, tempArr);
            selectionSort(tempArr, i);
            delete[] tempArr;
        }
        clock_t end = clock();

        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        file << i <<", ";
        f << time_taken/100<<", ";
        delete[] arr;  
    }

    file.close();
    f.close();
    cout << "done";
}
