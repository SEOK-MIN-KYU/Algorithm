#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
	int n, m, i, j, tmp;
	int* ary;
	scanf("%d", &n);
	ary = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		scanf("%d", &ary[i]);
	for (i = 1; i < n; i++) {
		tmp = ary[i];
		j = i - 1;
		while ((j >= 0) && (ary[j] > tmp)) {
			ary[j + 1] = ary[j];
			j -= 1;
		}
		ary[j + 1] = tmp;
	}
	for (i = 0; i < n; i++)
		printf("%d ", ary[i]);
	free(ary);
	return 0;
}