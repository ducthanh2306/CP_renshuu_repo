#include<bits/stdc++.h> //https://codeforces.com/contest/2193/problem/D
using namespace std;

typedef long long ll;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // 1. Sắp xếp mảng kiếm tăng dần
    sort(a.begin(), a.end());

    // 2. Tính mảng tiền tố cho b (số đòn đánh cần để qua k level)
    vector<ll> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + b[i];
    }

    ll max_score = 0;

    // 3. Duyệt qua từng sức mạnh x khả dĩ trong mảng a
    for (int i = 0; i < n; i++) {
        ll x = a[i];
        ll swords_available = n - i; // Số kiếm có sức mạnh >= a[i]

        // Tìm k lớn nhất sao cho tổng số đòn đánh pref[k] <= swords_available
        auto it = upper_bound(pref.begin(), pref.end(), swords_available);
        ll levels = distance(pref.begin(), it) - 1;

        max_score = max(max_score, x * levels);

        // Bỏ qua các giá trị a[i] giống nhau để tối ưu thời gian
        while (i + 1 < n && a[i + 1] == a[i]) i++;
    }

    cout << max_score << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

// #include<bits/stdc++.h> //https://codeforces.com/contest/2193/problem/D
// using namespace std;
// const int MAXN = 2 *1e5;

// int main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(0);
//     int t;
//     cin >> t;
//     while(t--){
//         int n;
//         cin >> n;
//         vector<int> a(n),b(n);
//         for(int&x: a) cin >> x;
//         for(int&x: b) cin >> x;
//         int MAX = *max_element(a.begin(),a.end());
//         vector<int> larger(MAX + 1,0);

//         for(int i = 1; i < larger.size();i++){
//             for(int x : a){
//                 if(x >= i) larger[i]++;
//             }
//         }
//         int res = 0;
//         for(int x = 1; x <= MAX;x++){ 
//             int strikeNum = larger[x];
//             int level = 0;

//             for(int i = 0 ; i < b.size();i++){
//                 if(strikeNum >= b[i]){
//                     strikeNum -= b[i];
//                     level++;
//                 }else break;
//             }
//            res = max(res,level * x);
//         }
//         cout << res << "\n";
//     }
// }