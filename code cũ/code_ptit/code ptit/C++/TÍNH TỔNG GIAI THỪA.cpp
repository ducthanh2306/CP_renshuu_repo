#include <bits/stdc++.h>
using namespace std;
long long giaithua(int n){
    long long giaithua = 1;
    for(long long i = 1;i <= n;i++){
        giaithua = giaithua * i;
    }
    return giaithua;
}
int main() {
    long long n;
    cin >> n;
    long long tong =0;
    for(long long i = 1; i <= n;i++){
        tong += giaithua(i);
    }
    cout << tong << endl;
}
