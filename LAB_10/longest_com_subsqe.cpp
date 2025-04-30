#include <iostream>
#include <string>
using namespace std;

int lcs(string a, string b) {
    int m = a.length(), n = b.length();
    int dp[m+1][n+1];
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    return dp[m][n];
}

int main() {
    string s1 ,s2;
    cout<<"Enter s1 and s2 : ";
    cin>>s1;
    cin>>s2;
    cout << "Length of LCS: " << lcs(s1, s2) << endl;
    return 0;
}
