#include <bits/stdc++.h>
using namespace std;
// root nguyen to o day la mot so le vi ta dag xet 1i , 2i , 3i nen no co chung 1 root la i bat chap
int rootNguyento(int tmp){
    int n = tmp;
    while(n > 0 && n % 2 == 0){
        n /= 2;
    }
    return n;
}
bool solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <=n;i++) cin >> a[i];
    for(int i = 1; i <= n;i+= 2){ // vi neu ta xet 2 thi luc xet 1 no da xet het so chan roi, neu ko xet tu 1=> n cung dc ,it ms hon
        for(int j = i; j <= n; j *= 2){
            if (rootNguyento(i) != rootNguyento(a[j])) return false;
        }
        
    }
    return true;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        if(solve()) cout << "YES";
        else cout << "NO";
        cout << "\n";
    }
}