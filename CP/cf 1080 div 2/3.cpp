#include <bits/stdc++.h>
using namespace std;
int INF = 1e9;
void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <=n;i++) cin >> a[i];
    vector<vector<int>> dp(n + 1, vector<int>(7,INF));
    for(int i = 1; i <= 6;i++){
        dp[1][i] = (a[1] != i) ? 1 : 0;
    }
    for(int i = 2; i <= n;i++){
        for(int v = 1; v <= 6;v++){
            for(int u = 1; u <= 6;u++){
                if(u != v && v != 7 - u){
                    dp[i][v] = min(dp[i][v],dp[i-1][u] + int(a[i] != v));
                }
            }
        }
    }
    int best = INF;
    for(int i = 1; i <= 6;i++){
        best=  min( dp[n][i],best);
    }
    cout << best << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}