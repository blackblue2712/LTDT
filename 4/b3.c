#define  MAX_VERTICES 100
#define INFINITY 99999
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

    int b[MAX_VERTICES];
    int count = G->n;
    while(count >= 1) {
        int max = -1;
        int keyMax = 0;
        for (int i = 1; i <= G->n; i++) {
            if (max < rank[i] && rank[i] != INFINITY) {
                max = rank[i];
                keyMax = i;
            }
        }

        int min = INFINITY;
        int keyMin = 0;
        for (int i = 1; i <= G->n; i++) {
            if (min > rank[i] && rank[i] != INFINITY) {
                min = rank[i];
                keyMin = i;
            }
        }


        b[keyMax] = min;
        b[keyMin] = max;
        rank[keyMax] = INFINITY;
        rank[keyMin] = INFINITY;

        count--;
    }

    int s = 0;
    for (int i = 1; i <= G->n; i++) {
        printf("%d\n", b[i]);
        s+= b[i];
    }
    printf("%d\n", s);

}

int main() {
    int n = 7, m = 10;
    int x, y;
    Graph G;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        add_edge(&G, x, y);
    }

    // add_edge(&G, 1, 3);
    // add_edge(&G, 3, 2);
    
    // add_edge(&G, 2, 1);
    // add_edge(&G, 3, 1);
    // add_edge(&G, 4, 1);
    // add_edge(&G, 3, 2);
    // add_edge(&G, 6, 2);
    // add_edge(&G, 7, 3);
    // add_edge(&G, 5, 4);
    // add_edge(&G, 3, 5);
    // add_edge(&G, 7, 5);
    // add_edge(&G, 7, 6);
    
    ranking(&G);

    

}