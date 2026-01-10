#include <stdio.h>
#include <math.h>
int main() {
    printf("Chao mung ban den menu tinh toan\n");
    int d;
    double a,b,c;
    printf(" hay nhap so a: ");
    scanf("%lf",&a);
    printf(" hay nhap so b: ");
    scanf("%lf",&b);
    printf("Hay chon tinh nang\n");
    printf("1. a + b\n");
    printf("2. a-b\n");
    printf("3. a*b\n");
    printf("4. a/b\n");
    printf("5. a^b\n");
    printf("6. a/b du\n");
    printf(" Ban chon: ");
    scanf("%d",&d);
    if (d == 1){
        c = a +b;
        printf("%.2lf + %.2lf= %.2lf. Vay dap an la %.2lf", a,b,c,c);
    }
    else if(d ==2){
        c = a - b;
        printf("%.2lf - %.2lf= %.2lf. Vay dap an la %.2lf", a,b,c,c);

    }
    else if(d ==3) {
        c = a * b;
        printf("%.2lf * %.2lf= %.2lf. Vay dap an la %.2lf", a,b,c,c);
    }
    else if(d ==4){
        if (b !=0){
            c= a/b;
            printf("%.2lf / %.2lf= %.2lf. Vay dap an la %.2lf", a,b,c,c);
        }else {
            printf(" m ngu vcl 0 thi chia cc nao dc");
        }
    }
    else if(d==5){
        c = pow(a,b);
        printf("%.2lf ^ %.2lf= %.2lf. Vay dap an la %.2lf", a,b,c,c);
    }
    else if(d==6){
        if (b !=0){
        c= fmod(a,b);
        printf("%.2lf / %.2lf= du %.2lf. Vay dap an la %.2lf", a,b,c,c);
    }
    else {
        printf(" 0 chia cc dc a");
    }

    }
    else{
        printf(" m nhap so nao the thg ngu");
    }
    
}

