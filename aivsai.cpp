#include <iostream>
#include <limits>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

// Print the current board
void printBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---|---|---\n";
    }
    cout << "\n";
}

// Check if a player has won
bool checkWin(char player) {
    for (int i = 0; i < SIZE; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;
    return false;
}

// Check for a draw
bool isDraw() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == ' ')
                return false;
    return true;
}

// Minimax with Alpha-Beta Pruning from O's perspective
// returns +1 if O wins, -1 if X wins, 0 if draw
int minimaxAB(int alpha, int beta, bool isOTurn) {
    if (checkWin('O')) return +1;
    if (checkWin('X')) return -1;
    if (isDraw())     return  0;

    if (isOTurn) {
        int maxEval = -2;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int eval = minimaxAB(alpha, beta, false);
                    board[i][j] = ' ';
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha)
                        return maxEval;  // β cutoff
                }
            }
        }
        return maxEval;
    } else {
        int minEval = +2;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int eval = minimaxAB(alpha, beta, true);
                    board[i][j] = ' ';
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha)
                        return minEval;  // α cutoff
                }
            }
        }
        return minEval;
    }
}

// AI chooses the best move for O (maximizes the score)
void bestMoveO() {
    int bestScore = -2;
    int moveRow = -1, moveCol = -1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimaxAB(-2, +2, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }
    board[moveRow][moveCol] = 'O';
    cout << "O-AI placed at (" << moveRow + 1 << ", " << moveCol + 1 << ")\n";
}

// AI chooses the best move for X (minimizes O’s score, i.e. maximizes X)
void bestMoveX() {
    int bestScore = +2;
    int moveRow = -1, moveCol = -1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                // Next is O’s turn
                int score = minimaxAB(-2, +2, true);
                board[i][j] = ' ';
                if (score < bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }
    board[moveRow][moveCol] = 'X';
    cout << "X-AI placed at (" << moveRow + 1 << ", " << moveCol + 1 << ")\n";
}

int main() {
    // Initialize board
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';

    cout << "Tic Tac Toe: AI vs. AI\n";
    printBoard();

    // O goes first
    bool oTurn = true;
    while (true) {
        if (oTurn) {
            bestMoveO();
        } else {
            bestMoveX();
        }
        printBoard();

        if (checkWin(oTurn ? 'O' : 'X')) {
            cout << (oTurn ? "O-AI wins!\n" : "X-AI wins!\n");
            break;
        }
        if (isDraw()) {
            cout << "It's a draw!\n";
            break;
        }
        oTurn = !oTurn;
    }

    cout << "Game over.\n";
    return 0;
}
