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

void add_edge(Graph* G, int x, int y) {
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}


int adjacent(Graph* G, int x, int y) {
	return G->A[x][y] != 0;
}

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
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);
	int buff[225];
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			printf("%d ", G.A[i][j]);
		}
		printf("\n");
	}

}
