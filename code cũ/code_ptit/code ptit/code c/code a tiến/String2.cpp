#include <stdio.h>
#include <string.h>

int main() {
	char s1[200] = "Hoc vien";
	printf("%s\n", s1);
	char s2[100];
	strcpy(s2, s1);
	printf("%s\n", s2);
	
}
