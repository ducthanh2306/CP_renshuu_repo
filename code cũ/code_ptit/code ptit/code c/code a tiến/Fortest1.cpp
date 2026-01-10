#include <stdio.h>

int main() {
//	int i;
//	for (i = 0; i < 10; i = i + 1) {
//		printf("Hello %d\n", i);
//	}
	int n = 3, m = 4;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d", i + j);
			printf("\n");
		}
	}
}
