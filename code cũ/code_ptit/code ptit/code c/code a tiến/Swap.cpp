#include <stdio.h>

void swap1(int x, int y) {
	printf("start swap1\n");
	int temp = x;
	x = y;
	y = temp;
	printf("%d %d\n", x, y);
	printf("end swap1\n");
}
void swap2(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

int main() {
	int m = 12, n = 28;
	swap2(&m, &n);
	printf("%d %d", m, n);
}
