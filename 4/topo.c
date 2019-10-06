#define  MAX_VERTICES 100
#define INFINITY 99999
#define MAX_ELEMENTS 100

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
    ElementType data[MAX_ELEMENTS];
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
    return a > b ? b : a;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    Graph G;
    int n, u, x, v ,j;
    List L;
    make_null(&L);

    // 1. Đọc đồ thị

    // 2. Thêm cung nối alpha với các đỉnh có bậc vào bằng 0
    for(u = 1; u <= n; u++) {
        int deg_neg = 0;
        for(x = 1; x <= n; x++) {
            if(G.A[x][u] > 0) {
                deg_neg++;
            }
            if(deg_neg == 0) {
                add_edge(&G, n+1, u); // Đỉnh alpha là đỉnh n+1
            }
        }
    }

    // 3. Thêm cung nối các đỉnh có bậc ra = 0 vào beta
    for(u = 1; u <= n; u++) {
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

    // 4. Xếp thứ tự topo và lưu vào trong L
    topo_sort(&G, &L);

    // 5. Tính t[u]
    int t[MAX_VERTICES];
    t[n+1] = 0; // t[alpha] = 0
    for(j = 2; j <= L.size; j++) {
        int u = element_at(&L, j);
        t[u] = INFINITY;
        for(x = 1; x <= G.n; x++) {
            if(G.A[x][u] > 0) {
                t[u] = min(t[u], t[x] + d[x]);
            }
        }
    }

    // 6. Tính T[u]
    T[n+2] = t[n+2];
    for(j = L.size - 1; j >= 1; j--) {
        int u = element_at(&L, j);
        t[u] = -1;
        for(v = 1; v <= G.n; v++ ) {
            if(G.A[u][v] > 0) {
                T[u] = max(T[u], T[v] - d[u]);
            }
        }
    }

    // 7. In kết quả ra màn hình


    return 0;
}