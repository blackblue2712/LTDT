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
int p[MAXN];
int p1[MAXN];
int mark[MAXN];
int marks[MAXN][MAXN];
int cnt[MAXN];

int Dijkstra (Graph* G, int s) {
    int i, j, it;
    for( i = 1; i <= G->n; i++) {
        p1[i] = INFINITY;
        cnt[i] = 0;
        mark[i] = 0;
    }
    p1[s] = 0;
    p[s] = -1; // Trước đỉnh s không có đỉnh nào cả

    // Lặp n hoặc n-1 lần đều được
    for( it = 1; it < G->n; it++) {
        // 1. Tìm i có mark[i]] == 0 và có p[i] nhỏ nhất
        int min_p1 = INFINITY;
        for( j = 1; j <= G->n; j++) {
            if(mark[j] == 0 && p1[j] < min_p1) {
                min_p1 = p1[j];
                i = j;
            }
        }
        // Đánh dấu i đã xét
        mark[i] = 1;
        // 2. Cập nhật p1 và p của các đỉnh kề của i (nếu thỏa)
        for( j = 1; j <= G->n; j++) {
            if(G->L[i][j] != NO_EDGE && mark[j] == 0) {
                if(p1[i] + G->L[i][j] < p1[j]) {
                    p1[j] = p1[i] + G->L[i][j];
                    cnt[j] = 1;
                    p[j] = i;
                } else if(p1[i] + G->L[i][j] == p1[j]) {
                    cnt[j] += 1;
                }
            }
        }
    }

    // printf("Generate result ... \n");
    // for(i = 1; i <= G->n; i++) {
    //     printf("p1[%d] = %d, cnt[%d] = %d\n", i, p1[i], i, cnt[i]);
    // }

    if(p1[G->n] == INFINITY) {
        printf("-1 0");
    } else {
        printf("%d %d\n", p1[G->n], cnt[G->n]);
    }
}


int main () {
    int n = 3, m = 3;
    int x, y, w;
    Graph G;

    // scanf("%d%d", &n, &m);
    init_graph(&G, n, m);

    // for(int i = 1; i <= m; i++) {
    //     scanf("%d%d%d", &x, &y, &w);
    //     add_edge(&G, x, y, w);
    // }
    
    add_edge(&G, 1, 2, 2);
    add_edge(&G, 2, 3, 4);
    add_edge(&G, 1, 3, 6);

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

    // scanf("%d", &s)
    Dijkstra(&G, 1);
    

    return 0;
}
