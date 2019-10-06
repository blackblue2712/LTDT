#include <stdio.h>

int main () {
	int n, m;
	int count = 0;
	scanf("%d", &n);
	scanf("%d", &m);
	int buff[n][m];

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			scanf("%d", &buff[i][j]);
		}
	}
	

	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < m; j ++ ) {
			printf("%d ", buff[i][j]);
			if(buff[i][j] > 0) count ++;
		}
		printf("\n");
	}

	printf("%d ", count);

	return 0;
}

