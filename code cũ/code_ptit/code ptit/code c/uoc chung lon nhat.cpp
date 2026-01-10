#include <stdio.h>
#include <math.h>
int ucln(int a, int b){
    if (a == 0 && b == 0){
        return 0;
    }
   if( a == 0|| b == 0){
    return a + b;
   }
   if (a <= b){
    for ( int i = a;i>= 0 ;i--){
        if (a % i == 0 && b % i == 0){
            return i;
        }
    }
   }
   if (a >= b){
    for ( int i = b; i >= 0 ; i--){
        if (a % i == 0 && b % i == 0){
            return i;
        }
    }
   }
   return 0;
}

int main(){
   printf("%d", ucln(20, 0));
   return 0;
}