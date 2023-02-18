#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int key;
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
	if ((w->lChild != NULL) && (w->rChild != NULL))
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
N* expandExternal(N* z) {
	N* l = (N*)malloc(sizeof(N));
	N* r = (N*)malloc(sizeof(N));
	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = z;
	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = z;
	z->lChild = l;
	z->rChild = r;
	return z;
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
void insertItem(N* root, int k) {
	N* w = treeSearch(root, k);
	if (isInternal(w))
		return;
	else {
		w->key = k;
		expandExternal(w);
	}
}
int removeElement(N* root, int k) {
	int e;
	N* z, * y;
	N* w = treeSearch(root, k);
	if (isExternal(w))
		return -1;
	e = w->key;
	z = w->lChild;
	if (!isExternal(z))
		z = w->rChild;
	if (isExternal(z))
		reduceExternal(z);
	else {
		y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		reduceExternal(z);
	}
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
	return 0;
	free(root);
}