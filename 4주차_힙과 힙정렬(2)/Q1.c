#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int H[100];
int n, x;
void upHeap(int i) {
	int tmp, p = i / 2;
	if (i == 1)
		return;
	if (H[i] <= H[p])
		return;
	tmp = H[i];
	H[i] = H[p];
	H[p] = tmp;
	upHeap(p);
}
void insertItem(int key) {
	n += 1;
	H[n] = key;
	upHeap(n);
}
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
void inPlaceHeapSort() {
	int i, tmp;
	x = n;
	for (i = n; i >= 2; i--) {
		tmp = H[1];
		H[1] = H[i];
		H[i] = tmp;
		n--;
		downHeap(1);
	}
}
void printArray() {
	int i;
	for (i = 1; i <= x; i++)
		printf(" %d", H[i]);
}
int main() {
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}
	rBuildHeap(1);
	inPlaceHeapSort();
	printArray();
	return 0;
}