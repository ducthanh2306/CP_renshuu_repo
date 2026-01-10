#include <stdio.h>
#include <math.h>
int main(){
    int a,b;
    scanf("%d %d",&a,&b);
    for (int i = 1;i <= b;i++){
        if( i == 1 || i == b) {
            for(int k = 1; k <= a;k++){
            printf("*");
            }
        }
        else{
            printf("*");
            for(int j = 1; j<= a-2;j++){
                printf(" ");
            }
            printf("*");
        }
        printf("\n");
    }
}