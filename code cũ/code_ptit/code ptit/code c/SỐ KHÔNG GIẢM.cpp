#include <stdio.h>

int skg(int n) {
    int socu = n % 10;
    while (n > 0) {
        int k = n % 10;
        if (k > socu) return 0;
        socu = k;
        n /= 10;
    }
    return 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int chuso;
        scanf("%d", &chuso);
        int start = 1;
        for (int i = 1; i < chuso; i++) {
            start *= 10;  
        }
        int end = start * 10; 
        for (int j = start; j < end; j++) {
            if (skg(j)) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
    return 0;
}
