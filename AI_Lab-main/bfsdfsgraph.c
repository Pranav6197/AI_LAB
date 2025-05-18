#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjMatrix[MAX][MAX];
int visited[MAX];

void BFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;
    while (front < rear) {
        int node = queue[front++];
        printf("%d ", node);
        for (int i = 0; i < MAX; i++) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

void DFS(int start) {
    int stack[MAX], top = -1;
    stack[++top] = start;
    while (top >= 0) {
        int node = stack[top--];
        if (!visited[node]) {
            visited[node] = 1;
            printf("%d ", node);
        }
        for (int i = 0; i < MAX; i++) {
            if (adjMatrix[node][i] == 1 && !visited[i]) {
                stack[++top] = i;
            }
        }
    }
}

int main() {
    int n, m, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        adjMatrix[u][v] = adjMatrix[v][u] = 1;
    }
    for (int i = 0; i < n; i++) visited[i] = 0;
    printf("BFS starting from node 0: ");
    BFS(0);
    for (int i = 0; i < n; i++) visited[i] = 0;
    printf("\nDFS starting from node 0: ");
    DFS(0);
    return 0;
}