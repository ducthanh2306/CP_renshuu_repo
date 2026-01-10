#include <stdio.h>
#include <math.h>
int bcnn(int a, int b){
    if ( a == 0 || b == 0 ){
        return 0;
    }
    if (a >= b){
        for(int i = a; ;i++){
            if ( i % a ==0 && i % b ==0){
                return i;
            }
        } 
    }
    if(a <= b){
        for(int i = b; ;i++){
            if ( i % a ==0 && i % b ==0){
                return i;
            }
        } 
    }
    return 0;
}
int main() {
    int a,b;
    scanf("%d %d", &a,&b);
    printf("%d", bcnn(a,b));
}