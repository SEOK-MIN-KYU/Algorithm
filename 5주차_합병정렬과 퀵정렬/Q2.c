#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int findPivot(int l, int r) {
	int k;
	srand(time(NULL));
	k = rand() % (r - l + 1) + l;
	return k;
}
int inPlacePartition(int* A, int l, int r, int k) {
	int p, tmp;
	int i, j;
	p = A[k];
	tmp = A[k];
	A[k] = A[r];
	A[r] = tmp;
	i = l;
	j = r - 1;
	while (i <= j) {
		while (i <= j && A[i] <= p)
			i += 1;
		while (j >= i && A[j] >= p)
			j -= 1;
		if (i < j) {
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
	}
	tmp = A[i];
	A[i] = A[r];
	A[r] = tmp;
	return i;
}
void inPlaceQuickSort(int* L, int l, int r) {
	int a, b, k, t;
	if (l >= r)
		return;
	k = findPivot(l, r);
	b = inPlacePartition(L, l, r, k);
	t = b;
	while (1) {
		if (L[t] != L[b]) {
			a = t + 1;
			break;
		}
		t--;
	}
	inPlaceQuickSort(L, l, a - 1);
	inPlaceQuickSort(L, b + 1, r);
}
void PRINT(int* L, int n) {
	int i;
	for (i = 0; i < n; i++)
		printf(" %d", L[i]);
}
int main() {
	int n, i;
	scanf("%d", &n);
	int* L = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		scanf("%d", &L[i]);
	inPlaceQuickSort(L, 0, n - 1);
	PRINT(L, n);
	free(L);
	return 0;
}