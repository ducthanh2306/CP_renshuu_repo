#include <stdio.h>

int swapFirstLast(int n) {
    int last = n % 10; // Lấy chữ số cuối cùng
    int temp = n, first, power = 1;
    
    // dTìm chữ số đầu tiên và độ lớn của số
    while (temp >= 10) {
        temp /= 10;
        power *= 10;
    }
    first = temp; // Chữ số đầu tiên
    
    // Nếu số chỉ có một chữ số thì không cần đổi
    if (power == 1) return n;

    // Xóa chữ số đầu tiên và chữ số cuối cùng, rồi chèn lại
    int middle = (n % power) / 10; // Phần giữa (loại bỏ chữ số đầu và cuối)
    int result = last * power + middle * 10 + first; // Ghép lại

    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", swapFirstLast(n));
    return 0;
}
