#include <stdio.h>
#include <math.h>

int checkNT(int n) {
	if (n < 2) {
		return 0;
	}
	int i;
	for (i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;
}

int checkTN(int n) {
	int m = 0;
	int n1 = n;
	while (n != 0) {
		int d = n % 10;
		m = m * 10 + d;
		n /= 10;
	}
	if (n1 == m) {
		return 1;
	}
	return 0;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int a, b;
		scanf("%d %d", &a, &b);
		int i;
		int c = 0;
		for (i = a; i <= b; i++) {
			if (checkNT(i) && checkTN(i)) {
				printf("%d ", i);
				c++;
				if (c % 10 == 0) {
					printf("\n");
				}
			}
		}
		printf("\n");
	}
}
