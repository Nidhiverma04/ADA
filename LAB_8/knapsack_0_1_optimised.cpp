#include<iostream>
#include<algorithm>
#include<ctime>
#include<set>
#include<vector>

using namespace std;
int** generate_requests(int c, int n){
    
    int** det = new int*[n];
    for(int i=0;i<n;i++){
        det[i] = new int[2];
    }
    for(int i=0;i<n;i++){
        det[i][0] = rand()%100; //profit
        det[i][1] = rand()%10+1 ; //storage
    }

    cout << "Items (Storage, Profit):\n";
    for (int i = 0; i < n; i++) {
        cout << "(" << det[i][0] << ", " << det[i][1] << ")\n";
    }
    cout << "Knapsack Capacity: " << c << "\n";
    return det;
}

set<pair<int, int>> mergepurge(set<pair<int, int>> s0, set<pair<int, int>> s1){
    set<pair<int, int>> s = s0;
    for (auto &p : s1) {
        s.insert({p.first, p.second});
    }
    vector<pair<int, int>> to_remove;
    for (auto it1 = s.begin(); it1 != s.end(); ++it1) {
        for (auto it2 = s.begin(); it2 != s.end(); ++it2) {
            if (it1 == it2) continue;
            if (it2->first >= it1->first && it2->second < it1->second) {
                to_remove.push_back(*it1);
            }
        }
    }
    for (const auto& p : to_remove) {
        s.erase(p);
    }
    return s;
}
void traceback(int prof, int wt, set<pair<int, int>>s0[], int n, int** det){
    int x[n]={0};
    for(int i=n-1;i>=0;i--){
        bool flag = true;
        for (auto p : s0[i]) {
            if(p.first == prof && p.second == wt){
                flag = false;
                break;
            }     
        }
        if(flag && i>=0){
            x[i] = 1;
            prof -= det[i][0];
            wt -= det[i][1];
        }
    }

    cout << "\nItems taken (Storage, Profit):\n";
    for(int i=0;i<n;i++){
        if(x[i] == 1){
            cout << "(" << det[i][0] << ", " << det[i][1] << ")\n";
        }
    }
}

void knapsack(int n, int c, int** det){
    set<pair<int, int>> s0[n+1];
    set<pair<int, int>> s1[n];

    s0[0].insert({0,0});
    for(int i=1;i<=n;i++){
        for (auto& p : s0[i-1]) {
            int wt = p.second;
            int pro = p.first;
            if( wt + det[i-1][1] <= c)
                s1[i-1].insert({pro + det[i-1][0], wt + det[i-1][1]});
        }
    
        s0[i] = mergepurge(s0[i-1], s1[i-1]);
    }

    int max_prof = 0;
    int wt = 0;
    for (auto p : s0[n]) {
        if(p.first > max_prof){
            max_prof = p.first;
            wt = p.second;
        }
    }
    cout<<"\nMax profit : "<<max_prof<<" wt : "<<wt<<endl;

    traceback(max_prof, wt, s0, n, det);
}

int main(){
    srand(time(0));
    int c = rand()%10 + 10;
    int n;
    cout<<"Enter n : ";
    cin>>n;
    int** det = generate_requests(c, n);
    knapsack(n, c, det);

    for (int i = 0; i < n; i++) {
        delete[] det[i];
    }
    delete[] det;
    return 0;
}