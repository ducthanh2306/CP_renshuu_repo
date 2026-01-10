#include <stdio.h>

int main(){
    int n, nam,tuan;
    scanf("%d",&n);
    nam = n / 365;
    n = n % 365 ;
    tuan = n / 7;
    n = n % 7;
    printf("%d %d %d",nam, tuan, n);
}