#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int M;
int* H;

int h(int x) {
	return x % M;
}
int getNextBucket(int v, int i) {
	return (v + i) % M;
}
int insertItem(int x) {
	int v, i, j, b;
	v = h(x);
	i = 0;
	while (i < M) {
		b = getNextBucket(v, i);
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
		b = getNextBucket(v, i);
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
int main() {
	int x, n, i, f;
	char c;
	scanf("%d", &M);
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
		else if (c == 'e')
			break;
	}
	free(H);
	return 0;
}