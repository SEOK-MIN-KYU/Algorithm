#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int H[100];
int n;
void downHeap(int i) {
	int tmp, m;
	int l = i * 2;
	int r = i * 2 + 1;
	if ((l > n) && (r > n))
		return;
	m = l;
	if (r <= n) {
		if (H[r] > H[m])
			m = r;
	}
	if (H[i] >= H[m])
		return;
	tmp = H[i];
	H[i] = H[m];
	H[m] = tmp;
	downHeap(m);
}
void rBuildHeap(int i) {
	if (i > n)
		return;
	rBuildHeap(i * 2);
	rBuildHeap(i * 2 + 1);
	downHeap(i);
	return;
}
void buildHeap() {
	int i;
	for (i = n / 2; i > 0; i--)
		downHeap(i);
	return;
}
void printHeap() {
	int i;
	for (i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}
int main() {
	int i;
	scanf("%d", &n);
	for (i = 1; i < n + 1; i++) {
		scanf("%d", &H[i]);
		getchar();
	}
	rBuildHeap(1);
	printHeap();
	return 0;
}