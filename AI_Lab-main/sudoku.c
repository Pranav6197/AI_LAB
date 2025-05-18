#include <stdio.h>
#include <stdbool.h>

#define SIZE 9
#define EMPTY 0
#define BOX_SIZE 3

// Print the Sudoku grid
void printGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        if (row % BOX_SIZE == 0 && row != 0)
            printf("------+-------+------\n");
            
        for (int col = 0; col < SIZE; col++) {
            if (col % BOX_SIZE == 0 && col != 0)
                printf("| ");
                
            if (grid[row][col] == EMPTY)
                printf(". ");
            else
                printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

// Check if a number can be placed in a given position
bool isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check row
    for (int x = 0; x < SIZE; x++)
        if (grid[row][x] == num)
            return false;
            
    // Check column
    for (int x = 0; x < SIZE; x++)
        if (grid[x][col] == num)
            return false;
            
    // Check 3x3 box
    int startRow = row - row % BOX_SIZE;
    int startCol = col - col % BOX_SIZE;
    for (int i = 0; i < BOX_SIZE; i++)
        for (int j = 0; j < BOX_SIZE; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;
                
    return true;
}

// Find an empty cell
bool findEmptyCell(int grid[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (grid[*row][*col] == EMPTY)
                return true;
    return false;
}

// Solve Sudoku using backtracking
bool solveSudoku(int grid[SIZE][SIZE]) {
    int row, col;
    
    // If no empty cell, puzzle is solved
    if (!findEmptyCell(grid, &row, &col))
        return true;
        
    // Try digits 1-9
    for (int num = 1; num <= SIZE; num++) {
        // Check if safe to place
        if (isSafe(grid, row, col, num)) {
            // Place the number
            grid[row][col] = num;
            
            // Recursively solve rest of puzzle
            if (solveSudoku(grid))
                return true;
                
            // If placing num doesn't lead to solution, backtrack
            grid[row][col] = EMPTY;
        }
    }
    // Trigger backtracking
    return false;
}

int main() {
    // Sample puzzle (0 represents empty cells)
    int grid[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    printf("Original Sudoku puzzle:\n");
    printGrid(grid);
    
    if (solveSudoku(grid)) {
        printf("\nSolved Sudoku puzzle:\n");
        printGrid(grid);
    } else {
        printf("\nNo solution exists.\n");
    }
    
    return 0;
}
