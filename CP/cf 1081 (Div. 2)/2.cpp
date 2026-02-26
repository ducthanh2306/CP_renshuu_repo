#include <bits/stdc++.h>
using namespace std;
bool possible(string &s){
    if(s.size() % 2 == 0) return true;
    int cnt1 = 0;
    for(auto x : s){
        if (x == '1') cnt1++;
    }
    return cnt1 % 2 != 1;
}
void solve(){
    int n;
    string s;
    cin >> n >> s;
    int cnt1 = 0,cnt2 = 0;
    vector<int> idx1,idx0;
    for(int i = 0 ; i < n;i++){
        if(s[i] == '1') idx1.push_back(i + 1);
        else idx0.push_back(i + 1);
    }
    if(possible(s)){
        if (idx1.size() % 2 == 0){
            cout << idx1.size() << "\n";
            for (auto x : idx1 ) cout << x << " ";
            if (idx1.size() != 0 )cout << "\n";
        }else{
            cout << idx0.size() << "\n";
            for (auto x : idx0 ) cout << x << " ";
            cout << "\n";
        }
    }else{
        cout << -1 << "\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}