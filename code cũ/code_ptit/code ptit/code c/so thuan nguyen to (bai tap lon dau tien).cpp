#include <stdio.h>
#include <math.h>
// Bài 4. Liệt kê số thuần nguyên tố trong đoạn [1, N].

// Số thuần nguyên tố thỏa mãn : 

// N là số nguyên tố
// N có tất cả các chữ số là số nguyên tố
// N có tổng chữ số là số nguyên tố 
int prime(int n){
    if (n < 2){
        return 0;
    }
    for( int i = 2; i<= sqrt(n); i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;
}
int tong_chuso(int n){
    int tong= 0, z=n;
    for (;z >0;){
        tong = tong + z % 10;
        z = z /10;
    }
    if(prime(tong ) == 1){
    return 1;}
    return 0;
}
int chusonguyento(int n){
    int i = 0, chuso=0 ;
    for (; n > 0; n = n/10){
        chuso =  n  % 10;
        if ( prime(chuso) == 0){
            return 0;
        }
        }
        return 1;
    }
int main(){
    int i, n;
    scanf("%d",&n);
    for(i =1; i <= n; i++){
        if (prime(i) == 1 && tong_chuso(i) == 1 && chusonguyento(i)){
            printf("%d ", i);
        }

    }
}