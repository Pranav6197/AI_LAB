#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isSafe(int row, int col, const vector<int>& queens) {
    for (int r = 0; r < row; ++r) {
        int c = queens[r];
        if (c == col || abs(row - r) == abs(col - c))
            return false; // Same column or diagonal
    }
    return true;
}

// CSP Backtracking
bool solveNQueens(int row, int N, vector<int>& queens, vector<vector<int>>& solutions) {
    if (row == N) {
        solutions.push_back(queens);
        return true;
    }

    bool found = false;
    for (int col = 0; col < N; ++col) {
        if (isSafe(row, col, queens)) {
            queens[row] = col;
            found |= solveNQueens(row + 1, N, queens, solutions);
            // No need to undo assignment since it's overwritten in next loop
        }
    }
    return found;
}

// Print a solution
void printSolution(const vector<int>& solution) {
    int N = solution.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << (solution[i] == j ? "Q " : ". ");
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    int N;
    cout << "Enter value of N: ";
    cin >> N;

    vector<int> queens(N, -1);           // queens[row] = col
    vector<vector<int>> solutions;

    if (solveNQueens(0, N, queens, solutions)) {
        cout << "Found " << solutions.size() << " solution(s):\n\n";
        for (const auto& sol : solutions)
            printSolution(sol);
    } else {
        cout << "No solution exists for N = " << N << endl;
    }

    return 0;
}
