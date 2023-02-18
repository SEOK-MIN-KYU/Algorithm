#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int M, n, q;
int* H;

int h(int x) {
	return x % M;
}
int hd(int x) {
	return q - (x % q);
}
int getNextBucket(int v, int i, int x) {
	return (v + i * hd(x)) % M;
}
int insertItem(int x) {
	int v, i, j, b;
	v = h(x);
	i = 0;
	while (i < M) {
		b = getNextBucket(v, i, x);
		if (H[b] == 0) {
			H[b] = x;
			for (j = 0; j < i; j++)
				printf("C");
			return b;
		}
		else
			i++;
	}
}
int findElement(int x) {
	int v, i, b;
	v = h(x);
	i = 0;
	while (i < M) {
		b = getNextBucket(v, i, x);
		if (H[b] == 0) {
			return -1;
		}
		else if (x == H[b]) {
			return b;
		}
		else
			i++;
	}
	return -1;
}
void PRINT() {
	int i;
	for (i = 0; i < M; i++)
		printf(" %d", H[i]);
	printf("\n");
}
int main() {
	int x, n, i, f;
	char c;
	scanf("%d %d %d", &M, &n, &q);
	H = (int*)malloc(sizeof(int) * M);
	for (i = 0; i < M; i++)
		*(H + i) = 0;
	while (1) {
		scanf("%c", &c);
		if (c == 'i') {
			scanf("%d", &x);
			printf("%d\n", insertItem(x));
			getchar();
		}
		else if (c == 's') {
			scanf("%d", &x);
			f = findElement(x);
			if (f == -1)
				printf("-1\n");
			else
				printf("%d %d\n", f, *(H + f));
			getchar();
		}
		else if (c == 'p') {
			PRINT();
			getchar();
		}
		else if (c == 'e') {
			PRINT();
			break;
		}
	}
	free(H);
	return 0;
}