// 23 jan 2025 Q2
#include<iostream>
#include<algorithm>
using namespace std;

int peak_2d(int** arr, int row, int start_col, int col){
    if(start_col > col)
        return -1;

    int mid = (start_col + col) / 2;
    int maximum = INT32_MIN;
    int idx = 0;

    for(int i = 0; i < row; i++) {
        if (maximum < arr[i][mid]) {
            maximum = arr[i][mid];
            idx = i;
        }
    }

    if((mid + 1 <= col) && (mid - 1 >= 0)){
        cout<< maximum<<" "<<arr[idx][mid+1]<<" "<<arr[idx][mid-1]<<endl;
        if( maximum > arr[idx][mid+1] && (maximum > arr[idx][mid-1]))
            return maximum;
    }

    if((mid+1 <= col )&& maximum < arr[idx][mid+1])
        return peak_2d(arr, row,mid+1,col) ;

    if((mid - 1 >=0) && maximum < arr[idx][mid-1])
        return peak_2d(arr, row,0,mid-1) ;

    return -1;
}

int main(){
    
    cout<<"Enter size (m x n): ";
    int m, n;
    cin>>m>>n;
    cout<<"Enter elements : ";
    int** arr = new int* [m];
    for(int i = 0;i<m;i++){
        arr[i] = new int[n];
    }
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            cin>> arr[i][j];
        }
    }
    
    int element = peak_2d(arr,m,0,n-1);
    if(element != -1){
        cout<<"Peak element: "<<element;
    }
    else
        cout<<"No peak found!";
        
    return 0;
}
