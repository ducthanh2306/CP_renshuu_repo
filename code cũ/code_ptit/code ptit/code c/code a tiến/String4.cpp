#include <stdio.h>
#include <string.h>

int main() {
	char s1[200] = "Hoc vien Cong nghe Buu chinh Vien thong";
	char *p = strtok(s1, " ");
	while (p != NULL) {
		if (p[0] >= 97 && p[0] <= 122) {
			p[0] -= 32;
		}
		printf("%s\n", p);
		p = strtok(NULL, " ");
	}
}
