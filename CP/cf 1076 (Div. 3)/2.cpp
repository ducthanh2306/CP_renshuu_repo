#include<bits/stdc++.h> // https://codeforces.com/contest/2193/problem/B
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int &x : a) cin >> x;
        int i = 0;
        while(i < a.size() && a[i] == n - i){
            i++;
        }
        int j = i;
        while(j < a.size() && a[j] != n - i){
            j++;
        }
        if(i == a.size()){
            for(int &x : a) cout << x << " ";
            cout << "\n";
        }else{
            int l = i, r = j;
            while(l < r){
                swap(a[l],a[r]);
                l++;
                r--;
            }
            for(int x : a) cout << x << " ";
            cout << "\n";
        }
    }
}