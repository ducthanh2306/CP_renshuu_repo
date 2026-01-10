#include <stdio.h>

int main() {
	float a;
	scanf("%f", &a);
	if (a >= 9 && a <= 10) {
		printf("A+");
	} else if (a >= 8.5 && a < 9) {
		printf("A");
	} else if (a >= 8.0 && a < 8.5) {
		printf("B+");
	} else if (a >= 7.0 && a < 8.0) {
		printf("B");
	} else if (a >= 6.5 && a < 7.0) {
		printf("C+");
	} else if (a >= 5.5 && a < 6.5) {
		printf("C");
	} else if (a >= 5.0 && a < 5.5) {
		printf("D+");
	} else if (a >= 4.0 && a < 5.0) {
		printf("D");
	} else if (a >= 0 && a < 4) {
		printf("F");
	} else {
		printf("Diem khong hop le");
	}
}
