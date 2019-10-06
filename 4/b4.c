#define  MAX_VERTICES 100
#define INFINITY 999
#include <stdio.h>
typedef struct {
    int n;
    int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph* G, int n) {
	int i, j;
	G->n = n;
	for(i = 0; i <= n; i++) {
		for(j = 0; j <= n; j++) {
			G->A[i][j] = 0;
		}
	}
}

void add_edge(Graph* G, int x, int y) {
	G->A[x][y] = 1;
}


typedef int ElementType;
typedef struct {
    ElementType data[MAX_VERTICES];
    int size;
} List;

// List methods
void make_null(List* L) {
    L->size = 0;
}
void push_back(List* L, ElementType x) {
    L->data[L->size] = x;
    L->size++;
}
ElementType element_at(List* L, int i) {
    return L->data[i-1];
}
int count_list(List*L) {
    return L->size;
}

int min(int a, int b) {
    if(a > b) {
        return b;
    } else {
        return a;
    }
}

int max(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}


// rank
int rank[MAX_VERTICES];
void topo_sort(Graph* G, List* L) {
    int d[MAX_VERTICES];
    int x, u;

    for( u = 1; u <= G->n; u++) {
        d[u] = 0;
    }

    for(x = 1; x <= G->n; x++) {
        for(u = 1;u <= G->n; u++) {
            if(G->A[x][u] != 0) {
                d[u]++;

            }
        }
    }

    List S1, S2;
    make_null(&S1);

    for(u = 1; u <= G->n; u++) {
        if(d[u] == 0) {
            push_back(&S1, u);
        }
    }

    int k = 1, i;
    while(S1.size > 0) {
        make_null(&S2);
        for(i = 1; i <= S1.size; i++) {
            int u = element_at(&S1, i);
            rank[u] = k;
            push_back(L, u);
            int v;
            for(v = 1; v <= G->n; v++) {
                if(G->A[u][v] != 0) {
                    d[v]--;
                    if(d[v] == 0) {
                        push_back(&S2, v);
                    }
                }
            }
        }
        S1 = S2;
        k++;
    }
}

int d[MAX_VERTICES];
int main() {
    int n;
    int x, u, v, j;
    List ips;
    List L;
    make_null(&L);
    Graph G;
    scanf("%d", &n);
    init_graph(&G, n+2);
    d[n+1] = 0;

    // add_edge(&G, 1, 2);
    // add_edge(&G, 2, 3);
    // add_edge(&G, 1, 4);
    // add_edge(&G, 3, 5);
    // add_edge(&G, 4, 5);
    // add_edge(&G, 3, 6);
    // add_edge(&G, 4, 6);
    // add_edge(&G, 3, 7);
    // add_edge(&G, 4, 7);
    // add_edge(&G, 6, 8);
    // add_edge(&G, 8, 9);
    // add_edge(&G, 5, 10);
    // add_edge(&G, 7, 10);
    // add_edge(&G, 9, 10);
    // d[1] = 7;
    // d[2] = 3;
    // d[3] = 1;
    // d[4] = 8;
    // d[5] = 2;
    // d[6] = 1;
    // d[7] = 1;
    // d[8] = 2;
    // d[9] = 2;
    // d[10] = 1;

    for(int i = 1; i <= n; i++) {
        make_null(&ips);
        while(1) {
            scanf("%d", &x);
            if(x == 0) break;
            push_back(&ips, x);
        }
        for(int j = 2; j <= ips.size; j++) {
            if(element_at(&ips, j) != 0) {
                add_edge(&G, element_at(&ips, j), i);
            }
        }
        d[i] = element_at(&ips, 1);
    }

    // 2. Thêm cung nối alpha với các đỉnh có bậc vào bằng 0
    for( u = 1; u <= n; u++) {
        int deg_neg = 0;
        for(x = 1; x <= n; x++) {
            if(G.A[x][u] > 0) {
                deg_neg++;
            }
            if(deg_neg == 0) {
                // printf("deg_nef %d \n", u);
                add_edge(&G, n+1, u); // Đỉnh alpha là đỉnh n+1
            }
        }
    }
    // add_edge(&G, n+1, 1);

    // 3. Thêm cung nối các đỉnh có bậc ra = 0 vào beta
    for( u = 1; u <= n; u++) {
        int deg_pos = 0;
        for(v = 1; v <= n; v++) {
            if(G.A[u][v] > 0) {
                deg_pos++;
            }
        }
        if(deg_pos == 0) {
            add_edge(&G, u, n+2); // Đỉnh beta là đỉnh n+2
        }
    }
    // add_edge(&G, 10, n+2);


    // 4. Xếp thứ tự topo và lưu vào trong L
    topo_sort(&G, &L);


    // 5. Tính t[u]
    int t[MAX_VERTICES];
    t[n+1] = 0; // t[alpha] = 0
    for(j = 2; j <= L.size; j++) {
        int u = element_at(&L, j);
        t[u] = -1;
        for(x = 1; x <= G.n; x++) {
            if(G.A[x][u] > 0) {
                t[u] = max(t[u], t[x] + d[x]);
            }
        }
    }

     // 6. Tính T[u]
    int T[MAX_VERTICES];
    T[n+2] = t[n+2];
    for(j = L.size - 1; j >= 1; j--) {
        int u = element_at(&L, j);
        T[u] = INFINITY;
        for(v = 1; v <= G.n; v++ ) {
            if(G.A[u][v] > 0) {
                T[u] = min(T[u], T[v] - d[u]);
            }
        }
    }

   

    // 7. In kết quả ra màn hình
    printf("%d \n", t[n+2]);
    for(int z = 1; z <= n+2; z++) {
        printf("%d-%d \n", t[z], T[z]);
    }

    // printf("%d %d", t[11], T[11]);

    return 0;
    

}