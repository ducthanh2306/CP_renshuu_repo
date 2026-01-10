#include <stdio.h>
#include <math.h>
int main(){
    int a[3][3];
    for(int i = 0;i< 3;i++){
        for(int j = 0; j< 3;j++){
            printf("nhap phan tu [%d,%d]: ",i,j);
            scanf("%d",&a[i][j]);
        }
    }
    for(int k = 0; k< 3;k++){
        for(int z = 0; z < 3;z++ ){
            printf("phan tu [%d][%d]:%d \n",k ,z,a[k][z]);
        }
    }
}