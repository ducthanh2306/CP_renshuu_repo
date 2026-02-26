#include<bits/stdc++.h>  //https://codeforces.com/contest/2188/problem/A
using namespace std;
using ll = long long;
// Đối với số chẵn :
// lấy số đầu là floor trên 
// For 0 -> n
// Đan dấu - + - + -
// Đối với số lẻ:
// Lấy số đầu là floor trên 
// For 0 -> n

// Đan dấu + - + - +

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> res;    
        int first = n % 2 == 0 ? n / 2: (n / 2 )+ 1;
        if(n % 2 == 0){
            int cnt = 0;
            for(int i = 0; i < n;i++){
                if(cnt % 2 == 0){
                    first -= i;
                }else{
                    first += i;
                }
                cnt++;
                res.push_back(first);
            }
        }else{
            int cnt = 0;
            for(int i = 0; i < n;i++){
                if(cnt % 2 == 0){
                    first += i;
                }else{
                    first -= i;
                }
                cnt++;
                res.push_back(first);
            }
        }
        for(int x : res) cout << x << " ";
        cout << "\n";
    }
}

