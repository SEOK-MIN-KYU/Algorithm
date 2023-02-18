#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int rFE(int* L, int k, int l, int r) {
	int mid;
	if (l > r)
		return r;
	mid = (l + r) / 2;
	if (k == L[mid])
		return mid;
	else if (k < L[mid])
		return rFE(L, k, l, mid - 1);
	else
		return rFE(L, k, mid + 1, r);
}
int findElement(int* L, int k, int n) {
	return rFE(L, k, 0, n -1);
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