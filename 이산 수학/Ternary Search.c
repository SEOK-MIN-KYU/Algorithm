#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int ternarySearch(int x, int a[], int n) {
	int i, j, l, u, loc;
	i = 1;
	j = n;
	l = (i + j) / 3;
	u = 2 * (i + j) / 3;
	while (i < j - 1) {
		if (x > a[u])
			i = u + 1;
		else if (x > a[l]) {
			i = l + 1;
			j = u;
		}
		else
			j = l;
		l = i + (j - i) / 3;
		u = j - (j - i) / 3;
	}
	if (x == a[i])
		loc = i;
	else if (x == a[j])
		loc = j;
	else
		loc = 0;
	return loc;
}
int main() {
	int x, n, i;
	int* a;
	scanf("%d", &x);
	scanf("%d", &n);
	a = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);
	printf("%d", ternarySearch(x, a, n - 1));
	free(a);
	return 0;
}