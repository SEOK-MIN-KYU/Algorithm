#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int element;
	struct node* next;
}N;
typedef struct vertex {
	char name;
	int inDegree;
	N* outEdges, * inEdges;
}VERTEX;
typedef struct edge {
	int origin, destination;
}EDGE;
typedef struct graph {
	VERTEX* vertices;
	EDGE* edges;
}GRAPH;
typedef struct queue {
	int f, r, * q;
}QUEUE;

GRAPH G;
QUEUE Q;
int n, m;
int* topOrder;

int isEmpty() {
	if ((Q.r + 1) % n == Q.f)
		return 1;
	else
		return 0;
}
void enqueue(int v) {
	Q.r = (Q.r + 1) % n;
	Q.q[Q.r] = v;
	return;
}
int dequeue() {
	int v;
	v = Q.q[Q.f];
	Q.f = (Q.f + 1) % n;
	return v;
}
int index(char vName) {
	int i;
	for (i = 0; i <= n - 1; i++) {
		if (G.vertices[i].name == vName)
			return i;
	}
}
void addFirst(N* H, int i) {
	N* node = (N*)malloc(sizeof(N));
	node->element = i;
	node->next = H->next;
	H->next = node;
	return;
}
void insertVertex(char vName, int i) {
	G.vertices[i].name = vName;
	G.vertices[i].outEdges->next = NULL;
	G.vertices[i].inEdges->next = NULL;
	G.vertices[i].inDegree = 0;
}
void insertDirectedEdge(char uName, char wName, int i) {
	int u, w;
	u = index(uName);
	w = index(wName);
	G.edges[i].origin = u;
	G.edges[i].destination = w;
	addFirst(G.vertices[u].outEdges, i);
	addFirst(G.vertices[w].inEdges, i);
	G.vertices[w].inDegree++;
	return;
}
void buildGraph() {
	char vName, uName, wName;
	int i;
	scanf("%d", &n);
	getchar();

	G.vertices = (VERTEX*)malloc(sizeof(VERTEX) * n);
	for (i = 0; i <= n - 1; i++) {
		G.vertices[i].outEdges = (N*)malloc(sizeof(N));
		G.vertices[i].inEdges = (N*)malloc(sizeof(N));
		scanf("%c", &vName);
		insertVertex(vName, i);
		getchar();
	}
	scanf("%d", &m);
	getchar();

	G.edges = (EDGE*)malloc(sizeof(EDGE) * m);
	for (i = 0; i <= m - 1; i++) {
		scanf("%c %c", &uName, &wName);
		insertDirectedEdge(uName, wName, i);
		getchar();
	}
	return;
}
void topologicalSort() {
	int* in, t, u, w, e, i;
	N* p;
	in = (int*)malloc(sizeof(int) * n);
	topOrder = (int*)malloc(sizeof(int) * (n + 1));

	Q.q = (int*)malloc(sizeof(int) * n);
	Q.f = 0;
	Q.r = n - 1;
	for (i = 0; i <= n - 1; i++) {
		in[i] = G.vertices[i].inDegree;
		if (in[i] == 0)
			enqueue(i);
	}
	t = 1;
	while (!isEmpty()) {
		u = dequeue();
		topOrder[t] = u;
		t += 1;
		p = G.vertices[u].outEdges->next;
		while (p != NULL) {
			e = p->element;
			w = G.edges[e].destination;
			in[w] -= 1;
			if (in[w] == 0)
				enqueue(w);
			p = p->next;
		}
	}
	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
	return;
}
int main() {
	int i;
	buildGraph();
	topologicalSort();
	if (topOrder[0] == 0)
		printf("0");
	else {
		for (i = 1; i <= n; i++)
			printf("%c ", G.vertices[topOrder[i]].name);
	}
	return 0;
}
