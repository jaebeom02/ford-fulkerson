#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_NODES 1000
#define oo 1000000000
int n;  // node ��
int e;  // edge ��
int capacity[MAX_NODES][MAX_NODES]; // �뷮 ���
int flow[MAX_NODES][MAX_NODES];     // ���� ���
int color[MAX_NODES]; // bfs�� �ʿ�               
int pred[MAX_NODES];  // augmenting path(Ȯ�� ���)�� ������ �迭

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
        // ������ ��� ��� ��� v.
        // �ܿ� ��Ʈ��ũ�� u���� v������ �뷮�� ����̸� enqueue v.
        for (v = 0; v < n; v++) {
            if (color[v] == WHITE && capacity[u][v] - flow[u][v] > 0) {
                enqueue(v);
                pred[v] = u;
            }
        }
    }
     // ��� ����� ������ ���� �������̸� �����ߴٴ� ���� �ǹ��մϴ�.
    return color[target] == BLACK;
}

int max_flow(int source, int sink) {
    int i, j, u;
    // �� ������ �ʱ�ȭ�մϴ�.
    int max_flow = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            flow[i][j] = 0;
        }
    }
    // augmenting path(���� ���)�� �ִ� ����, �� ��θ� ���� ������ ������ŵ�ϴ�.
    while (bfs(source, sink)) {
        // ������ ������ų �� �ִ� ���� �����մϴ�.
        int increment = oo;
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {
            increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
        }
        // ���� ������ ������ŵ�ϴ�.
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {
            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;
        }
        max_flow += increment;
    }
    // �� �̻� ��ΰ� �����ϴ�. ��Ĩ�ϴ�.
    return max_flow;
}

void read_input_file() {
    int a, b, c, i, j;
    FILE* input = fopen("data.txt", "r");
    // node, edge �� �о��ݴϴ�.
    fscanf(input, "%d %d", &n, &e);
    printf("\nnode ���� : %d   edge ���� : %d", n, e);
    // �� �뷮 ��� �ʱ�ȭ�մϴ�.
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            capacity[i][j] = 0;
        }
    }
    // edge �뷮�� �н��ϴ�.
    for (i = 0; i < e; i++) {
        fscanf(input, "%d %d %d", &a, &b, &c);
        capacity[a][b] = c;
        printf("\nA : %d  B : %d  �뷮 : %d", a, b, c);
    }
    fclose(input);
}

int main() {
    read_input_file();
    printf("\nS�� T���� �Է��ض� :\n");
    int s = 0, t = n - 1;
    scanf("%d %d", &s, &t);
    printf("\n�ִ� ���� : %d\n", max_flow(s, t));
    return 0;
}