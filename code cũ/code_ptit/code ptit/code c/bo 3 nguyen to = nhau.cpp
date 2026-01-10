#include <stdio.h>
int gcd(int a, int b){
    if (b== 0){
        return a;
    }
    return gcd(b,a%b);
}
int check(int a, int b){
    return gcd(a,b) ==1;
}
int main(){
    int a,b;
    scanf("%d %d", &a, &b);
    b++;
    for (int i =a;i<b;i++){
        for ( int j =i+1; j < b; j++){
            for(int k = j+ 1; k< b; k++){
                if ( check(i,j) && check(j,k) && check (i,k)){
                    printf("(%d, %d, %d)\n", i, j, k);
                }
            }
        }
    }
}