#define  MAX_VERTICES 100

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

void add_edge(Graph* G, int e, int x, int y) {
	G->A[x][e] = 1;
	G->A[y][e] = 1;
}
int adjacent(Graph* G, int x, int y) {
    int j;
    for(j = 1; j <= G->adj[x].size; j++) {
        if(element_at(&G->adj[x], j) == y) {
            return 1;
        }
    }
    return 0;
}

int degree(Graph* G, int x) {
	int y, deg = 0;
	for( y = 1; y <= G->m; y++) {
		deg +=  G->A[x][y];
	}
	return deg;
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

List neighbors(Graph* G, int x) {
    int y;
    List list;
    make_null(&list);
    for(y = 1; y <= G->n; y++) {
        if(adjacent(G, x, y)) {
            push_back(&list, y);
        }
    }
    return list;
}

// rank
int rank[MAX_VERTICES];
void ranking(Graph* G) {
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