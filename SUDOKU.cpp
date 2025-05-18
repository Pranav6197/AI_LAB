#include <iostream>
using namespace std;

const int SIZE = 9;

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

// Check if placing num at (row, col) is valid
bool isValid(int row, int col, int num) {
    for (int x = 0; x < SIZE; ++x) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Backtracking solver
bool solveSudoku() {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku()) return true;
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Print the grid
void printGrid() {
    for (int i = 0; i < SIZE; ++i) {
        if (i % 3 == 0 && i != 0)
            cout << "------+-------+------\n";
        for (int j = 0; j < SIZE; ++j) {
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    cout << "Initial Sudoku Puzzle:\n";
    printGrid();

    if (solveSudoku()) {
        cout << "\nSolved Sudoku Puzzle:\n";
        printGrid();
    } else {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}
