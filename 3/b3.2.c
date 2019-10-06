#include <stdio.h>
#define INFINITY 999999
#define MAXN 200
#define NO_EDGE 0

typedef struct {
    int n;
    int L[MAXN][MAXN];
} Graph;

void init_graph(Graph* G, int n ) {
    G->n = n;
    int i, j;
    for( i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            G->L[i][j] = NO_EDGE;
        }
    }
}

void add_edge(Graph* G, int x, int y, int w) {
    G->L[x][y] = w;
}

int mark[MAXN];
int pi[MAXN];
int p[MAXN];

void Dijkstra (Graph* G, int s) {
    int i, j, it;
    for( i = 1; i <= G->n; i++) {
        pi[i] = INFINITY;
        mark[i] = 0;
    }
    pi[s] = 0;
    p[s] = -1; // Trước đỉnh s không có đỉnh nào cả

    // Lặp n hoặc n-1 lần đều được
    for( it = 1; it < G->n; it++) {
        // 1. Tìm i có mark[i]] == 0 và có p[i] nhỏ nhất
        int min_pi = INFINITY;
        for( j = 1; j <= G->n; j++) {
            if(mark[j] == 0 && pi[j] < min_pi) {
                min_pi = pi[j];
                i = j;
            }
        }
        // Đánh dấu i đã xét
        mark[i] = 1;
        // 2. Cập nhật pi và p của các đỉnh kề của i (nếu thỏa)
        for( j = 1; j <= G->n; j++) {
            if(G->L[i][j] != NO_EDGE && mark[j] == 0) {
                if(pi[i] + G->L[i][j] < pi[j]) {
                    pi[j] = pi[i] + G->L[i][j];
                    p[j] = i;
                }
            }
        }
    }

    printf("Generate result ... \n");
    for(i = 1; i <= G->n; i++) {
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
    }

    // if(pi[G->n] == INFINITY) {
    //     printf("-1");
    // } else {
    //     printf("%d", pi[G->n]);
    // }

    printf("%d", pi[G->n]);
}

int main () {
    int n = 4, m = 3;
    int x, y, w;
    Graph G;

    scanf("%d%d", &n, &m);

    init_graph(&G, n);
    for( int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        add_edge(&G, x, y, w);
    }


    //
    // add_edge(&G, 1, 2, 5);
    // add_edge(&G, 2, 3, 2);
    // add_edge(&G, 3, 4, 1);
    //
    // add_edge(&G, 1, 2, 3);
    // add_edge(&G, 2, 4, 4);
    // add_edge(&G, 1, 4, 10);


    Dijkstra(&G, 1);

    return 0;
}
