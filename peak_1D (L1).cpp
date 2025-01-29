// 23 jan 2025 Q1
#include<iostream>
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

int main(){
    cout<<"Enter size: ";
    int n;
    cin>>n;
    cout<<"Enter elements : ";
    int arr[n];
    for(int i = 0;i<n;i++){
        cin>>arr[i];
    }
    
    if((arr[0] > arr[1])){
        return 0;
    }
    if((arr[n-1] > arr[n-2])){
        return n-1;
    }
    
    int idx = peak_1d(arr,n, 0, n-1);
    if(idx!=-1)
        cout<<"Peak element : "<< arr[idx];

    else
        cout<<"No Peak found !";

    return 0;
}
