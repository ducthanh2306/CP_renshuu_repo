#include <stdio.h>
#include <math.h>
//Cach 1: dem uoc , neu so chi co 2 uoc thi la so nguyen to 
//if (n%i == 0) uoc 1
//if (i khac cai uoc con lai, tranh so chinh phuong ) thi dc uoc 2
// Cach 2: xem tu 2 den sqrt(n) thi cai nao n % i == 0 thi phu dinh, lay cai con lai
int prime(int n){
    int a;
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n);i++){
        if ( n % i == 0) return 0;
    }
    return 1;
}
int main() {
    int n,i, dem =0;
    scanf("%d",&n);
    for (i = 1;i <= n; i++){
        if (prime(i) == 1){
            printf("%d",i);
            dem++;
        }
    }
    printf("\n%d",dem);
}