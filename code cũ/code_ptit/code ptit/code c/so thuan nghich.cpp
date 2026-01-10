#include <stdio.h>

int thuan_nghich(int n){
    int m = 0, tmp = n;
    while(n != 0){
        m = m * 10 + n % 10; 
        n /= 10;
    }
    if(tmp == m){ 
        return 1;
    }
    return 0;
}

int main(){
    int n = 12321;
    if(thuan_nghich(n)){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}