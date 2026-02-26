#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n+1), diff(n+2);

    a[0] = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        diff[i] = a[i] - a[i-1];
    }

    int q;
    cin >> q;
    while(q--){
        int l, r;
        long long x;
        cin >> l >> r >> x;
        diff[l] += x;
        diff[r+1] -= x;   // an toàn vì diff có size n+2
    }

    for(int i = 1; i <= n; i++){
        a[i] = a[i-1] + diff[i];
    }

    for(int i = 1; i <= n; i++){
        cout << a[i] << " ";
    }
}
