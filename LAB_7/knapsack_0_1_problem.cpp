#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;
int main(){
    srand(time(0));
    int c = rand()%10 + 10;
    int** det = new int*[5];
    for(int i=0;i<5;i++){
        det[i] = new int[2];
    }
    for(int i=0;i<5;i++){
        det[i][0] = rand()%10+1; //storage
        det[i][1] = rand()%100; // profit
    }

    cout << "Items (Storage, Profit):\n";
    for (int i = 0; i < 5; i++) {
        cout << "(" << det[i][0] << ", " << det[i][1] << ")\n";
    }
    cout << "Knapsack Capacity: " << c << "\n";

    int** profit = new int*[6];
    for(int i=0;i<=5;i++){
        profit[i] = new int[c+1];
    }
    for(int i=0;i<=c;i++){
        profit[0][i] = 0;
    }
    for(int i=0;i<=5;i++){
        profit[i][0] = 0;
    }

    for(int i=1;i<=5;i++){
        for(int j=1;j<=c;j++){
            if(j >= det[i-1][0]){
                profit[i][j] = max(profit[i-1][j], profit[i-1][j-det[i - 1][0]] + det[i - 1][1]);}
            else{
                profit[i][j] = profit[i-1][j];
            }
        }
    }

    cout<<"Profit : "<<profit[5][c];

    for (int i = 0; i < 5; i++) {
        delete[] det[i];
    }
    delete[] det;

    for (int i = 0; i <= 5; i++) {
        delete[] profit[i];
    }
    delete[] profit;

    return 0;

}