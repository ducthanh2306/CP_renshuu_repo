#include<bits/stdc++.h> //https://codeforces.com/contest/2193/problem/D
using namespace std;
using ll = long long;


//luu y cac edge case sau
//Thiếu trường hợp tổng bằng k ngay từ đầu ( idx == 0)
//giữ lại chỉ số đầu tiên (để lấy mảng dài nhất) chi cap nhat mp[current_sum] = i neu no chua bao gio duoc update

int main(){
    ll n,k;
    cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<ll> pre(n + 1,0);
    for(int i = 1 ; i <= n;i++){
        pre[i] = pre[i - 1] + a[i - 1];
    }
    unordered_map<ll,ll> mp;
    mp[0] = 0;
    ll max_len = 0;
    for(int i = 1 ; i <= n;i++){
        ll rem = ((pre[i] % k)+k) % k;
        if(mp.count(rem)){
            max_len = min(max_len,i - mp[rem] );
        }
        mp[rem] = i;
    } 
    cout << max_len;
}

