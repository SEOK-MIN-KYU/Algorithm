#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int key;
	struct node* next;
}N;
N* H;
int M;
int h(int x) {
	return x % M;
}
void insertItem(int x) {
	int v;
	v = h(x);
	N* p = H + v;
	N* q = (N*)malloc(sizeof(N));
	q->key = x;
	q->next = p->next;
	p->next = q;
}
int findElement(int x) {
	int v, c = 0;
	v = h(x);
	N* p = H + v;
	if (p->next == NULL)
		return 0;
	else {
		while (1) {
			p = p->next;
			c++;
			if (p->key == x)
				return c;
			if (p->next == NULL)
				return 0;
		}
	}
}
int removeElement(int x) {
	int v, c = 0;
	v = h(x);
	N* p = H + v;
	N* q = H + v;
	if (p->next == NULL)
		return 0;
	else {
		while (1) {
			p = p->next;
			c++;
			if (p->key == x) {
				while (q->next != p) {
					q = q->next;
				}
				q->next = p->next;
				free(p);
				return c;
			}
			if (p->next == NULL)
				return 0;
		}
	}
}
void PRINT() {
	int i;
	N* p;
	for (i = 0; i < M; i++) {
		p = H + i;
		if (p->next != NULL) {
			p = p->next;
			printf(" %d", p->key);
			while (p->next != NULL) {
				p = p->next;
				printf(" %d", p->key);
			}
		}
	}
	printf("\n");
}
int main() {
	int x, i;
	char c;
	scanf("%d", &M);
	H = (N*)malloc(sizeof(N) * M);
	for (i = 0; i < M; i++) {
		(H + i)->key = NULL;
		(H + i)->next = NULL;
	}
	while (1) {
		scanf("%c", &c);
		if (c == 'i') {
			scanf("%d", &x);
			insertItem(x);
			getchar();
		}
		else if (c == 's') {
			scanf("%d", &x);
			printf("%d\n", findElement(x));
			getchar();
		}
		else if (c == 'd') {
			scanf("%d", &x);
			printf("%d\n", removeElement(x));
			getchar();
		}
		else if (c == 'p') {
			PRINT();
			getchar();
		}
		else if (c == 'e') {
			break;
		}
	}
	free(H);
	return 0;
}