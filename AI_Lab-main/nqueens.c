#include <stdio.h>
#define N 5
int solutionCount = 0;

void printSolution(int board[N][N]) {
    printf("Solution %d:\n", solutionCount);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%c ", board[i][j] ? 'Q' : '.');
        printf("\n");
    }
    printf("\n");
}

int isSafe(int board[N][N], int row, int col) {
    // Check column above (no need to check below as we fill row by row from top)
    for (int i = 0; i < row; i++)
        if (board[i][col]) return 0;
        
    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return 0;
        
    // Check upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j]) return 0;
        
    return 1;
}

int solveNQueens(int board[N][N], int row) {
    // If all rows are filled, we have a solution
    if (row >= N) {
        solutionCount++;
        printSolution(board);
        return solutionCount >= 3 ? 1 : 0;  // Stop after 3 solutions
    }
    
    // Try placing a queen in each column of the current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;  // Place the queen
            
            // Recursively place queens in the next row
            if (solveNQueens(board, row + 1))
                return 1;  // If we've found enough solutions, stop
                
            board[row][col] = 0;  // Backtrack: remove the queen
        }
    }
    
    return 0;  // No solution found
}

void nQueens() {
    int board[N][N] = {0};
    solveNQueens(board, 0);  // Start with row 0
    
    if (solutionCount == 0)
        printf("No solution exists.\n");
}

int main() {
    nQueens();
    return 0;
}
