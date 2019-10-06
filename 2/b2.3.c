#include <stdio.h>
#define MAX_ELEMENTS 100
#define MAX_VERTICES 100
int mark[MAX_VERTICES];
int parent[MAX_VERTICES];
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


// check mark
int isAllMark(int m[], Graph* G) {
    for(int j = 1; j <= G->n; j++) {
        if(m[j] == 0) return j;
    }
    return 0;
}

// Duyệt đệ quy đỉnh x
void traversal(Graph* G, int x, int p) {
    // printf("x%d - markx%d\n", x, mark[x]);
    if(mark[x] == 1) return;
    mark[x] = 1;
    parent[x] = p;
    // Lấy các đỉnh kề của nó và duyệt đỉnh kề
    List list = neighbors(G, x);
    int j;
    for(j = 1; j <= list.size; j++) {
        int y = element_at(&list, j);
        traversal(G, y, x);
        // if(y != 1 && parent[y] != 0) {
        //     if(parent[y] == -1) parent[y] = x;
        // }
    }
}

// Duyệt đồ thị theo chiều sâu (đệ qui)
void depth_first_search(Graph* G) {
    // Khởi tạo mark, chưa đỉnh nào được xét
    int j;
    for(j = 1; j <= G->n; j++) {
        mark[j] = 0;
        parent[j] = -1;
    }
    parent[1] = 0;
    // traversal(G, isAllMark(mark, G));
    while(isAllMark(mark, G) != 0) {
        traversal(G, isAllMark(mark, G), 0);
        // parent[isAllMark(mark, G)] = 0;
    }
    for( int i = 1; i <= G->n; i++) {
        printf("%d %d\n", i, parent[i]);
        
    }
}

int main () {
    Graph G;
    int n = 4, m;
    int u, v;

    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    // add_edge(&G, 1, 4);
    // add_edge(&G, 1, 2);
    // add_edge(&G, 1, 12);
    // add_edge(&G, 2, 4);
    // add_edge(&G, 3, 7);
    // add_edge(&G, 4, 6);
    // add_edge(&G, 4, 7);
    // add_edge(&G, 5, 6);
    // add_edge(&G, 5, 8);
    // add_edge(&G, 5, 9);
    // add_edge(&G, 6, 7);
    // add_edge(&G, 6, 13);
    // add_edge(&G, 8, 9);
    // add_edge(&G, 10, 11);
    // add_edge(&G, 10, 12);
    // add_edge(&G, 11, 12);
    // add_edge(&G, 2, 4);

    // 1.
    // add_edge(&G, 2, 1);
    // add_edge(&G, 1, 3);
    // add_edge(&G, 2, 4);

    // 2.
    // add_edge(&G, 1, 2);
    // add_edge(&G, 3, 4);

    // 3.
    // add_edge(&G, 1, 4);
    // add_edge(&G, 2, 3);

    

    depth_first_search(&G);
    return 0;
}