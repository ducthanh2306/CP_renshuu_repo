#include <stdio.h>
#include <string.h>

int main() {
	char s1[200] = "apple";
	char s2[200] = "Banana";
	int x = strcmp(s1, s2);
	int x = stricmp(s1, s2);
	printf("%d", x);
}
