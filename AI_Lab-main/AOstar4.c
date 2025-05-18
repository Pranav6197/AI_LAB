#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CHILDREN 10
#define INF INT_MAX

typedef enum { OR_NODE, AND_NODE } NodeType;

typedef struct Node {
    int id;
    NodeType type;
    int heuristic;
    int solved;
    int cost;
    int num_children;
    struct Node* children[MAX_CHILDREN];
    int weights[MAX_CHILDREN];
    int best_child;  // Index of best child for OR nodes
} Node;

Node* create_node(int id, NodeType type, int heuristic) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = id;
    node->type = type;
    node->heuristic = heuristic;
    node->solved = 0;
    node->cost = heuristic;
    node->num_children = 0;
    node->best_child = -1;
    return node;
}

void add_child(Node* parent, Node* child, int weight) {
    if (parent->num_children < MAX_CHILDREN) {
        parent->children[parent->num_children] = child;
        parent->weights[parent->num_children] = weight;
        parent->num_children++;
    }
}

// Update node cost and solved status
void update_node(Node* node) {
    if (node->num_children == 0) {
        node->solved = 1;
        return;
    }

    if (node->type == OR_NODE) {
        int min_cost = INF;
        node->solved = 0;
        
        for (int i = 0; i < node->num_children; i++) {
            int child_cost = node->weights[i] + node->children[i]->cost;
            if (child_cost < min_cost) {
                min_cost = child_cost;
                node->best_child = i;
                node->solved = node->children[i]->solved;
            }
        }
        node->cost = min_cost;
    } 
    else { // AND_NODE
        int total_cost = 0;
        node->solved = 1;
        
        for (int i = 0; i < node->num_children; i++) {
            total_cost += node->weights[i] + node->children[i]->cost;
            if (!node->children[i]->solved) {
                node->solved = 0;
            }
        }
        node->cost = total_cost;
    }
}

int ao_star(Node* root) {
    if (root->num_children == 0) {
        root->solved = 1;
        return root->cost;
    }
    
    int changed;
    do {
        changed = 0;
        
        // Process all unsolved non-leaf nodes in a bottom-up manner
        for (int i = 0; i < root->num_children; i++) {
            if (!root->children[i]->solved) {
                int old_cost = root->children[i]->cost;
                ao_star(root->children[i]);
                if (old_cost != root->children[i]->cost) {
                    changed = 1;
                }
            }
        }
        
        // Update the root node
        int old_cost = root->cost;
        update_node(root);
        if (old_cost != root->cost) {
            changed = 1;
        }
    } while (!root->solved && changed);
    
    return root->cost;
}

void print_solution(Node* node) {
    if (!node) return;
    
    printf("Node %d (Cost: %d, Type: %s, Solved: %s)\n", 
           node->id, node->cost,
           node->type == OR_NODE ? "OR" : "AND", 
           node->solved ? "Yes" : "No");
    
    if (node->type == OR_NODE && node->best_child >= 0) {
        printf("  Best child -> ");
        print_solution(node->children[node->best_child]);
    } 
    else if (node->type == AND_NODE) {
        for (int i = 0; i < node->num_children; i++) {
            print_solution(node->children[i]);
        }
    }
}

int main() {
    // Create the graph nodes
    Node* n1 = create_node(1, OR_NODE, 5);
    Node* n2 = create_node(2, AND_NODE, 3);
    Node* n3 = create_node(3, OR_NODE, 4);
    Node* n4 = create_node(4, OR_NODE, 2);
    Node* n5 = create_node(5, OR_NODE, 6);
    Node* n6 = create_node(6, OR_NODE, 1);

    // Adding children with weights
    add_child(n1, n2, 2);
    add_child(n1, n3, 3);
    add_child(n2, n4, 1);
    add_child(n2, n5, 4);
    add_child(n3, n6, 2);

    // Run AO* algorithm
    int cost = ao_star(n1);

    // Print results
    printf("Minimum cost solution graph has cost: %d\n", cost);
    printf("Solution graph nodes:\n");
    print_solution(n1);

    return 0;
}