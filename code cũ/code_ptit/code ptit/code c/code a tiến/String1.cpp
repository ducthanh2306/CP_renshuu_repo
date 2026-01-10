#include <stdio.h>
#include <string.h>

int main() {
	char s1[200];
//	scanf("%s", &s1);
	gets(s1);
	puts(s1);
	printf("%d", strlen(s1));
	int i;
	for (i = 0; i < strlen(s1); i++) {
		printf("%c\n", s1[i]);
	}
//	printf("%s", s1);
}
