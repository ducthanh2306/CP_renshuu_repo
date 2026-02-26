#include<bits/stdc++.h>  //https://codeforces.com/contest/2188/problem/A
using namespace std;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0 ; i < n;i++) a[i] = i + 1;
        int l = 0, r = n - 1;
        int pos = n - 1,cnt = n % 2 == 0? 1 : 0 ;
        vector<int> res(n);
        while( pos >= 0){
            if(cnt % 2 == 0){
                res[pos] = a[r];
                pos--;
                r--;
            }else{
                res[pos] = a[l];
                pos--;
                l++;
            }
            cnt++;
        }
        for(int x : res) cout << x << " ";
        cout << "\n";
    }
}

