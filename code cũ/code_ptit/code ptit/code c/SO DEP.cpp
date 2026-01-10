#include <stdio.h>
#include <math.h>
int cc1(int n){
    if ( n < 2) return 0;
    for(int i = 2;i <= sqrt(n);i++){
        if ( n % i == 0) return 0;
    }
    return 1;
}
int fibon( int n){
    if ( n== 1 || n == 0) return 1;
    int f0 = 0, f1 = 1, fn;
    for (int i = 2; i <= 39; i++){
        fn = f1 + f0;
        f0 = f1;
        f1 = fn;
        if (n == fn ) return 1;
    }   
    return 0;
}
int chuso( int n){
    int tong =0;
    for (;n != 0;){
        int k = n % 10;
        tong = tong + k;
        n /= 10;
    }
    if (fibon(tong) == 1) return 1;
    return 0;
}
int main(){
    int a,b; 
    scanf("%d %d",&a ,&b);
    if ( a <b){
    for(int i = a; i <= b;i++){
    if (chuso(i) == 1 && cc1(i) == 1) {
        printf("%d ",i);
    }
    
}
}
if ( a >b){
    for(int i = b; i <= a;i++){
    if (chuso(i) == 1 && cc1(i) == 1) {
        printf("%d ",i);
    }
    
}
}
}