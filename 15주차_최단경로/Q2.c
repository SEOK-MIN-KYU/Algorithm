#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int element;
	struct node* next;
}N;
typedef struct vertex {
	int id, x, y;
	N* olist;
	N* ilist;
}VERTEX;
typedef struct edge {
	int a, b, weight;
}EDGE;
typedef struct graph {
	VERTEX* vertices;
	EDGE* edges;
}GRAPH;

GRAPH G;
int n, m;
N* getnode(int e) {
	N* p = (N*)malloc(sizeof(N));
	p->element = e;
	p->next = NULL;
	return p;
}
int opposite(N* e, int a) {
	EDGE E = G.edges[e->element];
	if (E.a == a)
		return E.b;
	else
		return E.a;
}
void insertAdj(N* p, int id) {
	N* q = getnode(id);
	while (p->next) {
		p = p->next;
	}
	p->next = q;
}
void insertEdge(int id, int a, int b, int w) {
	G.edges[id].a = a;
	G.edges[id].b = b;
	G.edges[id].weight = w;
	insertAdj(G.vertices[a].olist, id);
	insertAdj(G.vertices[b].ilist, id);
}
void BellmanFordShortestPaths(int st) {
	int i, j, u, z, e, weight;
	N* tmp;
	u = -1, weight = 0;
	for (i = 1; i <= n; i++) {
		G.vertices[i].x = 30000;
		G.vertices[i].y = -1;
	}
	G.vertices[st].x = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			u = G.edges[j].a;
			z = G.edges[j].b;
			weight = G.edges[j].weight;
			if (G.vertices[u].x != 30000 && (G.vertices[u].x + weight) < G.vertices[z].x) {
				G.vertices[z].y = u;
				G.vertices[z].x = G.vertices[u].x + weight;
			}
		}
	}
}
int main() {
	int i, a, b, w, st;
	scanf("%d %d %d", &n, &m, &st);
	G.edges = (EDGE*)malloc(sizeof(EDGE) * m);
	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * n + 1);
	for (i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].olist = getnode(-1);
		G.vertices[i].ilist = getnode(-1);
	}
	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &w);
		insertEdge(i, a, b, w);
	}
	BellmanFordShortestPaths(st);
	for (i = 1; i <= n; i++) {
		if (G.vertices[i].y != -1) {
			printf("%d %d\n", G.vertices[i].id, G.vertices[i].x);
		}
	}
	return 0;
}
