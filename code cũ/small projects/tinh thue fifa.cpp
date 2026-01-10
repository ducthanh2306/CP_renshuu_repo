#include <stdio.h>
int main() {
    int  b, c;
    double a;
    printf("Chao mung ban den voi cong cu tinh toan thue cua chung toi\n");
    printf("\n");
    printf("Developed by Thanh dep trai:))\n");
    printf("\n");
    printf("So tien cau thu: ");
    scanf("%lf", &a);
    double n=a;
     printf("Ban co vip khong ?\n");
   printf("1. SVIP\n");
   printf("2. VIP\n");
   printf("3. Ko co\n");
    for(;;){
        printf("cau tra loi cua ban: ");
        scanf("%d", &b);
        if (b == 1){
            a= n *0.72;
            break;
        }
        else if (b == 2){
            a= n* 0.64;
            break;
        }
        else if (b == 3){
            a= n* 0.6;
            break;
        }
        else{
            printf("Lua chon khong hop le.Hay chon lai\n");
        }
    }
    printf("Ban co phieu bao nhieu % ? \n");
   printf("1. 30% \n");
   printf("2. 20% \n");
   printf("3. 10% \n");
   printf("4. ko co :(\n");
   
   for(;;){
    printf("cau tra loi cua ban: ");
   scanf("%d", &c);
        if (c == 1 && b== 1){
            a= n *0.84;
            break;}
        else if ( c== 1 && b== 2){
            a= n*0.76;
            break;
        }
        else if ( c== 1 && b== 3){
            a= n*0.72;
            break;
        }else if ( c== 2 && b== 1){
            a= n * 0.80;
            break;
        }else if ( c== 2 && b== 2){
            a= n*0.72;
            break;
        }else if ( c== 2 && b== 3){
            a= n*0.68;
            break;
        }else if ( c== 3 && b== 1){
            a= n*0.76;
            break;
        }else if ( c== 3 && b== 2){
            a= n*0.68;
            break;
        }else if ( c== 3 && b== 3){
            a= n*0.64;
            break;
        }else if ( c== 4 && b== 1){
            a= n*0.72;
            break;
        }else if ( c== 4 && b== 2){
            a= n*0.64;
            break;
        }else if ( c== 4 && b== 3){
            a= n*0.6;
            break;
        } else {
            printf("Lua chon ko phu hop. Hay thu lai-_- \n");
        }
        
}
printf("Vay so tien sau thue la %.2lf", a);
}