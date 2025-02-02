// 23 jan 2025 Q3
#include<iostream>
#include<algorithm>
using namespace std;

void print(int** arr, int n){
    cout<<"Magic Square : "<<endl;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}

void magicSquare(int** arr, int n){
    int row = 0, col = n/2;
    for(int i = 1;i<=n*n;i++){
        arr[row][col] = i;

        int new_r = row - 1;
        int new_col = col - 1;

        if(new_r < 0) new_r = n-1;
        if(new_r >= n) new_r = 0;
        if(new_col < 0) new_col = n-1;
        if(new_col >= n) new_col = 0;

        if(arr[new_r][new_col] != 0){
            row+=1;
        }
        else{
            row = new_r;
            col = new_col;
        }
    }
    print(arr,n);
}

int main(){
    
    cout<<"Enter size (n x n): ";
    int n;
    cin>>n;
    int** arr = new int* [n];
    for(int i = 0;i<n;i++){
        arr[i] = new int[n];
    }
    // fill(&arr[0][0], &arr[0][0] + n * n, 0);
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            arr[i][j] = 0;
        }
    }

    magicSquare(arr,n);
    return 0;
}
