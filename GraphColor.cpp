#include <iostream>
#include <vector>
using namespace std;

// Function to check if the current color assignment is valid
bool isSafe(int node, int color, vector<vector<int>> &graph, vector<int> &colors) {
    for (int neighbor : graph[node]) {
        if (colors[neighbor] == color)
            return false;
    }
    return true;
}

// Backtracking function to solve the coloring problem
bool solve(int node, vector<vector<int>> &graph, int m, vector<int> &colors) {
    int n = graph.size();
    if (node == n) {
        return true;  // All nodes are assigned colors
    }

    for (int c = 1; c <= m; ++c) {
        if (isSafe(node, c, graph, colors)) {
            colors[node] = c;
            if (solve(node + 1, graph, m, colors))
                return true;
            colors[node] = 0;  // Backtrack
        }
    }
    return false;
}

int main() {
    int V, E, m;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> graph(V);
    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);  // Assuming undirected graph
    }

    cout << "Enter number of colors: ";
    cin >> m;

    vector<int> colors(V, 0);

    if (solve(0, graph, m, colors)) {
        cout << "Coloring possible. Assigned colors:\n";
        for (int i = 0; i < V; ++i) {
            cout << "Vertex " << i << " --> Color " << colors[i] << "\n";
        }
    } else {
        cout << "No valid coloring possible with " << m << " colors.\n";
    }

    return 0;
}
