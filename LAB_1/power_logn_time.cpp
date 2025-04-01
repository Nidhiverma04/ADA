#include <iostream>
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
    cout<<"Enter a and b : ";
    int a, n;
    cin >> a >> n;
    cout<<"\nPower : "<<power(a, n);
}


