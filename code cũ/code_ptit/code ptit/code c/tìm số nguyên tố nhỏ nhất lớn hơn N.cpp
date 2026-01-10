//Tìm số nguyên tố nhỏ nhất lơn hơn N:
// ý tưởng : 
// b1: viết hàm tính số nguyên tố
// b2: scan thằng N
// b3: nhét N vào vòng lặp, cho nó +1 mỗi vòng lặp
// b4: nếu nó là số nguyên tố thì break (prime (n) == 1)
#include <stdio.h>
#include <math.h>

int prime(int n){
    int a;
    if (n <2) return 0;
    for (int i = 2; i <= sqrt(n);i++){
        if ( n % i == 0) return 0;
    }
    return 1;
}
int main() {
    int n, dem =0;
    scanf("%d",&n);
    for (;;n++){
        if (prime(n)== 1){
            dem++;
            printf("%d",n);
            break;
        }
    };
}