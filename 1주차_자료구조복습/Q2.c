#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}N;
void addTree(N* tree, int x, int y, int z) {
	if (tree == NULL)
		return;
	N* lc = (N*)malloc(sizeof(N));
	N* rc = (N*)malloc(sizeof(N));
	lc->data = y;
	lc->left = NULL;
	lc->right = NULL;
	rc->data = z;
	rc->left = NULL;
	rc->right = NULL;
	if (tree->data == x) {
		if (y != 0)
			tree->left = lc;
		else {
			tree->left = NULL;
			free(lc);
		}
		if (z != 0)
			tree->right = rc;
		else {
			tree->right = NULL;
			free(rc);
		}
	}
	else {
		free(lc);
		free(rc);
	}
	addTree(tree->left, x, y, z);
	addTree(tree->right, x, y, z);
}
void search(N* tree, char str[100]) {
	int i;
	printf(" %d", tree->data);
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == 'L')
			tree = tree->left;
		else if (str[i] == 'R')
			tree = tree->right;
		else
			return -1;
		printf(" %d", tree->data);
	}
	printf("\n");
}
int main() {
	int n, m, x, y, z, i;
	char str[100];
	N* tree = (N*)malloc(sizeof(N));
	N* lc = (N*)malloc(sizeof(N));
	N* rc = (N*)malloc(sizeof(N));
	lc->left = NULL;
	lc->right = NULL;
	rc->left = NULL;
	rc->right = NULL;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d %d", &x, &y, &z);
		if (i == 0) {
			tree->data = x;
			lc->data = y;
			rc->data = z;
			if (y != 0)
				tree->left = lc;
			else
				free(lc);
			if (z != 0)
				tree->right = rc;
			else
				free(rc);
		}
		else
			addTree(tree, x, y, z);
	}
	scanf("%d", &m);
	for (i = 0; i < m; i++) {
		scanf("%s", str);
		search(tree, str);
	}
	free(tree);
	return 0;
}