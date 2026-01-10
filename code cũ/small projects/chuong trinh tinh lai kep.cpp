#include <stdio.h>
#include <math.h>
int main() {
    int m,k;
    double n;
    printf("Nhap lai suat(%): ");
    scanf("%lf",&n);
    printf("Nhap so tien gui(d): ");
    scanf("%d",&m);
    printf("Ban gui may nam: ");
    scanf("%d",&k);
    n = n /100;
    double z = m * pow((1+n),k);
    printf("ban se duoc %.2lf sau %d nam!",z,k);
}