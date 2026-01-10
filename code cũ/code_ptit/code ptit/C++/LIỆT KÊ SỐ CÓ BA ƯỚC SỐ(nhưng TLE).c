#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll uoc(int n){
	if (n < 2) return 0;
	int dem =0;
	for(int i = 2;i<= sqrt(n);i++){
		if (n % i == 0 && i != n /i){
			return 0;
		}
		if(n % i == 0 && i == n /i) {
			dem++;
			break;
		}
	}
	if(dem == 1) return 1;
}
int main(){
	ll t;
	cin >> t;
	while(t--){
		ll a;
		cin >> a;
		for(int i = 1;i<= a;i++){
			if(uoc(i) == 1) cout << i <<" ";
		}
		cout << endl;
	}
}
