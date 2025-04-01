#include <iostream>
#include <fstream>
#include<ctime>
#include<cmath>
using namespace std;
int power(int a, int b){
    if(a == 1){
        return 1;
    }
    if(b == 0)
        return 1;
    
    int res = 1;
    
    while(b > 0){
        if(b%2 == 1)
            res*=a;
        a*=a;
        b/=2;   
    }
    return res;
}

int main() {
    ofstream file, f;
    file.open("size.csv");
    f.open("time.csv");
    for (int i = 3; i <= 5000; i = i * log2(i)) { 
        clock_t start = clock();
        int a  = rand()%1000 + 1;
        int b = i*i + 100;
        for (int k = 0; k < 100000; k++) {
            int idx = power(a, b);
        }
        clock_t end = clock();
        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        file << b <<endl;
        f <<time_taken/100000<<endl; 
    }
    file.close();
    f.close();
}

