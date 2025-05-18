#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

char board[3][3];

void initializeBoard();
void displayBoard();
bool isValidMove(int row, int col);
bool checkWin(char player);
bool isBoardFull();
void getHumanMove(char player, int *row, int *col);
void getAIMove(char player, int *row, int *col);
int minimax(char player, char currentPlayer, int depth, bool isMaximizing, int alpha, int beta);
int evaluateBoard(char player);

int main() {
    char currentPlayer = 'X';
    int row, col;
    bool gameOver = false;
    char humanPlayer, aiPlayer;
    
    printf("Tic Tac Toe Game with AI (Minimax with Alpha-Beta Pruning)\n");
    printf("Do you want to play as X or O? (X goes first): ");
    char choice;
    scanf(" %c", &choice);
    
    if (choice == 'X' || choice == 'x') {
        humanPlayer = 'X';
        aiPlayer = 'O';
    } else {
        humanPlayer = 'O';
        aiPlayer = 'X';
    }
    
    initializeBoard();
    
    while (!gameOver) {
        displayBoard();
        
        printf("Player %c's turn\n", currentPlayer);
        
        if (currentPlayer == humanPlayer) {
            getHumanMove(currentPlayer, &row, &col);
        } else {
            printf("AI is thinking...\n");
            getAIMove(currentPlayer, &row, &col);
            printf("AI placed at row %d, column %d\n", row, col);
        }
        
        board[row][col] = currentPlayer;
        
        if (checkWin(currentPlayer)) {
            displayBoard();
            if (currentPlayer == humanPlayer) {
                printf("Congratulations! You win!\n");
            } else {
                printf("AI wins! Better luck next time.\n");
            }
            gameOver = true;
        } else if (isBoardFull()) {
            displayBoard();
            printf("It's a draw!\n");
            gameOver = true;
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    
    printf("Game Over\n");
    char playAgain;
    printf("Play again? (y/n): ");
    scanf(" %c", &playAgain);
    
    if (playAgain == 'y' || playAgain == 'Y') {
        main(); 
        return 0;
    }
    
    return 0;
}

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

bool isValidMove(int row, int col) {
    if (row < 0 || row > 2 || col < 0 || col > 2) {
        return false;
    }
    
    return board[row][col] == ' ';
}

bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    
    return false;
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void getHumanMove(char player, int *row, int *col) {
    int validMove = 0;
    
    while (!validMove) {
        printf("Enter row (0-2) and column (0-2) separated by space: ");
        scanf("%d %d", row, col);
        
        if (isValidMove(*row, *col)) {
            validMove = 1;
        } else {
            printf("Invalid move! Try again.\n");
        }
    }
}

int evaluateBoard(char player) {
    char opponent = (player == 'X') ? 'O' : 'X';
    
    if (checkWin(player)) {
        return 10;
    } else if (checkWin(opponent)) {
        return -10;
    } else {
        return 0; 
    }
}

int minimax(char player, char currentPlayer, int depth, bool isMaximizing, int alpha, int beta) {
    char opponent = (player == 'X') ? 'O' : 'X';
    int score = evaluateBoard(player);
    
    if (score == 10) return score - depth; 
    if (score == -10) return score + depth; 
    if (isBoardFull()) return 0; 
    
    if (isMaximizing) {
        int bestScore = INT_MIN;
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player;
                    int currentScore = minimax(player, opponent, depth + 1, false, alpha, beta);
                    board[i][j] = ' ';
                    bestScore = (currentScore > bestScore) ? currentScore : bestScore;
                    
                    alpha = (alpha > bestScore) ? alpha : bestScore;
                    if (beta <= alpha) {
                        break; 
                    }
                }
            }
            
            if (beta <= alpha) {
                break;
            }
        }
        
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = opponent;
                    int currentScore = minimax(player, player, depth + 1, true, alpha, beta);
                    board[i][j] = ' ';
                    bestScore = (currentScore < bestScore) ? currentScore : bestScore;
                    
                    // Alpha-Beta Pruning
                    beta = (beta < bestScore) ? beta : bestScore;
                    if (beta <= alpha) {
                        break; 
                    }
                }
            }
            
            if (beta <= alpha) {
                break;
            }
        }
        
        return bestScore;
    }
}

void getAIMove(char player, int *row, int *col) {
    int bestScore = INT_MIN;
    *row = -1;
    *col = -1;
    
    bool boardEmpty = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                boardEmpty = false;
                break;
            }
        }
        if (!boardEmpty) break;
    }
    
    if (boardEmpty) {
        if (rand() % 2 == 0) {
            *row = 1;
            *col = 1; 
        } else {
            int corner = rand() % 4;
            switch (corner) {
                case 0: *row = 0; *col = 0; break; // Top-left
                case 1: *row = 0; *col = 2; break; // Top-right
                case 2: *row = 2; *col = 0; break; // Bottom-left
                case 3: *row = 2; *col = 2; break; // Bottom-right
            }
        }
        return;
    }
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = player;
                int moveScore = minimax(player, player, 0, false, INT_MIN, INT_MAX);
                board[i][j] = ' ';
                
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    *row = i;
                    *col = j;
                }
            }
        }
    }
    
    if (*row == -1 || *col == -1) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    *row = i;
                    *col = j;
                    return;
                }
            }
        }
    }
}
