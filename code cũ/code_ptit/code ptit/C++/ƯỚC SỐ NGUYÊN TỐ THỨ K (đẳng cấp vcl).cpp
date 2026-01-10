#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll t;
	cin >> t;
	while(t--){
		ll n ,a,dem=0;
		cin >> n >> a;
		for(int i = 2; i<= sqrt(n);i++){
			while( n % i == 0){
				n /= i;
				dem++;
				if(dem == a) {
					cout << i;
					break;
				}
			}
			if(dem == a) break;
		}
		if(dem + 1  == a && n > 1) cout << n;
		if (dem + 1< a && n > 1) cout << "-1";
		if (dem < a && n == 1) cout << "-1";
		cout<< "\n";
	}
}
