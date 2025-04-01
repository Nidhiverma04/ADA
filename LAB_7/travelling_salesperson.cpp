#include <bits/stdc++.h>
using namespace std;
#define V 4
int travllingSalesmanProblem(int cost[][V], int s)
{
    vector<int> vertex;
    for (int i = 0; i < V; i++)
        if (i != s)
            vertex.push_back(i);
 
    int min_path = INT_MAX;
    do {
        int current_pathweight = 0;
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += cost[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += cost[k][s];
 
        // update minimum
        if(min_path > current_pathweight){
            cout<<k<<" --> ";
        }
        min_path = min(min_path, current_pathweight);
    } while (
        next_permutation(vertex.begin(), vertex.end()));
 
    return min_path;
}
int main()
{
    int cost[][V] = { { 0, 10, 15, 20 },
                       { 10, 0, 35, 25 },
                       { 15, 35, 0, 30 },
                       { 20, 25, 30, 0 } };
    int s = 0;

    cout << endl<<"Mincost: "<<travllingSalesmanProblem(cost, s) << endl;
    return 0;
}