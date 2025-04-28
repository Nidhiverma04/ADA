#include<iostream>
using namespace std;
void print(int* arr, int* x, int n){
    
    cout<<"Solution: "<<endl;
    for(int i=0;i<n;i++){
        if(x[i] == 1){
            cout<<arr[i]<<" ";
        }
    }
    cout<<endl;
}

void sum_subsequence(int k, int* x, int* arr, int s, int r, int m, int n){
    if(k>=n) {
        if(s == m) print(arr, x, n);
        return;
    }
    else { //include
        x[k] = 1;
        if(s + arr[k] <= m) sum_subsequence(k + 1, x, arr, s+arr[k], r-arr[k], m, n);
    }

    if(s + r - arr[k] >= m) {
        x[k] = 0;
        sum_subsequence(k + 1, x, arr, s, r - arr[k], m, n);
    }
}

int main(){
    cout<<"Enter size: ";
    int n, s = 0, m;
    cin>>n;
    cout<<"Enter elements : ";
    int* arr = new int[n];
    int* x = new int[n];
    for(int i = 0;i<n;i++){
        cin>>arr[i];
        s+=arr[i];
        x[i] = 0;
    }

    cout<<"Enter the sum : ";
    cin>>m;
    sum_subsequence(0, x, arr, 0, s, m, n);
}
