#define white 0
#define black 1
#define gray 2
#define MAX_VERTICES 100
#include <stdio.h>
#define MAX_ELEMENTS 100

int color[MAX_VERTICES];
int fail;


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

// Tô màu đỉnh bằng phương pháp đệ quy
void colorize(Graph* G, int x, int c) {
    // Nếu đỉnh x chưa có màu, tô nó
    if(color[x] == -1) {
        color[x] = c;
        // Lấy các đỉnh kề  và tô màu các đỉnh kề bằng màu ngược với c
        List list = neighbors(G, x);
        int j;
        for(j = 1; j <= list.size; j++) {
            int y = element_at(&list, j);
            colorize(G, y, !c);
        }
    } else { // x đã có màu
        if(color[x] != c) { // 1 đỉnh bị tô 2 màu khác nhau
            fail = 1; // Thất bại
        }
    }
}

//  Kiểm tra đồ thị có là đồ thi phân đôi
int is_bigarph(Graph* G) {
    // Khởi tạo color, chưa đỉnh nào có màu
    int j;
    for(j = 1; j <= G->n; j++) {
        color[j] = -1;
    }
    fail = 0;
    colorize(G, 1, 0); // Tô màu đỉnh 1 bằng 1 màu đen
    // Nếu không thất bại, G là bigraph
    if(!fail) {
        for( int i = 1; i <= G->n; i++) {
            if( color[i] == 0) printf("%d ", i);
        }
        printf("\n");
        for( int i = 1; i <= G->n; i++) {
            if( color[i] == 1) printf("%d ", i);
        }
    } else {
        printf("IMPOSSIBLE");
    }
    return !fail;

}

int main () {
    Graph G;
    int n = 9, m;
    int u, v;

    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }


    // 1
    // add_edge(&G, 1, 2);
    // add_edge(&G, 2, 3);
    
    // 2 
    // add_edge(&G, 1, 2);
    // add_edge(&G, 2, 3);
    // add_edge(&G, 3, 1);

    // 3
    // add_edge(&G, 1, 2);
    // add_edge(&G, 1, 3);
    // add_edge(&G, 1, 4);
    // add_edge(&G, 1, 5);
    // add_edge(&G, 1, 6);
    // add_edge(&G, 1, 7);
    // add_edge(&G, 1, 8);
    // add_edge(&G, 1, 9);

    is_bigarph(&G);

    

    return 0;
}