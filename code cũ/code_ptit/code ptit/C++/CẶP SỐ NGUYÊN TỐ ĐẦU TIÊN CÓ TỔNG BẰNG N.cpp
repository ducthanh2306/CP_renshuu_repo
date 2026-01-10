//Cho số tự nhiên N. Hãy tìm cặp số nguyên tố đầu tiên có tổng là N. 
//Nếu không tồn tại cặp số nguyên tố có tổng bằng N, hãy đưa ra -1.
#include <bits/stdc++.h>
using namespace std;
int nt(int n){
	for(int i=2;i<=sqrt(n);i++){
		if(n%i==0) return 0;
	}
	return n>1;
}
int main(){
	int t; cin >> t;
	while(t--){
		int n,cnt=0; cin >> n;
		for(int i=2;i<=n/2;i++){
			if(nt(i)&&nt(n-i)){
				++cnt;
				cout << i << " " << n-i;
				break;
			}
		}
		if(cnt==0) cout << "-1";
		cout << endl;
    }
}