#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int e;
	struct node* next;
}N;
typedef struct vertex {
	int n;
	N* list;
}VERTEX;
typedef struct edge {
	int a, b, w;
}EDGE;
typedef struct graph {
	VERTEX* vertex;
	EDGE* edge;
}GRAPH;

N* getnode(int e) {
	N* p = (N*)malloc(sizeof(N));
	p->e = e;
	p->next = NULL;
	return p;
}
void initV(VERTEX* V, int n) {
	V->n = n;
	V->list = getnode(-1);
}
void initE(EDGE* E, int n) {
	int i, j, k = 0;
	for (i = 0; i < n; i++) {
		for (j = i; j < n; j++) {
			E[k].a = i + 1;
			E[k].b = j + 1;
			E[k].w = 0;
			k++;
		}
	}
}
void setE(EDGE* E, int index, int w) {
	E[index].w = w;
}
void setN(VERTEX* V1, VERTEX* V2, int e) {
	N* p = getnode(e);
	N* tmp;
	tmp = V1->list;
	if (tmp == NULL)
		V1->list = p;
	else {
		while (tmp->next != NULL) {
			if (tmp->next != NULL && tmp->next->e > e)
				break;
			tmp = tmp->next;
		}
		p->next = tmp->next;
		tmp->next = p;
	}
	if (V1 == V2)
		return;
	p = getnode(e);
	tmp = V2->list;
	if (tmp == NULL)
		V2->list = p;
	else {
		while (tmp->next != NULL) {
			if (tmp->next != NULL && tmp->next->e > e)
				break;
			tmp = tmp->next;
		}
		p->next = tmp->next;
		tmp->next = p;
	}
}
void schV(GRAPH* G, int n) {
	N* p = G->vertex[n].list;
	EDGE tmp;
	if (n < 0 || n > 5) {
		printf("-1\n");
		return;
	}
	while (p != NULL) {
		if (p->e == -1)
			p = p->next;
		tmp = G->edge[p->e];
		if (tmp.w != 0) {
			if (tmp.a == n + 1)
				printf(" %d %d", tmp.b, tmp.w);
			else
				printf(" %d %d", tmp.a, tmp.w);
		}
		p = p->next;
	}
	printf("\n");
}
void mdfE(GRAPH* G, int v1, int v2, int w) {
	int i, tmp;
	if ((v1 < 0 || v1 > 5) || (v2 < 0 || v2 > 5)) {
		printf("-1\n");
		return;
	}
	if (v1 > v2) {
		tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	for (i = 0; i < 21; i++) {
		if (G->edge[i].a == v1 + 1 && G->edge[i].b == v2 + 1) {
			if (G->edge[i].w == 0) {
				G->edge[i].w = w;
				setN(&(G->vertex[v1]), &(G->vertex[v2]), i);
			}
			else
				G->edge[i].w = w;
			break;
		}
	}
}
int main() {
	int i, e, a, b, w;
	char c;
	GRAPH* G;
	G = (GRAPH*)malloc(sizeof(G));
	G->vertex = (VERTEX*)malloc(sizeof(VERTEX) * 6);
	G->edge = (EDGE*)malloc(sizeof(EDGE) * 21);
	for (i = 0; i < 6; i++)
		initV(&(G->vertex[i]), i + 1);
	initE(G->edge, 6);

	setE(G->edge, 1, 1);
	setE(G->edge, 2, 1);
	setE(G->edge, 3, 1);
	setE(G->edge, 5, 2);
	setE(G->edge, 7, 1);
	setE(G->edge, 13, 4);
	setE(G->edge, 18, 4);
	setE(G->edge, 19, 3);

	setN(&(G->vertex[0]), &(G->vertex[1]), 1);
	setN(&(G->vertex[0]), &(G->vertex[2]), 2);
	setN(&(G->vertex[0]), &(G->vertex[3]), 3);
	setN(&(G->vertex[0]), &(G->vertex[5]), 5);
	setN(&(G->vertex[1]), &(G->vertex[2]), 7);
	setN(&(G->vertex[2]), &(G->vertex[4]), 13);
	setN(&(G->vertex[4]), &(G->vertex[4]), 18);
	setN(&(G->vertex[4]), &(G->vertex[5]), 19);
	while (1) {
		scanf("%c", &c);
		if (c == 'a') {
			scanf("%d", &e);
			schV(G, e - 1);
			getchar();
		}
		else if (c == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			mdfE(G, a - 1, b - 1, w);
			getchar();
		}
		else if (c == 'q')
			break;
	}
	free(G);
	return 0;
}
