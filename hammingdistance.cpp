#include<iostream>
using namespace std;

int main(){
    int d1, d2;
    cout<<"Enter d1 and d2 : ";
    cin>>d1>>d2;

    int setBits = 0;
    int x = d1^d2;

    while(x > 0){
        setBits += x&1;
        x = x >> 1; 
    }
    cout<<"Hamming Distance : "<<setBits;
}

