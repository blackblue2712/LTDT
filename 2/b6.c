#define white 0
#define black 1
#define gray 2
#define MAX_VERTICES 100
#include <stdio.h>
#define MAX_ELEMENTS 100

int color[MAX_VERTICES];
int cycle;
int mark[MAX_VERTICES];


//List
typedef int ElementType;
typedef struct {
    ElementType data[MAX_ELEMENTS];
    int size;
} List;
// Graph
typedef struct {
    int n;
    List adj[MAX_VERTICES];
} Graph;
// Queue
typedef struct {
    int data[MAX_ELEMENTS];
    int front, rear;
} Queue;

List a;

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
int adjacent(Graph* G, int x, int y) {
    int j;
    for(j = 1; j <= G->adj[x].size; j++) {
        if(element_at(&G->adj[x], j) == y) {
            return 1;
        }
    }
    return 0;
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

// Graph methods
void init_graph(Graph* G, int n) {
    int i, j;
    G->n = n;
    for(i = 1; i <= n; i++) {
        make_null(&G->adj[i]);
    }
}
void add_edge(Graph* G, int x, int y) { 
    push_back(&G->adj[x], y);
    push_back(&G->adj[y], x);
}

// Queue methods
void make_null_queue (Queue* Q) {
    Q->front = 0;
    Q->rear = -1;
}

void push (Queue* Q, int x) {
    Q->rear++;
    Q->data[Q->rear] = x;
}

int top(Queue* Q) {
    return Q->data[Q->front];
}

void pop(Queue* Q) {
    Q->front++;
}

int empty(Queue* Q) {
    return Q->front > Q->rear;
}

// Duyệt đồ thị bắt đầu từ đỉnh
void dfs(Graph* G, int x, int parent) {

    color[x] = gray;
    int j;
    List list = neighbors(G, x);
    for(j = 1; j <= count_list(&list); j++) {
        int y = element_at(&list, j);
        // if(x == 2) printf("x%d\n", list.size);
        if(y == parent) continue;
        // printf("%d\n", y);
        
        if(color[y] == gray) {
            cycle = 1;
            return;
        }
        if(color[y] == white) {
            // printf("recursive%d\n", x);
            dfs(G, y, x);
        }
    }
    color[x] = black;
}

// Kiểm tra toàn bộ đồ thị
int contains_cycle(Graph* G) {
    int j;
    for( j = 1; j <= G->n; j++) {
        color[j] = white;
    }
    cycle = 0;
    for(j = 1; j <= G->n; j++) {
        if(color[j] == white) {
            dfs(G, j, 0);
        }
    }
    return cycle;
}


int main () {
    Graph G;
    int n = 13, m;
    int u, v;

    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    for(int i = 1; i <= m; i++) {
        if(G.adj[i].size > 1) {
            // printf("main%d\n", i);
            for(int j = 1; j <= G.adj[i].size; j++) {
                for(int k = j+1; k < G.adj[i].size; k++) {
                    if(element_at(G.adj, j) == element_at(G.adj, k)) {
                        printf("NO");
                        return 0;
                    }
                }   
            }
        }
    }

    // printf("size%d\n", G.adj[3].size);

    // 1
    // add_edge(&G, 1, 3);
    // add_edge(&G, 2, 3);
    
    // 2 
    // add_edge(&G, 1, 2);
    // add_edge(&G, 1, 3);
    // add_edge(&G, 1, 4);
    // add_edge(&G, 2, 3);
    // add_edge(&G, 2, 6);
    // add_edge(&G, 3, 5);
    // add_edge(&G, 3, 7);
    // add_edge(&G, 4, 5);
    // add_edge(&G, 5, 7);

    // 3
    // add_edge(&G, 1, 2);
    // add_edge(&G, 1, 3);
    // add_edge(&G, 2, 4);
    // add_edge(&G, 2, 5);
    // add_edge(&G, 2, 6);
    // add_edge(&G, 3, 5);
    // add_edge(&G, 3, 6);
    // add_edge(&G, 4, 7);
    // add_edge(&G, 5, 7);

    // 4
    // add_edge(&G, 1, 2);
    // add_edge(&G, 2, 3);

    // 5
    // add_edge(&G, 1, 2);
    // add_edge(&G, 2, 3);
    // add_edge(&G, 2, 4);

    if(contains_cycle(&G) == 1) {
        printf("NO");
    } else {
        printf("YES");
    }

    return 0;
}