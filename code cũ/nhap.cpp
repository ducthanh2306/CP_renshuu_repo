#include<bits/stdc++.h>
using namespace std;
bool visited[1001];
bool found = false;
bool check(long long &so){
	return abs (so % 10 - (so /10) % 10) == 1;
}
void bt(long long n,long long so,long long len){
	if(check(so) && len >= 2) return;
	if(len == n){
		found = true;
		cout << so << "\n";
		return;
	}
	for(long long i = 1 ; i <= n;i++){
		if(!visited[i]){
			visited[i] = true;
			bt(n,so * 10 + i,len + 1);
			visited[i] = false;
		}
		
	}
}

int main(){
	long long t;
	cin >> t;
	while(t--){
		long long n;
		cin >> n;
		memset(visited,false,sizeof(visited));
		bt(n,0,0);
		if(!found) cout << "\n"; 
		found = false;
	}
}