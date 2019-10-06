#include <stdio.h>
#define INFINITY 999999
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
    for( i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            G->L[i][j] = NO_EDGE;
        }
    }
}

void add_edge(Graph* G, int x, int y, int w) {
    G->L[x][y] = w;
}

int mark[MAXN][MAXN];
int pi[MAXN][MAXN];
int p[MAXN][MAXN];

void Dijkstra (Graph* G) {
    int i, j, it, x, y;
    for( i = 0; i < G->n; i++) {
        for( j = 0; j < G->m; j++) {
            pi[i][j] = INFINITY;
            mark[i][j] = 0;
        }
    }
    pi[0][0] = G->L[0][0];
    p[0][0] = -1; // Trước đỉnh s không có đỉnh nào cả
    
    // Lặp n hoặc n-1 lần đều được
    
    for(it = 1; it < G->n*G->m; it++) {
        // 1. Tìm i có mark[i]] == 0 và có p[i] nhỏ nhất
        int min_pi = INFINITY;
        
        for( i = 0; i < G->n; i++) {
            for( j = 0; j < G->m; j++) {
                if(mark[i][j] == 0 && pi[i][j] < min_pi) {
                    min_pi = pi[i][j];
                    x = i;
                    y = j;
                }
            }
        }
        
        // Đánh dấu i đã xét
        mark[x][y] = 1;
        // printf("xy %d-%d \n", x, y);
        // 2. Cập nhật pi và p của các đỉnh kề của i (nếu thỏa)

        int di[] = {-1, 1, 0, 0};
        int dj[] = {0, 0, -1, 1};
        int ii, jj;
        // Duyệt qua các ô kề của ô (i, j)
        for( int k = 0; k < 4; k++) {
            ii = x + di[k];
            jj = y + dj[k];
            // printf("iijj %d-%d \n", ii, jj);
            // Kiểm tra ô (ii, jj) có nằm trong mê cung không
            if(ii >= 0 && ii < G->n && jj >= 0 && jj < G->m) {
                // printf("IF 1  -%d-%d - ===================================\n", ii, jj);
                if(pi[x][y] + G->L[ii][jj] < pi[ii][jj]) {
                    // printf("*****CONG pi[%d%d] = pi[%d%d] + G->L[%d%d] = %d + %d = %d\n", ii, jj, x, y, ii, jj, pi[x][y], G->L[ii][jj], pi[x][y] + G->L[ii][jj]);
                    pi[ii][jj] = pi[x][y] + G->L[ii][jj];
                    p[ii][jj] = x*G->m + y + 1;
                }
            }
        }
    }

    // printf("Generate result ... %d - %d\n", G->n, G->m);

    // for(i = 0; i < G->n; i++) {
    //     for(j = 0; j < G->m; j++) {
    //         printf("pi[%d-%d] = %d, p[%d-%d] = %d ||", i,j, pi[i][j], i,j, p[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d", pi[G->n - 1][G->m - 1]);
}

int main () {
    int r = 4, c = 5, value;
    int x, y, w;
    Graph G;

    scanf("%d%d", &r, &c);

    init_graph(&G, r, c);
    for( int i = 0; i < r; i++) {
        for( int j = 0; j < c; j++) {
            scanf("%d", &value);
            add_edge(&G, i, j, value);
        }
    }




    // add_edge(&G, 0, 0, 0);
    // add_edge(&G, 0, 1, 3);
    // add_edge(&G, 0, 2, 1);
    // add_edge(&G, 0, 3, 2);
    // add_edge(&G, 0, 4, 9);

    // add_edge(&G, 1, 0, 7);
    // add_edge(&G, 1, 1, 3);
    // add_edge(&G, 1, 2, 4);
    // add_edge(&G, 1, 3, 9);
    // add_edge(&G, 1, 4, 9);

    // add_edge(&G, 2, 0, 1);
    // add_edge(&G, 2, 1, 7);
    // add_edge(&G, 2, 2, 5);
    // add_edge(&G, 2, 3, 5);
    // add_edge(&G, 2, 4, 3);
    
    // add_edge(&G, 3, 0, 2);
    // add_edge(&G, 3, 1, 3);
    // add_edge(&G, 3, 2, 4);
    // add_edge(&G, 3, 3, 2);
    // add_edge(&G, 3, 4, 5);



    // add_edge(&G, 0, 0, 1);
    // add_edge(&G, 0, 1, 2);
    // add_edge(&G, 0, 2, 3);

    // add_edge(&G, 1, 0, 2);
    // add_edge(&G, 1, 1, 4);
    // add_edge(&G, 1, 2, 4);

    // add_edge(&G, 2, 0, 1);
    // add_edge(&G, 2, 1, 4);
    // add_edge(&G, 2, 2, 10);

    // add_edge(&G, 0, 0, 1);
    // add_edge(&G, 0, 1, 2);
    // add_edge(&G, 0, 2, 2);

    // add_edge(&G, 1, 0, 2);
    // add_edge(&G, 1, 1, 1);
    // add_edge(&G, 1, 2, 4);

    // add_edge(&G, 2, 0, 4);
    // add_edge(&G, 2, 1, 2);
    // add_edge(&G, 2, 2, 1);

    // add_edge(&G, 3, 0, 8);
    // add_edge(&G, 3, 1, 4);
    // add_edge(&G, 3, 2, 10);

    // for(int i = 0; i < r; i++) {
    //     for(int j = 0; j < c; j++) {
    //         printf("%d ", G.L[i][j]);
    //     }
    //     printf("\n");
    // }

    Dijkstra(&G);
    
    // int di[] = {-1, 1, 0, 0};
    // int dj[] = {0, 0, -1, 1};

    // // Đổi đỉnh u thành ô (i, j)
    // int u = 1;
    // int i = (u - 1) / c;
    // int j = (u - 1) % c;
    // int adjacent;

    // // Duyệt qua các ô kề của ô (i, j)
    // for( int k = 0; k < 4; k++) {
    //     ii = i + di[k];
    //     jj = j + dj[k];
    //     // Kiểm tra ô (ii, jj) có nằm trong mê cung không
    //     if(ii >= 0 && ii < r && jj >= 0 && jj < c) {
    //         adjacent = ii * c + jj + 1; // Đổi ô (ii, jj) thành đỉnh adjacent
    //         // adjacent là đỉnh kề của đỉnh u
    //     }
    // }

    return 0;
}




