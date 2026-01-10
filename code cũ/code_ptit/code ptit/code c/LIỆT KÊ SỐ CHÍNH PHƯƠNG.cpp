#include <stdio.h>
#include <math.h>

int tich(int n) {
    int a = (int)sqrt(n);  
    if (a * a == n) return 1; 
    return 0;
}

int main() {
    int a, b, dem = 0;
    scanf("%d %d", &a, &b);
    
    for (int i = a; i <= b; i++) {
        if (tich(i) == 1) {
            dem++;
        }
    }
    
    printf("%d\n", dem);
    
    for (int i = a; i <= b; i++) {
        if (tich(i) == 1) {
            printf("%d\n", i);
        }
    }
}
