#include <bits/stdc++.h>
using namespace std;
int ktra(int n ){
    int sole= 0,sochan =0;
    while(n!= 0){
        int r = n % 10;
        if(r % 2==0) sochan++;
        else sole++;
        n /= 10;
    }
    if(sole == sochan) return 1;
    return 0;
}
int main(){
    int n,dem =0;
    cin >> n;
    for(int i = pow(10,n-1); i < pow(10, n);i++){
        if(ktra(i) == 1) {
            cout << i << " " ;
            dem++;
            if(dem == 10){
                cout << "\n";
                dem = 0  ;
            }
            
    }
}
}