#include <stdio.h>

void readArray(int a[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
}

void printArray(int a[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
}

int find(int a[], int n, int x) {
	int i;
	for (i = 0; i < n; i++) {
		if (a[i] == x) {
			return i;
		}
	}
	return -1;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	int a[n];
	readArray(a, n);
	printArray(a, n);
	int f = find(a, n, k);
	if (f >= 0) {
		printf("\n%d", f);
	} else {
		printf("\nkhong tim thay");
	}
}
