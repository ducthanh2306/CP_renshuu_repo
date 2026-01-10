#include <stdio.h>

int main() {
    int n, i, j, temp;
    scanf("%d", &n); // Nhập số phần tử

    int a[n]; 
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]); // Nhập từng phần tử của mảng
    }

    // Sắp xếp mảng theo thứ tự từ bé đến lớn (Selection Sort)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] > a[j]) { 
                temp = a[i];
                a[i] = a[j];
                a[j] = temp; // Hoán đổi hai số nếu cần
            }
        }
    }

    // In phần tử đầu tiên
    printf("%d", a[0]);

    // In các phần tử khác nhau
    for (i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) { // Nếu số hiện tại khác số trước thì in ra
            printf(" %d", a[i]);
        }
    }

    return 0;
}
