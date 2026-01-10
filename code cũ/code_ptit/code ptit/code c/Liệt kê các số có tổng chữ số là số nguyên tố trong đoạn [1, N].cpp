#include <stdio.h>
#include <math.h>

int prime(int n){
    if (n <2) return 0;
    for (int i = 2; i <= sqrt(n);i++){
        if ( n % i == 0) return 0;
    }
    return 1;
}
int main() {
    int a, n;
    scanf("%d", &n);
    for(a= 1; a <=n; a++){
        int z = a,tong = 0;
        while(z >0){
                tong= tong + z % 10;
                z = z / 10;
        }
        if(prime(tong) == 1){
            printf("%d ",a);
        }
    }
}