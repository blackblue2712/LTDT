#include <stdio.h>
#define INFINITY 99999
#define MAXN 200
#define NO_EDGE 0

typedef struct {
    int n;
    int m;
    int L[MAXN][MAXN];
} Graph;

void init_graph(Graph* G, int n, int m ) {
    G->n = n;
    G->m = m;
    int i, j;
    for( i = 1; i <= n; i++) {
        for(j = 1; j <= m; j++) {
            G->L[i][j] = NO_EDGE;
        }
    }
}

void add_edge(Graph* G, int x, int y, int w) {
    G->L[x][y] = w;
}

int pi[MAXN][MAXN];
int next[MAXN][MAXN];

void Floyd_Warshall (Graph* G) {
    int u, v, k;
    for( u = 1; u <= G->n; u++) {
        for(v = 1; v <= G->n; v++) {
            pi[u][v] = INFINITY;
            next[u][v] = -1;
        }
    }

    for( u = 1; u <= G->n; u++) {
        pi[u][u] = 0;
    }

    for(u = 1; u <= G->n; u++) {
        for(v = 1; v <= G->n; v++) {
            if(G->L[u][v] != NO_EDGE) {
                pi[u][v] = G->L[u][v];
                next[u][v] = v;
            }
        }
    }

    for( k = 1; k <= G->n; k++) {
        for(u = 1; u <= G->n; u++) {
            for(v = 1; v <= G->n; v++) {
                // printf("outside if: k u v %d - %d - %d\n", k, u, v);
                if(pi[u][k] + pi[k][v] < pi[u][v] && pi[u][k] != INFINITY && pi[k][v] != INFINITY) {
                    // printf("k u v %d - %d - %d\n", k, u, v);
                    pi[u][v] = pi[u][k] + pi[k][v];
                    next[u][v] = next[u][k];
                }
            }
        }
    }

    int negative_cycle = 0;
    for( u = 1; u <= G->n; u++) {
        if(pi[u][u] < 0) {
            negative_cycle = 1;
            printf("negative cycle");
            return;
        }
    }
    printf("ok");

    // for(u = 1; u <= G->n; u++) {
    //     for(v = 1; v <= G->n; v++) {
    //         if(pi[u][v] == INFINITY) {
    //             printf("%d -> %d: oo\n", u, v);
    //         } else {
    //             printf("%d -> %d: %d\n", u, v, pi[u][v]);
    //         }
    //     }
    // }
}


int main () {
    int n = 8, m = 13;
    int x, y, w;
    Graph G;

    scanf("%d%d", &n, &m);
    init_graph(&G, n, m);

    for(int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        add_edge(&G, x, y, w);
    }
    
    // add_edge(&G, 1, 2, 4);
    // add_edge(&G, 1, 3, 4);
    // add_edge(&G, 3, 5, 4);
    // add_edge(&G, 3, 6, 2);
    // add_edge(&G, 4, 1, 3);
    // add_edge(&G, 4, 3, 2);
    // add_edge(&G, 5, 4, 1);
    // add_edge(&G, 5, 7, 5);
    // add_edge(&G, 6, 2, 3);
    // add_edge(&G, 6, 5, -3);
    // add_edge(&G, 7, 6, 2);
    // add_edge(&G, 7, 8, 2);
    // add_edge(&G, 8, 5, -2);

    // add_edge(&G, 1, 2, 7);
    // add_edge(&G, 1, 3, 9);
    // add_edge(&G, 1, 5, 14);
    // add_edge(&G, 2, 3, 10);
    // add_edge(&G, 2, 4, 15);
    // add_edge(&G, 3, 4, 11);
    // add_edge(&G, 3, 5, 2);
    // add_edge(&G, 4, 6, 6);
    // add_edge(&G, 5, 6, 9);

    // scanf("%d", &s);
    Floyd_Warshall(&G);

    return 0;
}