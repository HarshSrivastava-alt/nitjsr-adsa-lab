#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int board[MAX];   // board[i] = column position of queen in row i
int N;

// Function to print the solution
void printSolution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

// Check if placing queen at (row, col) is safe
bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check same column and diagonals
        if (board[i] == col || (i - row) == (board[i] - col) || (i - row) == (col - board[i]))
            return false;
    }
    return true;
}

// Backtracking function
void solveNQueens(int row) {
    if (row == N) {
        printSolution();
        return;
    }
    
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;  // Place queen
            solveNQueens(row + 1);
            // Backtrack (implicitly by trying next column)
        }
    }
}

int main() {
    printf("Enter the value of N (number of queens): ");
    scanf("%d", &N);

    if (N < 1 || N > MAX) {
        printf("Invalid input! Please enter N between 1 and %d.\n", MAX);
        return 1;
    }

    printf("Solutions to %d-Queens problem:\n\n", N);
    solveNQueens(0);

    return 0;
}

Output::
Enter the value of N (number of queens): 4
Solutions to 4-Queens problem:

. Q . . 
. . . Q 
Q . . . 
. . Q . 

. . Q . 
Q . . . 
. . . Q 
. Q . . 
