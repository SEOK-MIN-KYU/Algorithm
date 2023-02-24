#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int* change(int c[], int n) {
	int i, d[4];
	for (i = 0; i < 4; i++) {
		d[i] = 0;
		while (n >= c[i]) {
			d[i] = d[i] + 1;
			n -= c[i];
		}
	}
	return d;
}
int main() {
	int c[4] = { 25, 10, 5, 1 };
	int* d;
	int n;
	scanf("%d", &n);
	d = change(c, n);
	printf("quarter : %d, dime : %d, nickel : %d, penny : %d\n", d[0], d[1], d[2], d[3]);
}