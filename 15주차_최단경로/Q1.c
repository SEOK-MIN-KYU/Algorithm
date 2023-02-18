#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int element;
	struct node* next;
}N;
typedef struct vertex {
	int id, x, y;
	N* list;
}VERTEX;
typedef struct edge {
	int a, b, weight;
}EDGE;
typedef struct graph {
	VERTEX* vertices;
	EDGE* edges;
}GRAPH;
typedef struct queue {
	int m, s;
	int* k, * v;
}QUEUE;

GRAPH G;
QUEUE Q;
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
int isEmpty() {
	if (Q.s == 0)
		return 1;
	else
		return 0;
}
void insertAdj(int id, int a, int b) {
	N* p = G.vertices[a].list;
	N* q;
	while (p->next) {
		p = p->next;
	}
	q = getnode(id);
	p->next = q;
}
void insertEdge(int id, int a, int b, int w) {
	G.edges[id].a = a;
	G.edges[id].b = b;
	G.edges[id].weight = w;
	insertAdj(id, a, b);
	if (a != b)
		insertAdj(id, b, a);
}
void initqueue(int s) {
	Q.m = s;
	Q.s = 0;
	Q.k = malloc(sizeof(int) * s);
	Q.v = malloc(sizeof(int) * s);
}
void enqueue(int k, int v) {
	int size = Q.s;
	Q.k[size] = k;
	Q.v[size] = v;
	Q.s++;
}
int dequeue() {
	int i, mk, mv, mi = 0;
	mk = Q.k[0];
	mv = Q.v[0];

	for (i = 1; i < Q.m; i++) {
		if (Q.k[i] < mk) {
			mk = Q.k[i];
			mv = Q.v[i];
			mi = i;
		}
	}
	Q.k[mi] = 30000;
	Q.v[mi] = -1;
	Q.s--;
	return mv;
}
int search(int t) {
	int i;
	for (i = 0; i < Q.m; i++) {
		if (Q.v[i] == t)
			return 1;
	}
	return 0;
}
void replace(int t, int k) {
	int i;
	for (i = 0; i < Q.m; i++) {
		if (Q.v[i] == t)
			Q.k[i] = k;
	}
}
void DijkstraShortestPaths(int st) {
	int i, z, e, u = -1;
	N* tmp;
	for (i = 1; i <= n; i++) {
		G.vertices[i].x = 100000;
		G.vertices[i].y = -1;
	}
	G.vertices[st].x = 0;
	initqueue(n);
	for (i = 1; i <= n; i++)
		enqueue(G.vertices[i].x, i);
	while (!isEmpty()) {
		u = dequeue();
		if (u == -1)
			break;
		tmp = G.vertices[u].list;
		while (tmp->next) {
			z = opposite(tmp->next, u);
			e = (tmp->next->element);
			if (search(z) && (G.edges[e].weight + G.vertices[u].x) < G.vertices[z].x) {
				G.vertices[z].y = u;
				G.vertices[z].x = G.edges[e].weight + G.vertices[u].x;
				replace(z, G.vertices[z].x);
			}
			tmp = tmp->next;
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
		G.vertices[i].list = getnode(-1);
	}
	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &w);
		insertEdge(i, a, b, w);
	}
	DijkstraShortestPaths(st);
	for (i = 1; i <= n; i++) {
		if (G.vertices[i].y != -1) {
			printf("%d %d\n", G.vertices[i].id, G.vertices[i].x);
		}
	}
	return 0;
}
