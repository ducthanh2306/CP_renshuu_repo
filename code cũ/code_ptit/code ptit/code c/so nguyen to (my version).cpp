#include <stdio.h> //sai ngu còn bảo thủ, 
int main(){
    int i, a;
    scanf("%d",&i);
    while(i--) {
        scanf("%d", &a);
        if (( a == 2|| a== 3||a== 5||a== 7) || 
        ( a % 2 != 0 && a % 3 != 0&& a % 4!= 0&& a % 5!= 0&& a % 6!= 0&& a % 7!= 0
        && a % 8!= 0 && a % 9!= 0 ) && (a != 1))  
        {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    }