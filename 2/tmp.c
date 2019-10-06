




// 


#define white 0
#define black 1
#define gray 2
#define MAX_VERTICES 100
#include <stdio.h>
#define MAX_ELEMENTS 100

int on_stack[MAX_VERTICES];
int num[MAX_VERTICES];
int min_mun[MAX_VERTICES];
int idx = 1;
int count = 0;

typedef struct {
    int n;
    int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

//List
typedef int ElementType;
typedef struct {
    ElementType data[MAX_ELEMENTS];
    int size;
} List;
// Stack
typedef struct {
    int data[MAX_ELEMENTS];
    int size;
} Stack;
Stack S;


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

int min (int a, int b) {
    return a > b ? b : a;
}

void init_graph(Graph* G, int n) {
    int i, j;
    G->n = n;
    for( i = 1; i <= n; i++) {
        for( j = 1; j <= n; j++) {
            G->A[i][j] = 0;
        }
    }
}

void add_edge(Graph* G, int x, int y) {
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}

int adjacent(Graph* G, int x, int y) {
    return G->A[x][y] != 0;
}

// List neighbors(Graph* G, int x) {
//     int y;
//     List list;
//     make_null(&list);
//     for(y = 1; y <= G->n; y++) {
//         if(adjacent(G, x, y)) {
//             push_back(&list, y);
//         }
//     }
//     return list;
// }

List neighbors(Graph* G, int x) {
	List list;
	int y, t = 0;
	make_null(&list);
	for(y = 1; y <= G->n; y++) {
		for(int e = 1; e <= G->n; e++) {
			if(G->A[x][e] == 1 && G->A[y][e] == 1 && y != x) {
				for(int u = 1; u <= list.size; u++) 
					if( element_at(&list, u) == y )
						t = 1;
					else t = 0;
					    if(t != 1)
					        push_back(&list, y);
			}
		}
	}
	return list;
}

void strong_connect(Graph* G, int x) {
    num[x] = min_mun[x] = idx; idx++;
    push(&S, x); // Đưa x vào stack
    on_stack[x] = 1; // x đang ở trong stack
    // Lấy các đỉnh kề và duyệt nó
    List list = neighbors(G, x);
    for(int j = 1; j <= list.size; j++) {
        int y = element_at(&list, j);
        if(num[y] == -1) {
            strong_connect(G, y);
            min_mun[x] = min(min_mun[x], min_mun[y]);
        } else if(on_stack[y]) {
            min_mun[x] = min(min_mun[x], num[y]);
        }
    }

    // Kiểm tra nếu num[x] == min_num[x]]
    if(num[x] == min_mun[x]) {
        count++;
        printf("count");
        // Loại bỏ các đỉnh ra khỏi stack
        int w;
        do {
            w = top(&S); pop(&S);
            on_stack[w] = 0;
            //
        } while(w != x);
    }

}

int main () {
    Graph G;
    int n = 8, m;
    int u, v;

    // scanf("%d%d", &n, &m);
    init_graph(&G, n);
    
    // for(int i = 0; i < m; i++) {
    //     scanf("%d%d", &u, &v);
    //     add_edge(&G, u, v);
    // }


    // 2 
    // add_edge(&G, 1, 2);
    // add_edge(&G, 2, 3);
    // add_edge(&G, 3, 1);
    // add_edge(&G, 2, 4);
    // add_edge(&G, 3, 4);
    // add_edge(&G, 4, 5);
    // add_edge(&G, 5, 3);

    // 3
    add_edge(&G, 1, 2);
    add_edge(&G, 1, 3);
    add_edge(&G, 2, 1);
    add_edge(&G, 2, 8);
    add_edge(&G, 3, 4);
    add_edge(&G, 3, 5);
    add_edge(&G, 4, 2);
    add_edge(&G, 4, 7);
    add_edge(&G, 4, 8);
    add_edge(&G, 5, 3);
    add_edge(&G, 5, 7);
    add_edge(&G, 6, 7);
    add_edge(&G, 7, 6);

    for(int v = 1; v <= n; v++) {
        num[v] = -1;
        on_stack[v] = 0;
    }

    make_null_stack(&S);

    for(int v = 1; v <= n; v++) {
        if(num[v] == -1) {
            // printf("yes");
            strong_connect(&G, v);
        }
    }

    if(count == 1) {
        printf("strong connected");
    } else {
        printf("unconnected");
    }

    return 0;
}