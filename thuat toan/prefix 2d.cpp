#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> grid(n + 1 ,vector<int> (n + 1));
    for(int i = 1; i <= n;i++){
        for(int j = 1; j <= n;j++){
            cin >> grid[i][j];
        }
    }
    vector<vector<int>> pre(n + 1,vector<int> (n + 1));
    for(int i = 1; i <= n;i++){
        for(int j = 1; j <=n;j++){
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + grid[i][j];
        }
    }
    cout << pre[4][4] - pre[2][4] - pre[4][2] + pre[2][2];
}