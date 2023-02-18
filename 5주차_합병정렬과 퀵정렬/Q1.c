#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int d;
	struct node* next;
}N;
typedef struct par {
	N* L1;
	N* L2;
}PAR;
PAR partition(N* L, int k) {
	N* L1 = L;
	N* L2;
	PAR p;
	N* q = L;
	int i;
	for (i = 0; i < k - 1; i++)
		q = q->next;
	L2 = q->next;
	q->next = NULL;
	p.L1 = L1;
	p.L2 = L2;
	return p;
}
N* merge(N** L1, N** L2) {
	N* L;
	N* p;
	N* A = L1;
	N* B = L2;
	if (A->d <= B->d) {
		L = A;
		A = A->next;
		p = L;
	}
	else {
		L = B;
		B = B->next;
		p = L;
	}
	while (A != NULL && B != NULL) {
		if (A->d <= B->d) {
			p->next = A;
			A = A->next;
			p = p->next;
		}
		else {
			p->next = B;
			B = B->next;
			p = p->next;
		}
	}
	while (A != NULL) {
		p->next = A;
		p = A;
		A = A->next;
	}
	while (B != NULL) {
		p->next = B;
		p = B;
		B = B->next;
	}
	return L;
}
void mergeSort(N** L, int s) {
	N* L1 = NULL;
	N* L2 = NULL;
	PAR p;
	if (s > 1) {
		p = partition(*L, s / 2);
		L1 = p.L1;
		L2 = p.L2;
		mergeSort(&L1, s / 2);
		mergeSort(&L2, s - s / 2);
		*L = merge(L1, L2);
	}
}
N* ADD(int d) {
	N* p = (N*)malloc(sizeof(N));
	p->d = d;
	p->next = NULL;
	return p;
}
void PRINT(N* L) {
	N* p = L;
	while (p != NULL) {
		printf(" %d", p->d);
		p = p->next;
	}
}
int main() {
	int n, i, d;
	N* H = (N*)malloc(sizeof(N));
	H->next = NULL;
	N* X = H;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &d);
		X->next = ADD(d);
		X = X->next;
	}
	mergeSort(&H->next, n);
	PRINT(H->next);
	free(H);
	return 0;
}