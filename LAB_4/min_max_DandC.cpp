#include <iostream>
#include <random>
#include<ctime>
#include<algorithm>
using namespace std;
void max_min(int* arr, int i, int j,  int& maximum, int& minimum){
    if(i==j){
        maximum = max(maximum, arr[i]);
        minimum = min(minimum, arr[i]);
    
        return;
    }
    else if(i == j-1){
        if(arr[i] > arr[j]){
            maximum = max(maximum, arr[i]);
            minimum = min(minimum, arr[j]);
        }
        else{
            maximum = max(minimum, arr[j]);
            minimum = min(maximum, arr[i]);
        }
    
        return;
    }
    else{
        int mid = (j + i)/2;
        int maximum1 = arr[mid+1], minimum1 = arr[mid+1];

        max_min(arr, i, mid, maximum, minimum);
        max_min(arr, mid+1,j,maximum1, minimum1);

        if(maximum < maximum1){
            maximum = maximum1;
        }
        if(minimum > minimum1){
            minimum = minimum1;
        }

        return;
    }
}

int main() {
    cout << "Enter size: ";
    int size;
    cin >> size;

    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
            arr[i] = rand() % 50;
    }

    int maximum = INT32_MIN;
    int minimum = INT32_MAX;
    max_min(arr, 0, size-1,maximum, minimum);

    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }

    cout<<"\nMax : "<<maximum<<" Min : "<<" "<<minimum;
;}