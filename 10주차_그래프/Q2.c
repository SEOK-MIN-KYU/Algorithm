#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct vertex {
	int n;
}VERTEX;
typedef struct edge {
	int a, b, w;
}EDGE;
typedef struct graph {
	VERTEX* vertex;
	EDGE* edge;
	int** M;
}GRAPH;

int EN(GRAPH* G, int a, int b) {
	int i;
	for (i = 0; i < 21; i++) {
		if (G->edge[i].a == a && G->edge[i].b == b)
			return i;
	}
}
void initM(GRAPH* G, int a, int b, int w) {
	int n, m, e;

	if (a < b) {
		n = a;
		m = b;
	}
	else {
		n = b;
		m = a;
	}
	e = EN(G, n, m);
	G->edge[e].w = w;
	G->M[a - 1][b - 1] = e;
	G->M[b - 1][a - 1] = e;
}
void schV(GRAPH* G, int n) {
	int i, e;

	if (n <= 0 || n > 6) {
		printf("-1");
		return;
	}
	for (i = 0; i < 6; i++) {
		e = G->M[n - 1][i];
		if (e == -1)
			continue;
		if (G->edge[e].a == n)
			printf("%d %d ", G->edge[e].b, G->edge[e].w);
		else if (G->edge[e].b == n)
			printf("%d %d ", G->edge[e].a, G->edge[e].w);
	}
}
void mdfE(GRAPH* G, int a, int b, int w) {
	int n, m, e;

	if ((a <= 0 || a > 6) || (b <= 0 || b > 6)) {
		printf("-1\n");
		return;
	}
	if (a < b) {
		n = a;
		m = b;
	}
	else {
		n = b;
		m = a;
	}
	e = EN(G, n, m);
	if (w == 0) {
		w = -1;
		G->M[a - 1][b - 1] = -1;
		G->M[b - 1][a - 1] = -1;
	}
	else {
		G->M[a - 1][b - 1] = e;
		G->M[b - 1][a - 1] = e;
	}
	G->edge[e].w = w;
}
int main() {
	int i, j, tmp = 0, n, m, w;
	char c;
	GRAPH* G = (GRAPH*)malloc(sizeof(GRAPH));

	G->vertex = (VERTEX*)malloc(sizeof(VERTEX) * 6);
	G->edge = (EDGE*)malloc(sizeof(EDGE) * 21);
	G->M = (int**)malloc(sizeof(int*) * 21);
	for (i = 0; i < 6; i++) {
		G->M[i] = (int*)malloc(sizeof(int) * 6);
		for (j = 0; j < 6; j++) {
			G->M[i][j] = -1;
		}
	}
	for (i = 0; i < 6; i++)
		G->vertex[i].n = i + 1;
	for (i = 0; i < 6; i++) {
		for (j = i; j < 6; j++) {
			G->edge[tmp].a = i + 1;
			G->edge[tmp].b = j + 1;
			tmp++;
		}
	}

	initM(G, 1, 2, 1);
	initM(G, 1, 3, 1);
	initM(G, 1, 4, 1);
	initM(G, 1, 6, 2);
	initM(G, 2, 3, 1);
	initM(G, 3, 5, 4);
	initM(G, 5, 5, 4);
	initM(G, 5, 6, 3);
	while (1) {
		scanf("%c", &c);
		if (c == 'a') {
			scanf("%d", &n);
			schV(G, n);
			printf("\n");
			getchar();
		}
		else if (c == 'm') {
			scanf("%d %d %d", &n, &m, &w);
			mdfE(G, n, m, w);
			getchar();
		}
		else if (c == 'q')
			break;
	}
	free(G);
	return 0;
}
