#include <stdio.h>
#include <math.h>

int swap_first_last(int n) {
    // Nếu số chỉ có một chữ số, không cần đổi
    if (n < 10) {
        return n;
    }
    
    // Tìm số chữ số của n
    int num_digits = (int)log10(n);
    
    // Lấy chữ số đầu tiên
    int first_digit = n / (int)pow(10, num_digits);
    
    // Lấy chữ số cuối cùng
    int last_digit = n % 10;
    
    // Lấy phần số còn lại sau khi loại bỏ chữ số đầu và cuối
    int middle_part = (n % (int)pow(10, num_digits)) / 10;
    
    // Ghép lại số mới với chữ số cuối cùng ở đầu, phần giữa, và chữ số đầu tiên ở cuối
    int result = last_digit * (int)pow(10, num_digits) + middle_part * 10 + first_digit;
    
    // Loại bỏ các số 0 ở cuối (nếu có)
    while (result % 10 == 0) {
        result /= 10;
    }
    
    return result;
}

int main() {
    int n;
    printf("Nhap so nguyen: ");
    scanf("%d", &n);

    int result = swap_first_last(n);
    printf("Kết quả sau khi đổi chỗ: %d\n", result);

    return 0;
}
