#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int M[1000][100];
int V[100000];

void BFS(int v, int n) {
	int q[100000] = { 0 };
	int k;
	int i, f = -1, r = -1;
	r++;
	q[r] = v;
	V[v] = 1;
	printf("%d\n", v);
	while (f < r) {
		f++;
		k = q[f];
		for (int i = 1; i <= n; i++) {
			if (!V[i] && M[k][i]) {
				r++;
				V[i] = 1;
				q[r] = i;
				printf("%d\n", i);
			}
		}
	}
}
int main() {
	int n, m, s, i, a, b;
	scanf("%d %d %d", &n, &m, &s);
	for (i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		M[a][b] = 1;
		M[b][a] = 1;
	}
	for (i = 1; i <= n; i++)
		V[i] = 0;
	BFS(s, n);
	return 0;
}
