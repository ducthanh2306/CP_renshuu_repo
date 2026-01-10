#include <stdio.h>
int main() {
    int i, n;
    printf("Hay nhap mat khau: ");
    for (i = 1; i <= 5; i++){
        printf("Mat khau nhap lan %d : ", i);
        scanf("%d",&n);
        if( n == 230606 ){
            printf("mat khau chinh xac\n");
            break;
        } else { 
            if(i < 5){
            printf("mat khau sai hay nhap lai\n");}
        }
    }
    if ( n != 230606){
        printf("ban da het luot thu, hen gap lai");
    }
}