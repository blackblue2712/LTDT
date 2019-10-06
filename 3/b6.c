#include <stdio.h>
#define INFINITY 999999
#define MAXN 2000

typedef struct {
    int u , v;
    int w;
} Edge;

typedef struct {
    int n, m;
    Edge edges[1000];
} Graph;

void init_graph(Graph* G, int  n) {
    G->n = n;
    G->m = 0;
}

void add_edge(Graph* G, int u, int v, int w) {
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->edges[G->m].w = w;
    G->m++;
}

int pi[MAXN];
int p[MAXN];

void BellmanFord(Graph* G, int s) {
    int i, j, it;
    for( i = 1; i <= G->n; i++) {
        pi[i] = INFINITY;
    }
    pi[s] = 0;
    p[s] = -1;

    for(it = 1; it < G->n; it++) {
        for(int k = 0; k < G->m; k++) {
            int u = G->edges[k].u;
            int v = G->edges[k].v;
            int w = G->edges[k].w;
            if( pi[u] + w < pi[v]) {
                pi[v] = pi[u] + w;
                p[v] = u;
            }
        }
    }

    for( i = 1; i <= G->n; i++) {
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
    }

}

int main () {
    int n, m;
    int x, y, w;
    Graph G;

    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for(int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        add_edge(&G, x, y, w);
    }

    BellmanFord(&G, 1);

    return 0;
}