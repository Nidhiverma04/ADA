#include <iostream>
#include <fstream>
#include<ctime>
#include<cmath>
using namespace std;
int peak_1d(int arr[], int n,int l, int h){
    if(l > h){
        return -1;
    }

    int mid = (l + h) / 2;
    if(mid+1 < n && mid-1 >=0){
        if((arr[mid] > arr[mid+1]) && (arr[mid] > arr[mid-1])){
            return mid;
        }
    }
    if((mid+1 < n) && arr[mid] < arr[mid+1])
        return peak_1d(arr,n,mid+1,h);

    if((mid-1 >= 0) && arr[mid] < arr[mid-1])
        return peak_1d(arr,n,l,mid-1);

    return -1;
}
int main() {
    ofstream file, f;
    file.open("size.csv");
    f.open("time.csv");
    for (int i = 3; i <= 5000; i = i * log2(i)) {
        int* arr = new int[i]; 
        clock_t start = clock();
        for (int l = 0; l < i; l++) arr[l] = rand()%100 + 1;
        for (int k = 0; k < 100000; k++) {
            int idx = peak_1d(arr,i, 0, i-1);
        }
        clock_t end = clock();
        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        file << i <<endl;
        f <<time_taken/100000<<endl;
        delete[] arr;  
    }
    file.close();
    f.close();
}

