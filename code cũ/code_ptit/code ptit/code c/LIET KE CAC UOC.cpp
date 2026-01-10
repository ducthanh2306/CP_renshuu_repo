#include <stdio.h> // luu y doc ky de bai
#include <math.h>
int stn(int n){
    int m = 0, stn = n;
    while(n!=0){
        m = m * 10 + n % 10;
        n/=10;
    }
    return m;
}
int main(){
    printf("%d",stn(12321));
}