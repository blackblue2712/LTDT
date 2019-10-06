#include <stdio.h>
#define MAX_ELEMENTS 100
#define MAX_VERTICES 100
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
// Stack
typedef struct {
    int data[MAX_ELEMENTS];
    int size;
} Stack;
// 

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

// Stack methods
void make_null_stack (Stack* S) {
    S->size = 0;
}

void push (Stack* S, int x) {
    S->data[S->size] = x;
    S->size++;
}

int top (Stack* S) {
    return S->data[S->size - 1];
}

void pop(Stack* S) {
    S->size--;
}

int empty(Stack* S) {
    return S->size == 0;
}

// check mark
int isAllMark(int m[], Graph* G) {
    for(int j = 1; j <= G->n; j++) {
        if(m[j] == 0) return j;
    }
    return 0;
}

void depth_first_search(Graph* G) {
    Stack L;
    int mark[MAX_ELEMENTS];
    int u[MAX_ELEMENTS];
    int parent[MAX_VERTICES];
    make_null_stack(&L);

    // Khởi tạo mark, chưa đỉnh nào được xét
    int j;
    for(j = 1; j <= G->n; j++) {
        mark[j] = 0;
        parent[j] = 0;
    }

    // Đưa 1 vào L
    push(&L, 1);
    u[1] = 1;
    parent[1] = 0;
    // Vòng lặp chính dùng để  duyệt
    while(!empty(&L)) {
        // Lấy phầ n tử đầu tiên trong L ra
        int x = top(&L); pop(&L);
        if(mark[x] != 0 && isAllMark(mark, G) != 0 && empty(&L)) {
            int notMark = isAllMark(mark, G);
            // printf("notmark %d\n", notMark);
            push(&L, notMark);
            continue;
        } else if(mark[x] != 0){
            continue;
        }
        // printf("%d\n", x);
        mark[x]= 1;
        // Lấy các đỉnh kề của nó
        List list = neighbors(G, x);
        // Xét các đỉnh kề của nó
        for (j = 1; j <= list.size; j++) {
            int y = element_at(&list, j);
            // if(y == 2) printf("x%d\n", x);
            push(&L, y); // Đưa vào hàng đợi đê lát nữa xét
            if(y == 1 || mark[y] != 0) continue;
            u[y] = y;
            parent[y] = x;
        }

        

        // if(isAllMark(mark, G) != 0 && empty(&L)) {
        //     int notMark = isAllMark(mark, G);
        //     printf("notmark %d\n", notMark);
        //     push(&L, notMark);
        // }
    }

    for(int i = 1; i <= G->n; i++) {
        printf("%d %d\n", i, parent[i]);
    }
    
}

int main () {
    Graph G;
    int n, m;
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
