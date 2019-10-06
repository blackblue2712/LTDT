#include <stdio.h>

#define MAX_VERTICES 100
#define MAX_EDGES 500

typedef struct {
	int n, m;
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph* G, int n, int m) {
	int i, j;
	G->n = n;
	G->m = m;
	for(i = 0; i <= n; i++) {
		for(j = 0; j <= m; j++) {
			G->A[i][j] = 0;
		}
	}
}

// void add_edge(Graph* G, int e, int x, int y) {
// 	G->A[x][e] = 1;
// 	G->A[y][e] = 1;
// }
void add_edge(Graph* G, int x, int y) {
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}

// int adjacent(Graph* G, int x, int y) {
// 	int e;
// 	for(e = 1; e <= G->m; e++) {
// 		if(G->A[x][e] == 1 && G->A[y][e] == 1) {
// 			return 1;
// 		}
// 	}
// 	return 0;
// }
int adjacent(Graph* G, int x, int y) {
	return G->A[x][y] != 0;
}

// int degree(Graph* G, int x) {
// 	int e, deg = 0;
// 	for( e = 1; e <= G->m; e++) {
// 		if(G->A[x][e] == 1) {
// 			deg++;
// 		}
// 	}
// 	return deg;
// }
int degree(Graph* G, int x) {
	int y, deg = 0;
	for( y = 1; y <= G->m; y++) {
		deg +=  G->A[x][y];
	}
	return deg;
}

int main () {
	Graph G;
	int n, m, u, v, e;
	FILE* fp;
	fp = freopen("data.txt", "r", stdin);

	fscanf(fp, "%d%d", &n, &m);
	init_graph(&G, n, m);
	
	
	for (e = 0; e < m; e++) {
		fscanf(fp, "%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			printf("%d ", G.A[i][j]);
		}
		printf("\n");
	}

	// printf("\n");

	// for (int i = 1; i <= n; i++) {
	// 	printf("def(%d) = %d\n", i, degree(&G, i));
	// 	buff[i-1] = degree(&G, i);
	// }

	// int maxLevel = buff[0];
	// int maxIndex = 1;
	// for(int i = 1; i < n; i++) {
	// 	if(buff[i] > maxLevel) {
	// 		maxLevel = buff[i];
	// 		maxIndex = i + 1;
	// 	}
	// }

	// printf("%d %d", maxIndex, maxLevel);
}

