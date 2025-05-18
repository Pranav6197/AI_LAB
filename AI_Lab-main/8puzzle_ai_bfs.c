#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 3
#define MAX_STATES 100000

// Structure to represent a puzzle state
typedef struct {
    int board[SIZE][SIZE];       // 3x3 puzzle board
    int blank_row, blank_col;    // Coordinates of the blank tile (0)
    int moves;                   // Number of moves made so far
    char path[100];              // Path of moves as a string (e.g., "ULDR")
} State;

// Queue for BFS
State queue[MAX_STATES];
int front = 0, rear = 0;

// Visited states stored as strings
char visited[MAX_STATES][SIZE * SIZE + 1];
int visit_count = 0;

// Initial configuration
int initial[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 0, 6},
    {7, 5, 8}
};

// Goal configuration
int goal[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// Converts a 3x3 board to a string (used for visited state checking)
void board_to_string(int board[SIZE][SIZE], char* str) {
    int k = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            str[k++] = board[i][j] + '0';
    str[k] = '\0';
}

// Checks if a board configuration has already been visited
bool is_visited(int board[SIZE][SIZE]) {
    char str[SIZE * SIZE + 1];
    board_to_string(board, str);

    for (int i = 0; i < visit_count; i++)
        if (strcmp(visited[i], str) == 0)
            return true;

    // Not visited: mark as visited
    strcpy(visited[visit_count++], str);
    return false;
}

// Checks if a board matches the goal configuration
bool is_goal(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] != goal[i][j])
                return false;
    return true;
}

// Displays a 3x3 board on the console
void print_board(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            board[i][j] ? printf("%d ", board[i][j]) : printf("  ");
        printf("\n");
    }
    printf("\n");
}

// Breadth-First Search to find the shortest solution
char* solve_puzzle() {
    // Directions for blank tile movement: up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    char mv[] = {'U', 'D', 'L', 'R'};

    // Create initial state
    State start;
    memcpy(start.board, initial, sizeof(initial));
    start.moves = 0;
    start.path[0] = '\0';

    // Locate blank tile in the initial board
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (start.board[i][j] == 0) {
                start.blank_row = i;
                start.blank_col = j;
            }

    // Add initial state to queue and mark visited
    queue[rear++] = start;
    board_to_string(start.board, visited[visit_count++]);

    // BFS main loop
    while (front < rear) {
        State curr = queue[front++];

        // If goal is reached, return the move path
        if (is_goal(curr.board))
            return strdup(curr.path); // dynamically allocate path to return

        // Try moving the blank tile in 4 directions
        for (int i = 0; i < 4; i++) {
            int nr = curr.blank_row + dr[i];
            int nc = curr.blank_col + dc[i];

            // Check if the new position is within bounds
            if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) {
                State next = curr;

                // Perform the move
                next.board[curr.blank_row][curr.blank_col] = next.board[nr][nc];
                next.board[nr][nc] = 0;
                next.blank_row = nr;
                next.blank_col = nc;

                // Update the move path
                next.path[next.moves++] = mv[i];
                next.path[next.moves] = '\0';

                // If not visited, enqueue the new state
                if (!is_visited(next.board))
                    queue[rear++] = next;
            }
        }
    }

    return NULL; // No solution found
}

int main() {
    printf("Initial state:\n");
    print_board(initial);

    printf("Solving...\n");
    char* solution = solve_puzzle();

    if (solution) {
        printf("Solved in %lu moves: %s\n\n", strlen(solution), solution);

        // Recreate the board to display solution step by step
        int curr[SIZE][SIZE];
        int br, bc;
        memcpy(curr, initial, sizeof(initial));

        // Find blank tile
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (curr[i][j] == 0) {
                    br = i;
                    bc = j;
                }

        // Show the board for each move
        print_board(curr);
        for (int i = 0; solution[i]; i++) {
            int nr = br, nc = bc;
            switch (solution[i]) {
                case 'U': nr--; break;
                case 'D': nr++; break;
                case 'L': nc--; break;
                case 'R': nc++; break;
            }

            // Perform the move on the board
            curr[br][bc] = curr[nr][nc];
            curr[nr][nc] = 0;
            br = nr;
            bc = nc;

            printf("Move %d: %c\n", i + 1, solution[i]);
            print_board(curr);
        }
        free(solution); // Free the allocated path string
    } else {
        printf("No solution found.\n");
    }
    return 0;
}
