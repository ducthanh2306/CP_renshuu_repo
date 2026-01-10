#include <stdio.h>
#include <math.h>
int main(){
    int a,b;
    scanf("%d",&a);
    for(int i = 1;i <= a;i++){
        for(int j= a -i;j < a;j++){
            printf("*");
        }
        printf("\n");
    }
}