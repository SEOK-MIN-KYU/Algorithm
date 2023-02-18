#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct node {
	int key;
	int height;
	struct node* parent;
	struct node* lChild;
	struct node* rChild;
}N;
N* root;
int isExternal(N* w) {
	if ((w->lChild == NULL) && (w->rChild == NULL))
		return 1;
	else
		return 0;
}
int isInternal(N* w) {
	if ((w->lChild != NULL) || (w->rChild != NULL))
		return 1;
	else
		return 0;
}
N* treeSearch(N* w, int k) {
	if (isExternal(w))
		return w;
	if (k == w->key)
		return w;
	else if (k < w->key)
		return treeSearch(w->lChild, k);
	else
		return treeSearch(w->rChild, k);
}
N* sibling(N* w) {
	if (w->parent == NULL)
		return;
	if (w->parent->lChild == w)
		return w->parent->rChild;
	else
		return w->parent->lChild;
}
N* reduceExternal(N* z) {
	N* w, * zs, * g;
	w = z->parent;
	zs = sibling(z);
	if (w->parent == NULL) {
		root = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
	}
	free(z);
	free(w);
	return zs;
}
N* expandExternal(N* w) {
	N* l = (N*)malloc(sizeof(N));
	N* r = (N*)malloc(sizeof(N));
	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = w;
	l->height = 0;
	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = w;
	r->height = 0;
	w->lChild = l;
	w->rChild = r;
	w->height = 1;
	return w;
}
int findElement(int k) {
	N* w = treeSearch(root, k);
	if (isExternal(w))
		return -1;
	else
		return w->key;
}
N* inOrderSucc(N* w) {
	w = w->rChild;
	if (isExternal(w))
		return;
	while (isInternal(w->lChild))
		w = w->lChild;
	return w;
}
int updateHeight(N* w) {
	int h;
	if (w->lChild->height > w->rChild->height)
		h = w->lChild->height + 1;
	else
		h = w->rChild->height + 1;
	if (h != w->height) {
		w->height = h;
		return 1;
	}
	else
		return 0;
}
int isBalanced(N* w) {
	if (abs(w->lChild->height - w->rChild->height) < 2)
		return 1;
	else
		return 0;
}
N* restructure(N* x, N* y, N* z) {
	N* a, * b, * c;
	N* T0, * T1, * T2, * T3;
	if ((z->key < y->key) && (y->key < x->key)) {
		a = z;
		b = y;
		c = x;

		T0 = a->lChild;
		T1 = b->lChild;
		T2 = c->lChild;
		T3 = c->rChild;
	}
	else if ((x->key < y->key) && (y->key < z->key)) {
		a = x;
		b = y;
		c = z;

		T0 = a->lChild;
		T1 = a->rChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else if ((z->key < x->key) && (x->key < y->key)) {
		a = z;
		b = x;
		c = y;

		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else {
		a = y;
		b = x;
		c = z;

		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	if (z->parent == NULL) {
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z) {
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else {
		z->parent->rChild = b;
		b->parent = z->parent;
	}
	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);

	c->lChild = T2;
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	b->lChild = a;
	b->rChild = c;
	a->parent = b;
	c->parent = b;
	updateHeight(b);

	return b;
}
void searchAndFixAfterInsertion(N* w)
{
	N* x, * y, * z;
	w->lChild->height = 0;
	w->rChild->height = 0;
	w->height = 1;
	if (w->parent == NULL)
		return NULL;
	z = w->parent;
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}

	if (isBalanced(z))
		return;
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;
	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else
		x = y->rChild;

	restructure(x, y, z);

	return;
}
void searchAndFixAfterRemoval(N* w) {
	N* x, * y, * z, * b;
	if (w == NULL)
		return;
	z = w;
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}

	if (isBalanced(z))
		return;
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else if (y->lChild->height < y->rChild->height)
		x = y->rChild;
	else {
		if (z->lChild == y)
			x = y->lChild;
		else if (z->rChild == y)
			x = y->rChild;
	}
	b = restructure(x, y, z);
	searchAndFixAfterRemoval(b->parent);
}
void insertItem(N* root, int k) {
	N* w = treeSearch(root, k);
	if (isInternal(w))
		return;
	else {
		w->key = k;
		expandExternal(w);
		searchAndFixAfterInsertion(w);
	}
}
int removeElement(N* root, int k) {
	int e;
	N* z, * y, * zs;
	N* w = treeSearch(root, k);
	if (isExternal(w))
		return -1;
	e = w->key;
	z = w->lChild;
	if (!isExternal(z))
		z = w->rChild;
	if (isExternal(z))
		zs = reduceExternal(z);
	else {
		y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		zs = reduceExternal(z);
	}
	searchAndFixAfterRemoval(zs->parent);

	return e;
}
void PRINT(N* w) {
	if (isExternal(w))
		return;
	else {
		printf(" %d", w->key);
		PRINT(w->lChild);
		PRINT(w->rChild);
	}
}
int main() {
	int k, s;
	char c;
	root = (N*)malloc(sizeof(N));
	root->parent = NULL;
	root->lChild = NULL;
	root->rChild = NULL;
	while (1) {
		scanf("%c", &c);
		if (c == 'i') {
			scanf("%d", &k);
			insertItem(root, k);
			getchar();
		}
		else if (c == 'd') {
			scanf("%d", &k);
			s = removeElement(root, k);
			if (s == -1)
				printf("X\n");
			else
				printf("%d\n", s);
			getchar();
		}
		else if (c == 's') {
			scanf("%d", &k);
			s = findElement(k);
			if (s == -1)
				printf("X\n");
			else
				printf("%d\n", s);
			getchar();
		}
		else if (c == 'p') {
			PRINT(root);
			printf("\n");
		}
		else if (c == 'q')
			break;
	}
	free(root);
	return 0;
}