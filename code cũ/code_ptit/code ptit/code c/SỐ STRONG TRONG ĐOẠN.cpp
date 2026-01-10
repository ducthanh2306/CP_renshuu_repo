#include <stdio.h>
#include <math.h>

int giaithua(int n){
	int k = 1;
	for (int i = 1; i<= n;i++){
		k = k * i;
	}
	return k;
}
int chuso(int n){
	int tong =0;
	while(n >0 ){
		int a = n % 10;
		n /= 10;
		tong = tong + giaithua(a);
	}
	return tong;
}
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	if ( n < m){
	for ( int i = n; i <= m; i++){
		if (chuso(i) == i){
			printf("%d ",i);
		}
	}
	}
	if ( m < n){
	for ( int i = m; i <= n; i++){
		if (chuso(i) == i){
			printf("%d ",i);
		}
	}
	}
}