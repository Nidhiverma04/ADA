#include <iostream>
#include <random>
#include<ctime>
using namespace std;

int** add(int** a, int** b, int n){
    int** ans = new int*[n];
    for(int i=0;i<n;i++){
        ans[i] = new int[n];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ans[i][j] = a[i][j] + b[i][j];
        }
    }

    return ans;
}

int** subt(int** a, int** b, int n){
    int** ans = new int*[n];
    for(int i=0;i<n;i++){
        ans[i] = new int[n];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ans[i][j] = a[i][j] - b[i][j];
        }
    }

    return ans;
}

int** conventional_mult(int** a, int** b , int n){
    int** ans = new int*[n];
    for(int i=0;i<n;i++){
        ans[i] = new int[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ans[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ans[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    return ans;
}

int** matrix_mult(int** a, int** b, int n) {

    if(n<=2){
        return conventional_mult(a, b, n);
    }

    int** a00 = new int*[n/2];
    int** a01 = new int*[n/2];
    int** a10 = new int*[n/2];
    int** a11 = new int*[n/2];
    int** b00 = new int*[n/2];
    int** b01 = new int*[n/2];
    int** b10 = new int*[n/2];
    int** b11 = new int*[n/2];
    
    for(int i=0;i<n/2;i++){
        a00[i] = new int[n/2];
        a01[i] = new int[n/2];
        a10[i] = new int[n/2];
        a11[i] = new int[n/2];
        b00[i] = new int[n/2];
        b01[i] = new int[n/2];
        b10[i] = new int[n/2];
        b11[i] = new int[n/2];
    }
    for(int i =0;i<n/2;i++){
        for(int j=0;j<n/2;j++){
            a00[i][j] = a[i][j];
            a01[i][j] = a[i][j+ n/2];
            a10[i][j] = a[i+ n/2][j];
            a11[i][j] = a[i+n/2][j+n/2];
            b00[i][j] = b[i][j];
            b01[i][j] = b[i][j+ n/2];
            b10[i][j] = b[i+ n/2][j];
            b11[i][j] = b[i+n/2][j+n/2];
        }
    }


    int** P = matrix_mult( add(a00, a11, n/2) , add(b00, b11, n/2), n/2);
    int** Q = matrix_mult( add(a10, a11, n/2) , b00, n/2);
    int** R = matrix_mult( a00 , subt(b01, b11, n/2), n/2);
    int** S = matrix_mult( a11 , subt(b10, b00, n/2), n/2);
    int** T = matrix_mult( add(a00, a01, n/2) , b11, n/2);
    int** U = matrix_mult( subt(a10, a00, n/2) , add(b00, b01, n/2), n/2);
    int** V = matrix_mult( subt(a01, a11, n/2) , add(b10, b11, n/2), n/2);
    cout<<"done\n";

    int** c00 = new int*[n/2];
    int** c01 = new int*[n/2];
    int** c10 = new int*[n/2];
    int** c11 = new int*[n/2];
    for(int i=0;i<n/2;i++){
        c00[i] = new int[n/2];
        c01[i] = new int[n/2];
        c10[i] = new int[n/2];
        c11[i] = new int[n/2];
    }

    c00 = add(add(P, S, n/2), subt(V, T, n/2), n/2); 
    c01 = add(R, T, n/2);
    c10 = add(Q, S, n/2);
    c11 = add(add(P, R, n/2) , subt(U, Q, n/2), n/2);

    int** c = new int*[n];
    for(int i=0;i<n;i++){
        c[i] = new int[n];
    }

    for(int i=0;i<n/2;i++){
        for(int j=0;j<n/2;j++){
            c[i][j] = c00[i][j];
            c[i][j+ n/2] = c01[i][j];
            c[i+ n/2][j] = c10[i][j];
            c[i+ n/2][j+ n/2] = c11[i][j];
        }
    }

    return c;
}

int main() {
    cout << "Enter size: ";
    int size;
    cin >> size;

    srand(time(0));

    int** arr = new int*[size];
    int** b = new int*[size];
    int** ans = new int*[size];

    for (int i = 0; i < size; i++) {
        arr[i] = new int[size];
        b[i] = new int[size];
        ans[i] = new int[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = rand() % 10;
            b[i][j] = rand() % 20;
            ans[i][j] = 0;
        }
    }

    ans = matrix_mult(arr, b, size);
    cout << "\nStrassen's Matrix Multiplication Result: \n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nStandard Matrix Multiplication Result: \n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int v = 0;
            for (int k = 0; k < size; k++) {
                v += arr[i][k] * b[k][j];
            }
            cout << v << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < size; i++) {
        delete[] arr[i];
        delete[] b[i];
        delete[] ans[i];
    }
    delete[] arr;
    delete[] b;
    delete[] ans;

    return 0;
}
