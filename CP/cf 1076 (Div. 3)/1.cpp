#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n,s,x;
        cin >> n >> s >> x;
        vector<int> a(n);
        for(int&x: a) cin >> x;
        int sum = 0;
        for(int x : a ) sum+= x;
        while(sum < s){
            sum+= x;
        }
        if(sum == s) cout << "YES";
        else cout << "NO";
        cout << "\n";
    }
}