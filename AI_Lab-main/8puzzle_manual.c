#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int puzzle[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 0, 6},
    {7, 5, 8}
};

void displayPuzzle() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (puzzle[i][j] == 0)
                printf("   ");
            else
                printf(" %d ", puzzle[i][j]);
        }
        printf("\n");
    }
}

int isSolved() {
    int count = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // For the last position, expect 0 (blank)
            if (i == SIZE-1 && j == SIZE-1) {
                if (puzzle[i][j] != 0)
                    return 0;
            }
            // For all other positions, check sequential order
            else if (puzzle[i][j] != count)
                return 0;
            count++;
        }
    }
    return 1;
}

void moveTile(char move) {
    int i, j, ni, nj;
    
    // Locate the blank tile (0)
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (puzzle[i][j] == 0) {
                goto found;
            }
        }
    }

found:
    ni = i;
    nj = j;

    // Note: Movement is reversed - we move the blank tile, not the number
    if (move == 'w') ni--;       // Move blank up
    else if (move == 's') ni++;  // Move blank down
    else if (move == 'a') nj--;  // Move blank left
    else if (move == 'd') nj++;  // Move blank right

    // Check if the move is valid
    if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE) {
        // Swap the blank with the adjacent tile
        puzzle[i][j] = puzzle[ni][nj];
        puzzle[ni][nj] = 0;
    } else {
        printf("Invalid move!\n");
    }
}

int main() {
    char move;
    printf("Use W A S D to move tiles. Goal: 1-8 in order with blank at bottom-right.\n");
    
    while (!isSolved()) {
        displayPuzzle();
        printf("Move (w/a/s/d): ");
        scanf(" %c", &move);
        moveTile(move);
    }
    
    printf("Puzzle Solved!\n");
    displayPuzzle();
    return 0;
}