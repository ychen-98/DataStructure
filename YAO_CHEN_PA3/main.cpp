// PA3: N Queen Problem
// Yao Chen
// Sep 18, 2023

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/* isQueenConflict is a function to check if the Queen has a conflict in current location
 * it returns True for a conflict or False for safe to place a Queen, no conflict          */

bool isQueenConflict(vector<vector<int>> &board, int row, int col, int N) {

    // 1. check for Queens in the same column of [row][col]
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return true;
        }
    }

    // 2. check for Queens in the right diagonal from the given cell [row][col] to the first row
    for (int i = row, j = col; i >= 0 && j < N; --i, ++j) {
        if (board[i][j] == 1) {
            return true;
        }
    }

    // 3. check for Queens in the left diagonal from the given cell [row][col] to the first row
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 1) {
            return true;
        }
    }

    // If none of the above three conditions are met, there are no conflicts, and it's safe to place the queen
    return false;
}

/* printChessboard is a function to draw chessboard.
 * A graphical interface of the chess board with the queen locations.  */

void printChessboard(const vector<vector<int>> &board) {
    auto N = board.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 1) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

/* solveNQueens is a function to solve the N Queens Problem using stack. */

bool solveNQueens(int N) {
    vector<vector<int>> board(N, vector<int>(N, 0)); // Initialize the N by N chessboard
    stack<int> ColStack;

    int row = 0;
    int col = 0;

    while (row < N) {
        // place a Queen in the current [row]
        while (col < N) {
            if (isQueenConflict(board, row, col, N)) {
                // there is a conflict placing a Queen at this [col] in the current [row]
                // move the next column
                ++col;
            } else {
                // Yay! It's safe to put a Queen at board[row][col].
                board[row][col] = 1;
                // push the current column to stack
                ColStack.push(col);
                // draw chessboard to show the queen location changes
                if (row < N - 1) {
                    printChessboard(board);
                    cout << "Move to next row: " << "Row " << row + 2 << endl;
                }
                // set column back to 0 for next row
                col = 0;
                break;
            }
        }

        /* If no valid column is found to place a Queen in the current [row], backtrack.
         * To backtrack, we throw out the new Queen, popping the stack, reducing filled by 1,
         * and returning to the previous row. At the previous row, we continue shifting the queen RIGHTWARD. */
        if (col == N) {
            if (ColStack.empty()) {
                return false;
            } else {
                cout << "No valid column in Row " << row + 1 << " to place a Queen, backtrack. " << endl
                     << "Return to Row " << row << ", we continue shifting the queen RIGHTWARD." << endl;
                printChessboard(board);
                col = ColStack.top();
                ColStack.pop();
                --row; // Move to [row-1] row
                board[row][col] = 0;
                col++; // Try shifting the queen to the right in the new row
            }
        } else if (row == N - 1) {
            // All queens are placed successfully, a solution is found and print the solution
            printChessboard(board);
            return true;
        } else {
            ++row; // Move to the next row
        }
    }
    return true;
}

int main() {
    int N;
    cout << "Enter the value of N (4-100): ";
    cin >> N;
    if (N < 4 | N > 100) {
        cout << "Invalid input. The value of N is in the range of [4, 100].";
    } else if (solveNQueens(N)) {
        cout << "Solution found!" << endl;
    }
    return 0;
}