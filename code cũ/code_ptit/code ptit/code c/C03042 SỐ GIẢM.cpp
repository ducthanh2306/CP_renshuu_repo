#include<stdio.h>
int sogiam(long long n){
    int sosau = -1;
    while(n > 0){
        int socuoi = n % 10; 
        if ( socuoi <= sosau) return 0;
        sosau = socuoi;
        n /= 10;
    }
    return 1;
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i = 1; i <= n;i++){
        long long a,b;
        int dem = 0;
        scanf("%lld %lld",&a,&b);
        for (long long j = a;j <= b;j++){
            if(sogiam(j) == 1) dem++;
        }
        printf("%d\n",dem);
    }
}