#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int V;
int color[MAX];
int adj[MAX][MAX];
int adjSize[MAX]; // adjacency list size

bool foundSolution = false;

void printSolution() {
    foundSolution = true;
    printf("Vertex Color Assignment:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d -> Color %d\n", i, color[i]);
    }
    printf("\n");
}

bool isSafe(int v, int c) {
    for (int i = 0; i < adjSize[v]; i++) {
        int neighbor = adj[v][i];
        if (color[neighbor] == c) {
            return false;
        }
    }
    return true;
}

bool graphColoring(int v, int m) {
    if (v == V) {
        printSolution();
        return false;  // continue searching for all solutions
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            graphColoring(v + 1, m);
            color[v] = 0;  // backtrack
        }
    }
    return false;
}

bool canColorWithM(int v, int m) {
    if (v == V) return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            if (canColorWithM(v + 1, m)) return true;
            color[v] = 0;
        }
    }
    return false;
}

int findMinColors() {
    int m;
    for (m = 1; m <= V; m++) {
        for (int i = 0; i < V; i++) color[i] = 0;
        if (canColorWithM(0, m)) {
            return m;
        }
    }
    return V; // worst case
}

int main() {
    int E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < V; i++) {
        adjSize[i] = 0;
    }

    printf("Enter %d edges (u v):\n", E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][adjSize[u]++] = v;
        adj[v][adjSize[v]++] = u;
    }

    int minColors = findMinColors();
    printf("\nMinimum number of colors required: %d\n", minColors);
    printf("\nAll possible valid colorings using %d colors:\n\n", minColors);

    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }

    foundSolution = false;
    graphColoring(0, minColors);

    if (!foundSolution) {
        printf("No valid colorings found.\n");
    }

    return 0;
}
