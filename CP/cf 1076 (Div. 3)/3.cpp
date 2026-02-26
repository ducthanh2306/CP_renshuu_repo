#include<bits/stdc++.h> // https://codeforces.com/contest/2193/problem/C?adcd1e=caf4f2lw8286we&csrf_token=ab7978419a1f2485f5bf601f00716a8e
using namespace std;
const int MAXN = 2 *10e5;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n,q;
        cin >> n >> q;
        vector<int> a(n),b(n);
        for(int &x : a) cin >> x;
        for(int &x : b) cin >> x;
        for(int i = 0 ; i < a.size();i++){
            if(b[i] > a[i]) a[i] = b[i];
        }
        int cur = a[n - 1];
        for(int i = n - 1; i >= 0;i--){
            if(a[i] > cur) cur = a[i];
            a[i] = cur;
        }
        vector<int> pre(n + 1);
        for(int i = 1; i <= n;i++){
            pre[i] = pre[i - 1] + a[i - 1];
        }
        
        while(q--){
            int l,r;
            cin >> l >> r;
            cout << pre[r] - pre[l - 1] << " ";
        }
        cout << "\n";
        // while(q--){ // cach giai bi nham vi operation co the lam bat ky o dau voi moi doan l r;
        //     int l,r;
        //     cin >> l >> r;
        //     int cur = (r < n ) ? a[r] : a[r - 1];
        //     int sum = 0;
        //     for(int i = r - 1 ; i >= l - 1;i--){
        //         if(a[i] > cur ) {
        //             cur = a[i];
        //         }
        //         sum += cur;
        //     }
        //     cout << sum <<" ";
        // }
        
    }
}