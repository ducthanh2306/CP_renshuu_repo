#include <bits/stdc++.h>
using namespace std;
#define ll long long // luu y % chi ap dung voi kieu so nguyen
int main(){
	int t;
	cin >> t;
	while(t--){
		ll x,dem,min =9999999999;
		cin >> x;
		ll a[x];
		for(int i = 0;i< x;i++){
			cin >> a[i];
		}
		for(int j = 0; j < x ;j++){
			for(int k  = 0; k< x;k++){
				if(k != j) {
				dem = abs(a[k] -a[j]);
				if(dem < min ) min = dem;
			}
			}
		}
		cout << min;
		cout << "\n";
	}
}