#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 5 

int graph[N][N] = {
    {0, 10, 3, 0, 0},
    {0, 0, 1, 2, 0},
    {0, 4, 0, 8, 2},
    {0, 0, 0, 0, 7},
    {0, 0, 0, 9, 0}
};

int heuristic[N] = {7, 6, 2, 1, 0};  

int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < N; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void aStar(int start, int goal) {
    int g[N], f[N], visited[N] = {0};

    for (int i = 0; i < N; i++) {
        g[i] = INT_MAX;
        f[i] = INT_MAX;
    }

    g[start] = 0;
    f[start] = heuristic[start];

    while (1) {
        int current = minDistance(f, visited);
        if (current == -1 || current == goal) break;

        visited[current] = 1;

        for (int i = 0; i < N; i++) {
            if (graph[current][i] && !visited[i]) {
                int tempG = g[current] + graph[current][i];

                if (tempG < g[i]) {
                    g[i] = tempG;
                    f[i] = g[i] + heuristic[i];
                }
            }
        }
    }

    printf("A* Path Cost: %d\n", g[goal]);
}

int main() {
    int start = 0, goal = 4;
    aStar(start, goal);
    return 0;
}
