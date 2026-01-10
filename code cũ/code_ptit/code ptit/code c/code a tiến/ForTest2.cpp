#include <stdio.h>

int main() {
	int test;
	scanf("%d", &test);
	for (int i = 0; i < test; i++) {
		int n;
		scanf("%d", &n);
		printf("%d\n", n * 2);
	}
	
}
