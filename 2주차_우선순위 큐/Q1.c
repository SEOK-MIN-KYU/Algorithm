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
	for (i = n - 1; i >= 0; i--) {
		m = i;
		for (j = 0; j < i; j++) {
			if (ary[j] > ary[m])
				m = j;
		}
		tmp = ary[i];
		ary[i] = ary[m];
		ary[m] = tmp;
	}
	for (i = 0; i < n; i++)
		printf("%d ", ary[i]);
	free(ary);
	return 0;
}