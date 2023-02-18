#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int H[100];
int n;
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
int removeMax() {
	int key;
	key = H[1];
	H[1] = H[n];
	n -= 1;
	downHeap(1);
	return key;
}
void printHeap() {
	int i;
	for (i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}
int main() {
	char c;
	int key;
	while (1) {
		scanf("%c", &c);
		if (c == 'i') {
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
			getchar();
		}
		else if (c == 'd') {
			printf("%d\n", removeMax());
			getchar();
		}
		else if (c == 'p') {
			printHeap();
			getchar();
		}
		else
			break;
	}
	return 0;

}