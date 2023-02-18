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
typedef struct sack {
	int r;
	int k;
	int* d;
}SACK;

GRAPH G;
QUEUE Q;
int n, m;
N* getnode(int e) {
	N* p = (N*)malloc(sizeof(N));
	p->element = e;
	p->next = NULL;
	return p;
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
	int i;
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
	Q.k[mi] = 100000;
	Q.v[mi] = -1;
	Q.s--;
	return mv;
}
SACK* getSack(int r, int k) {
	int i;
	SACK* S = malloc(sizeof(SACK));
	S->r = r + 1;
	S->k = k;
	S->d = malloc(sizeof(int) * (r + 1));
	for (i = 0; i < S->r; i++)
		S->d[i] = -1;
	return S;
}
int find(SACK* S, int e) {
	return S->d[e];
}
void Union(SACK* S, int a, int b) {
	S->k--;
	for (int i = 0; i < S->r; i++) {
		if (S->d[i] == b)
			S->d[i] = a;
	}
}
void Kruskal() {
	int i, t, a, b, r = 0;
	SACK* S;
	initqueue(m);
	for (i = 0; i < m; i++) {
		enqueue(G.edges[i].weight, i);
	}
	S = getSack(n, n);
	for (i = 1; i <= n; i++) {
		S->d[i] = i;
	}
	while (Q.s != 0) {
		t = dequeue();
		a = G.edges[t].a;
		b = G.edges[t].b;
		if (find(S, a) != find(S, b)) {
			r = r + G.edges[t].weight;
			printf(" %d", G.edges[t].weight);
			Union(S, find(S, a), find(S, b));
		}
	}
	printf("\n%d", r);
}
int main() {
	int i, a, b, w;
	scanf("%d %d", &n, &m);
	G.edges = (EDGE*)malloc(sizeof(EDGE) * m);
	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * n + 1);
	for (i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].list = getnode(-1);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &w);
		insertEdge(i, a, b, w);
	}
	Kruskal();
	return 0;
}