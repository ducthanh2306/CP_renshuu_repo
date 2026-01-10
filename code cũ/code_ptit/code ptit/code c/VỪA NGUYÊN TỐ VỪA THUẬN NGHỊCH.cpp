#include <stdio.h>
#include <math.h>
int snt(int n){
	if (n < 2) return 0;
	for ( int i = 2; i<= sqrt(n) ; i++){
		if (n % i== 0) return 0;
	}
	return 1;
}
int stn(int n){
	int m=0, k=n;
	while(n >0){
		m = m*10 + n%10; 
		n= n/10;
	}
	if ( k == m) return 1;
	return 0;
}
int main (){
	int n;
	scanf("%d",&n);
	for (int i =1;i<= n;i++){
		int m,a,dem =0;
		scanf("%d %d",&m,&a);
	for (int j = m; j <= a;j++){
		if (stn(j) == 1 && snt(j)==1){
			printf("%d ",j);
			dem++;
			if (dem % 10==0) printf("\n");
		}
	}
	printf("\n\n");
}
}