#include <stdio.h>
int main() {
    int a,b;
    scanf ("%d %d", &a, &b);
    if( b ==0){
    printf("0");
    }else {
        int sum=a + b;
        int diff= a - b;
        int prod= a * b;
        double div_real= (double)a / b;
        int mod= a % b; 
    printf("%d %d %d %.2lf %d", sum, diff, prod, div_real, mod);
    }
}
