#include <stdio.h>
int main() {
    int a, b, c, d, n , m, z; 
    scanf("%d", &a);
    n= a /365;
    
    if ( n != 0){
        b = a - n*365; 
        c = b / 7; // so tuan khi ma so nam khong phai la 0
        d = b % 7; // so ngay khi ma so nam khong phai la 0
        printf("%d %d %d", n , c ,d);
    } else if ( n == 0){
        m = a/ 7; // so tuan khi ma so nam la 0
        z = a % 7;// so ngay khi ma so nam la 0
        printf("%d %d %d", n , m ,z);
    }
    }