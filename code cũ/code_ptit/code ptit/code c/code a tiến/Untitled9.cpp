#include <stdio.h>

int main() {
	
	int a;
	scanf("%d", &a);
	switch(a) {
		case 0: printf("khong"); break;
		case 1: printf("mot"); break;
		case 2: printf("hai"); break;
		//...
		default: printf("khong doc duoc");
	}
}
