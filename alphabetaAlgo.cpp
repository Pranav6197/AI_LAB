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

// Minimax with Alpha-Beta Pruning
int minimaxAB(int alpha, int beta, bool isAI) {
    if (checkWin('O')) return +1;
    if (checkWin('X')) return -1;
    if (isDraw())     return  0;

    if (isAI) {
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

// AI chooses the best move using Alpha-Beta
void bestMoveAB() {
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
    cout << "AI placed 'O' at (" << moveRow + 1 << ", " << moveCol + 1 << ")\n";
}

int main() {
    // Initialize board
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';

    cout << "Welcome to Tic Tac Toe (You = X, AI = O)\n";
    printBoard();

    while (true) {
        int row, col;
        // Player move
        cout << "Enter your move (row and column 1-3): ";
        cin >> row >> col;
        row--; col--;

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ') {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[row][col] = 'X';
        printBoard();

        if (checkWin('X')) {
            cout << "You win!\n";
            break;
        }
        if (isDraw()) {
            cout << "It's a draw!\n";
            break;
        }

        // AI move
        bestMoveAB();
        printBoard();

        if (checkWin('O')) {
            cout << "AI wins!\n";
            break;
        }
        if (isDraw()) {
            cout << "It's a draw!\n";
            break;
        }
    }

    cout << "Game Over!\n";
    return 0;
}
