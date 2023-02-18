#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
	int a, b, n, m, i;
	char ch;
	scanf("%d %d %d", &a, &b, &n);
	getchar();
	for (i = 0; i < n; i++) {
		scanf("%c", &ch);
		m = (a + b) / 2;
		if (ch == 'Y')
			a = m + 1;
		else
			b = m;
	}
	printf("%d", a);
}