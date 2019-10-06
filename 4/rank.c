#define  MAX_VERTICES 100
#define  MAX_ELEMENTS 100
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


/// rank
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

int main() {
    int n = 10, m = 10;
    int x, y;
    Graph G;
    List L;
    make_null(&L);
    // scanf("%d%d", &n, &m);
    init_graph(&G, n+2);
    // for(int i = 0; i < m; i++) {
    //     scanf("%d%d", &x, &y);
    //     add_edge(&G, x, y);
    // }

    // add_edge(&G, 1, 3);
    // add_edge(&G, 3, 2);
    
    add_edge(&G, 1, 2);
    add_edge(&G, 2, 3);
    add_edge(&G, 1, 4);
    add_edge(&G, 3, 5);
    add_edge(&G, 4, 5);
    add_edge(&G, 3, 6);
    add_edge(&G, 4, 6);
    add_edge(&G, 3, 7);
    add_edge(&G, 4, 7);
    add_edge(&G, 6, 8);
    add_edge(&G, 8, 9);
    add_edge(&G, 5, 10);
    add_edge(&G, 7, 10);
    add_edge(&G, 9, 10);
    
    topo_sort(&G, &L);

    printf("\n");
    for(int i = 1; i <= n+2; i++) {
        printf("%d ", element_at(&L, i));
    }

}