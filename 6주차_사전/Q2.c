#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int findElement(int* L, int k, int n) {
	int l, r, mid;
	l = 0;
	r = n - 1;
	while (l <= r) {
		mid = (l + r) / 2;
		if (k == L[mid])
			return mid;
		else if (k < L[mid])
			r = mid - 1;
		else
			l = mid + 1;
	}
	return l;
}
int main() {
	int n, k, i;
	int* L;
	scanf("%d %d", &n, &k);
	L = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		scanf("%d", &L[i]);
	printf(" %d", findElement(L, k, n));
	free(L);
	return 0;
}