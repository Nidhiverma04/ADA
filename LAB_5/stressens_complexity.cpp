#include <iostream>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include<ctime>
#include<chrono>
#include<cmath>
using namespace std;
using namespace std::chrono;

// Helper function to delete a 2D array
void freeMatrix(int** matrix, int n) {
    for(int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

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

    int half = n/2;
    
    // Allocate submatrices
    int** a00 = new int*[half];
    int** a01 = new int*[half];
    int** a10 = new int*[half];
    int** a11 = new int*[half];
    int** b00 = new int*[half];
    int** b01 = new int*[half];
    int** b10 = new int*[half];
    int** b11 = new int*[half];
    
    for(int i=0;i<half;i++){
        a00[i] = new int[half];
        a01[i] = new int[half];
        a10[i] = new int[half];
        a11[i] = new int[half];
        b00[i] = new int[half];
        b01[i] = new int[half];
        b10[i] = new int[half];
        b11[i] = new int[half];
        
        for(int j=0;j<half;j++){
            a00[i][j] = a[i][j];
            a01[i][j] = a[i][j+half];
            a10[i][j] = a[i+half][j];
            a11[i][j] = a[i+half][j+half];
            
            b00[i][j] = b[i][j];
            b01[i][j] = b[i][j+half];
            b10[i][j] = b[i+half][j];
            b11[i][j] = b[i+half][j+half];
        }
    }

    // Calculate intermediate matrices
    int** a00_a11 = add(a00, a11, half);
    int** b00_b11 = add(b00, b11, half);
    int** a10_a11 = add(a10, a11, half);
    int** b01_b11 = subt(b01, b11, half);
    int** b10_b00 = subt(b10, b00, half);
    int** a00_a01 = add(a00, a01, half);
    int** a10_a00 = subt(a10, a00, half);
    int** b00_b01 = add(b00, b01, half);
    int** a01_a11 = subt(a01, a11, half);
    int** b10_b11 = add(b10, b11, half);

    int** P = matrix_mult(a00_a11, b00_b11, half);
    int** Q = matrix_mult(a10_a11, b00, half);
    int** R = matrix_mult(a00, b01_b11, half);
    int** S = matrix_mult(a11, b10_b00, half);
    int** T = matrix_mult(a00_a01, b11, half);
    int** U = matrix_mult(a10_a00, b00_b01, half);
    int** V = matrix_mult(a01_a11, b10_b11, half);

    // Free intermediate matrices
    freeMatrix(a00_a11, half);
    freeMatrix(b00_b11, half);
    freeMatrix(a10_a11, half);
    freeMatrix(b01_b11, half);
    freeMatrix(b10_b00, half);
    freeMatrix(a00_a01, half);
    freeMatrix(a10_a00, half);
    freeMatrix(b00_b01, half);
    freeMatrix(a01_a11, half);
    freeMatrix(b10_b11, half);

    // Calculate result submatrices
    int** temp1 = add(P, S, half);
    int** temp2 = subt(V, T, half);
    int** c00 = add(temp1, temp2, half);
    int** c01 = add(R, T, half);
    int** c10 = add(Q, S, half);
    int** temp3 = add(P, R, half);
    int** temp4 = subt(U, Q, half);
    int** c11 = add(temp3, temp4, half);

    // Free temporary matrices
    freeMatrix(temp1, half);
    freeMatrix(temp2, half);
    freeMatrix(temp3, half);
    freeMatrix(temp4, half);
    freeMatrix(P, half);
    freeMatrix(Q, half);
    freeMatrix(R, half);
    freeMatrix(S, half);
    freeMatrix(T, half);
    freeMatrix(U, half);
    freeMatrix(V, half);

    // Free input submatrices
    freeMatrix(a00, half);
    freeMatrix(a01, half);
    freeMatrix(a10, half);
    freeMatrix(a11, half);
    freeMatrix(b00, half);
    freeMatrix(b01, half);
    freeMatrix(b10, half);
    freeMatrix(b11, half);

    // Combine results
    int** c = new int*[n];
    for(int i=0;i<n;i++){
        c[i] = new int[n];
    }

    for(int i=0;i<half;i++){
        for(int j=0;j<half;j++){
            c[i][j] = c00[i][j];
            c[i][j+half] = c01[i][j];
            c[i+half][j] = c10[i][j];
            c[i+half][j+half] = c11[i][j];
        }
    }

    // Free result submatrices
    freeMatrix(c00, half);
    freeMatrix(c01, half);
    freeMatrix(c10, half);
    freeMatrix(c11, half);

    return c;
}

int main() {
    srand(time(0));
    ofstream file, f;
    file.open("size.csv");
    f.open("time.csv");
    for(int i = 16; i<=2000; i= i*2){
        int size = i;

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
       
        auto start = high_resolution_clock::now();
        for(int k = 0; k < 10; k++){
            int** temp = matrix_mult(arr, b, size);
            if(k > 0) {  // Don't free the first result (we want to keep the last one)
                freeMatrix(ans, size);
            }
            ans = temp;
        }
        auto end = high_resolution_clock::now();
        double time_taken = duration<double>(end - start).count();

        file << i << endl;
        f << time_taken/10 << endl; 
    
        // Free all memory
        freeMatrix(arr, size);
        freeMatrix(b, size);
        freeMatrix(ans, size);
    }
    f.close();
    file.close();
    cout << "done";
    return 0;
}