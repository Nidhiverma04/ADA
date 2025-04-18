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
void generate_values(int** arr, int size, int**ans, int**b) {
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
}

void matrix_mult(int** a, int** b, int sr1, int er1, int sc1, int ec1, int sr2, int er2, int sc2, int ec2, int** ans) {
    if (er1 - sr1 < 2 && ec2 - sc2 < 2) {
        int ans1[2][2];
        ans1[0][0] = a[sr1][sc1] * b[sr2][sc2] + a[sr1][sc1 + 1] * b[sr2 + 1][sc2];
        ans1[0][1] = a[sr1][sc1] * b[sr2][sc2 + 1] + a[sr1][sc1 + 1] * b[sr2 + 1][sc2 + 1];
        ans1[1][0] = a[sr1 + 1][sc1] * b[sr2][sc2] + a[sr1 + 1][sc1 + 1] * b[sr2 + 1][sc2];
        ans1[1][1] = a[sr1 + 1][sc1] * b[sr2][sc2 + 1] + a[sr1 + 1][sc1 + 1] * b[sr2 + 1][sc2 + 1];

        ans[sr1][sc2] += ans1[0][0];
        ans[sr1][sc2 + 1] += ans1[0][1];
        ans[sr1 + 1][sc2] += ans1[1][0];
        ans[sr1 + 1][sc2 + 1] += ans1[1][1];
        return;
    }
    
    int mid1 = sr1 + (er1 - sr1) / 2;
    int mid2 = sc1 + (ec1 - sc1) / 2;
    int mid3 = sr2 + (er2 - sr2) / 2;
    int mid4 = sc2 + (ec2 - sc2) / 2;

    matrix_mult(a, b, sr1, mid1, sc1, mid2, sr2, mid3, sc2, mid4, ans);
    matrix_mult(a, b, sr1, mid1, mid2 + 1, ec1, mid3 + 1, er2, sc2, mid4, ans);
    matrix_mult(a, b, sr1, mid1, sc1, mid2, sr2, mid3, mid4 + 1, ec2, ans);
    matrix_mult(a, b, sr1, mid1, mid2 + 1, ec1, mid3 + 1, er2, mid4 + 1, ec2, ans);
    matrix_mult(a, b, mid1 + 1, er1, sc1, mid2, sr2, mid3, sc2, mid4, ans);
    matrix_mult(a, b, mid1 + 1, er1, mid2 + 1, ec1, mid3 + 1, er2, sc2, mid4, ans);
    matrix_mult(a, b, mid1 + 1, er1, sc1, mid2, sr2, mid3, mid4 + 1, ec2, ans);
    matrix_mult(a, b, mid1 + 1, er1, mid2 + 1, ec1, mid3 + 1, er2, mid4 + 1, ec2, ans);
}

int main() {
    srand(time(0));
    ofstream file, f;
    file.open("conven_size.csv");
    f.open("conven__time.csv");
    for(int i = 16; i<=2000; i= i*2){
        int size =  i;

        int** arr = new int*[size];
        int** b = new int*[size];
        int** ans = new int*[size];


        generate_values(arr, i, ans, b);
       
        auto start = std::chrono::high_resolution_clock::now();
        for(int k = 0;k<10;k++){
            matrix_mult(arr, b, 0, size - 1, 0, size - 1, 0, size - 1, 0, size - 1, ans);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_taken = std::chrono::duration<double>(end - start).count();

        file << i <<endl;
        f <<time_taken/10<<endl; 
    
        for (int i = 0; i < 3; i++) delete[] arr[i];
        delete[] arr;
    }
    f.close();
    file.close();
    cout<<"done";
    return 0;
}


