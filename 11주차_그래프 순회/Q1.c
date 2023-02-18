#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int e;
	struct node* next;
}N;
typedef struct vertex {
	int num;
	int f;
	N* list;
}VERTEX;
typedef struct edge {
	int a, b, num;
}EDGE;
typedef struct graph {
	VERTEX* vertex;
	EDGE* edge;
}GRAPH;

GRAPH G;
int  n, m, s;

N* getnode(int e) {
	N* p = (N*)malloc(sizeof(N));
	p->e = e;
	p->next = NULL;
	return p;
}
int opposite(N* p, int a) {
	EDGE E = G.edge[p->e];
	if (E.a == a)
		return E.b;
	else
		return E.a;
}
void Insert(int a, int b, int num) {
	N* p = G.vertex[a].list;
	N* q = getnode(num);
	int v, v1;

	if (p->next == NULL)
		G.vertex[a].list->next = q;
	else {
		while (p->next != NULL) {
			v = opposite(p->next, a);
			if (v > b) {
				q->next = p->next;
				G.vertex[a].list->next = q;
				return;
			}
			else {
				if (p->next->next != NULL) {
					v1 = opposite(p->next->next, a);
					if (v1 > b) {
						q->next = p->next->next;
						p->next->next = q;
						return;
					}
				}
			}
			p = p->next;
		}
	}
	p->next = q;
}
void initE(int a, int b, int num) {
	G.edge[num].a = a;
	G.edge[num].b = b;
	G.edge[num].num = num;
	Insert(a, b, num);
	if (a != b)
		Insert(b, a, num);
}
void DFS(int u) {
	int w;
	G.vertex[u].f = 1;
	printf("%d\n", G.vertex[u].num);
	N* p = G.vertex[u].list;
	while (p->next != NULL) {
		w = opposite(p->next, u);
		if (G.vertex[w].f == 0)
			DFS(w);
		p = p->next;
	}
}
int main() {
	int i, a, b, num;
	scanf("%d %d %d", &n, &m, &s);
	G.vertex = (VERTEX*)malloc(sizeof(VERTEX) * n);
	G.edge = (EDGE*)malloc(sizeof(EDGE) * m);
	for (i = 1; i <= n; i++) {
		G.vertex[i].num = i;
		G.vertex[i].f = 0;
		G.vertex[i].list = getnode(-1);
	}
	for (i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		initE(a, b, i);
	}
	DFS(s);
	return 0;
}
