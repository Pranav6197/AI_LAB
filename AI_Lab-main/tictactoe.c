#include <stdio.h>
#include<stdlib.h>

void constBoard(int board[]);
void user1Turn(int board[]);
void user2Turn(int board[]);
int analyzeBoard(int board[]);

int main() {
    int board[9] = {0};

        for (int i = 0; i < 9; i++) {
            if (analyzeBoard(board) != 0) {
                break;
            }
            if (i % 2 == 0) {
                constBoard(board);
                user1Turn(board);
            } else {
                constBoard(board);
                user2Turn(board);
            }
        }


    int x = analyzeBoard(board);
    constBoard(board);
    if (x == 0) {
        printf("Draw!!!\n");
    } else if (x == -1) {
        printf("X Wins!!! Y Lose !!!\n");
    } else {
        printf("X Lose!!! O Wins !!!!\n");
    }
}

void constBoard(int board[]) {
    printf("Current State Of Board : \n\n");
    for (int i = 0; i < 9; i++) {
        if (i > 0 && i % 3 == 0) {
            printf("\n");
        }
        if (board[i] == 0) {
            printf("- ");
        } else if (board[i] == 1) {
            printf("O ");
        } else {
            printf("X ");
        }
    }
    printf("\n\n");
}

void user1Turn(int board[]) {
    printf("Enter X's position from [1...9]: ");
    int pos;
    scanf("%d", &pos);
    if (board[pos - 1] != 0) {
        printf("Wrong Move!!!\n");
        exit(0);
    }
    board[pos - 1] = -1;
}

void user2Turn(int board[]) {
    printf("Enter O's position from [1...9]: ");
    int pos;
    scanf("%d", &pos);
    if (board[pos - 1] != 0) {
        printf("Wrong Move!!!\n");
        exit(0);
    }
    board[pos - 1] = 1;
}

int analyzeBoard(int board[]) {
    // Check rows
    for (int row = 0; row < 3; row++) {
        int index = row * 3;  // Starting index of the row
        if (board[index] != 0 && board[index] == board[index+1] && board[index] == board[index+2]) {
            return board[index];  // Return winner
        }
    }
    
    // Check columns
    for (int col = 0; col < 3; col++) {
        if (board[col] != 0 && board[col] == board[col+3] && board[col] == board[col+6]) {
            return board[col];  // Return winner
        }
    }
    
    // Check diagonal (top-left to bottom-right)
    if (board[0] != 0 && board[0] == board[4] && board[0] == board[8]) {
        return board[0];  // Return winner
    }
    
    // Check diagonal (top-right to bottom-left)
    if (board[2] != 0 && board[2] == board[4] && board[2] == board[6]) {
        return board[2];  // Return winner
    }
    
    // No winner
    return 0;
}
