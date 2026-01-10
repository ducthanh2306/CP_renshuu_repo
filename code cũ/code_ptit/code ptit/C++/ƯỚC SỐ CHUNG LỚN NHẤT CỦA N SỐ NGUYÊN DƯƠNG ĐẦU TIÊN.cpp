#include <stdio.h>

// Hàm tính USCLN (GCD) bằng thuật toán Euclid
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

// i = 4  →  j = 5, 6, 7
// i = 5  →  j = 6, 7
// i = 6  →  j = 7
    // Liệt kê các cặp số (i, j) sao cho i < j và gcd(i, j) == 1
    for (int i = a; i < b; i++) {
        for (int j = i + 1; j <= b; j++) {
            if (gcd(i, j) == 1) {
                printf("(%d,%d)\n", i, j);
            }
        }
    }

    return 0;
}
