#include<iostream>
#include<algorithm>
using namespace std;

bool place(int k, int i, int* x){
    for(int j=0;j<k;j++){
        if(x[j] == i || abs(j-k) == abs(x[j]-i)){
            return false;
        }
    }
    return true;
}

void print(int* x, int n){
    cout<<endl<<"Solution : "<<endl;
    for(int p = 0;p<n;p++){
        for(int q =0;q<n;q++){
            if(x[p]==q){
                cout<<1<<" ";
            }
            else{
                cout<<0<<" ";
            }
        }
        cout<<endl;
    }
}

void NQueens(int k, int n, int* x){
    for(int i=0;i<n;i++){
        if(place(k, i, x)){

            x[k] = i;
            if(k == n - 1){
                print(x, n);
            }
            else{
                NQueens(k+1, n, x);
            }
        }
    }
}

int main(){
    cout<<"Enter the number of queens : ";
    int n;
    cin>>n;
    int* x = new int[n];
    NQueens(0, n, x);
    delete[] x;
}