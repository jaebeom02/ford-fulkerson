#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_NODES 1000
#define oo 1000000000
int n;  // node 수
int e;  // edge 수
int capacity[MAX_NODES][MAX_NODES]; // 용량 행렬
int flow[MAX_NODES][MAX_NODES];     // 유량 행렬
int color[MAX_NODES]; // bfs에 필요               
int pred[MAX_NODES];  // augmenting path(확장 경로)를 저장할 배열

int min(int x, int y) {
    return x < y ? x : y;
}
int head, tail;
int q[MAX_NODES + 2];

void enqueue(int x) {
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

int dequeue() {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}
int bfs(int start, int target) {
    int u, v;
    for (u = 0; u < n; u++) {
        color[u] = WHITE;
    }
    head = tail = 0;
    enqueue(start);
    pred[start] = -1;
    while (head != tail) {
        u = dequeue();
        // 인접한 모든 흰색 노드 v.
        // 잔여 네트워크의 u에서 v까지의 용량이 양수이면 enqueue v.
        for (v = 0; v < n; v++) {
            if (color[v] == WHITE && capacity[u][v] - flow[u][v] > 0) {
                enqueue(v);
                pred[v] = u;
            }
        }
    }
     // 대상 노드의 색상이 지금 검은색이면 도달했다는 것을 의미합니다.
    return color[target] == BLACK;
}

int max_flow(int source, int sink) {
    int i, j, u;
    // 빈 유량을 초기화합니다.
    int max_flow = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            flow[i][j] = 0;
        }
    }
    // augmenting path(증가 경로)가 있는 동안, 이 경로를 따라 유량을 증가시킵니다.
    while (bfs(source, sink)) {
        // 유량을 증가시킬 수 있는 양을 결정합니다.
        int increment = oo;
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {
            increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
        }
        // 이제 유량을 증가시킵니다.
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {
            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;
        }
        max_flow += increment;
    }
    // 더 이상 경로가 없습니다. 마칩니다.
    return max_flow;
}

void read_input_file() {
    int a, b, c, i, j;
    FILE* input = fopen("data.txt", "r");
    // node, edge 수 읽어줍니다.
    fscanf(input, "%d %d", &n, &e);
    printf("\nnode 갯수 : %d   edge 갯수 : %d", n, e);
    // 빈 용량 행렬 초기화합니다.
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            capacity[i][j] = 0;
        }
    }
    // edge 용량을 읽습니다.
    for (i = 0; i < e; i++) {
        fscanf(input, "%d %d %d", &a, &b, &c);
        capacity[a][b] = c;
        printf("\nA : %d  B : %d  용량 : %d", a, b, c);
    }
    fclose(input);
}

int main() {
    read_input_file();
    printf("\nS와 T값을 입력해라 :\n");
    int s = 0, t = n - 1;
    scanf("%d %d", &s, &t);
    printf("\n최대 유량 : %d\n", max_flow(s, t));
    return 0;
}