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
	printf("\n");
}

void sort(int a[], int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (a[i] < a[j]) {
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	int a[n];
	readArray(a, n);
	printArray(a, n);
	sort(a, n);
	printArray(a, n);
}
