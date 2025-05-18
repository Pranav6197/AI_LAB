#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int V;
int m;
int color[MAX];
int adj[MAX][MAX];
int adjSize[MAX]; // Keeps track of how many neighbors each vertex has

void printSolution();

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
        return false; // Continue to find more solutions
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            graphColoring(v + 1, m); // Continue without stopping
            color[v] = 0; // Backtrack
        }
    }

    return false;
}

void printSolution() {
    printf("Vertex Color Assignment:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d -> Color %d\n", i, color[i]);
    }
    printf("\n");
}

int main() {
    int E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    // Initialize adjacency list sizes
    for (int i = 0; i < V; i++) {
        adjSize[i] = 0;
    }

    printf("Enter %d edges (u v) pairs (0-based indexing):\n", E);
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        // Add edge u-v and v-u
        adj[u][adjSize[u]++] = v;
        adj[v][adjSize[v]++] = u;
    }

    printf("Enter the number of colors: ");
    scanf("%d", &m);

    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }

    if (!graphColoring(0, m)) {
        printf("All possible colorings are displayed above (if any).\n");
    }

    return 0;
}
