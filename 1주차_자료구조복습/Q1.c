#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	char elem;
	struct node* prev;
	struct node* next;
}N;
typedef struct list {
	N* head;
	N* tail;
	int s;
}L;
void initialize(L* list) {
	list->head = (N*)malloc(sizeof(N));
	list->tail = (N*)malloc(sizeof(N));
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->s = 0;
}
void addNodeBefore(N* p, char e) {
	N* q;
	q = (N*)malloc(sizeof(N));
	q->elem = e;
	q->prev = p->prev;
	q->next = p;
	p->prev->next = q;
	p->prev = q;
}

void add(L* list, int r, char e) {
	int i;
	N* p;
	p = list->head;
	if ((r < 1) || (r > list->s + 1))
		printf("invalid position\n");
	else {
		for (i = 0; i < r; i++)
			p = p->next;
		addNodeBefore(p, e);
		list->s++;
	}
}
void delete(L* list, int r) {
	int i;
	N* p;
	p = list->head;
	if ((r < 1) || (r > list->s))
		printf("invalid position\n");
	else {
		for (i = 0; i < r; i++)
			p = p->next;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		list->s--;
		free(p);
	}
}
char get(L* list, int r) {
	int i;
	N* p;
	p = list->head;
	if ((r < 1) || (r > list->s))
		return -1;
	else {
		for (i = 0; i < r; i++)
			p = p->next;
		return p->elem;
	}
}
void print(L* list) {
	N* p;
	p = list->head;
	while (p->next != list->tail) {
		p = p->next;
		printf("%c", p->elem);
	}
	printf("\n");
}
int main() {
	int i, n, r;
	char ch, e;
	L* list = (L*)malloc(sizeof(L));
	initialize(list);
	scanf("%d", &n);
	getchar();
	for (i = 0; i < n; i++) {
		scanf("%c", &ch);
		if (ch == 'A') {
			scanf("%d %c", &r, &e);
			getchar();
			add(list, r, e);
		}
		else if (ch == 'D') {
			scanf("%d", &r);
			getchar();
			delete(list, r);
		}
		else if (ch == 'G') {
			scanf("%d", &r);
			getchar();
			if (get(list, r) == -1)
				printf("invalid position\n");
			else
				printf("%c", get(list, r));

		}
		else {
			print(list);
			getchar();
		}
	}
	free(list);
	return 0;
}