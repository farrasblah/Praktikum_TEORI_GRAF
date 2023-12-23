#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int N = 8;
int xMove[] = {2, 1, -1, -2, -2, -1, 1, 2};
int yMove[] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isSafe(int x, int y, const vector<vector<int>>& sol);

void printSolution(const vector<vector<int>>& sol);

bool isClosedMove(int x, int y, int start_row, int start_col);

bool solveKTUtil(int x, int y, int movei, vector<vector<int>>& sol,
                 const int xMove[], const int yMove[], int start_row, int start_col);

vector<pair<int, int>> findWarnsdorffMove(int x, int y, const vector<vector<int>>& sol,
                                          const int xMove[], const int yMove[]);

bool findKnightTour(int start_row, int start_col);

int main() {
    int start_row, start_col;
    cout << "Enter the starting position (row and column) from 1 to 8: ";
    cin >> start_row >> start_col;

    // Adjust input to be 0-based
    --start_row;
    --start_col;

    if (start_row < 0 || start_row >= N || start_col < 0 || start_col >= N) {
        cout << "Invalid input. Please enter row and column values between 1 and 8.\n";
        return 1;
    }

    // Example usage:
    findKnightTour(start_row, start_col);

    return 0;
}

bool isSafe(int x, int y, const vector<vector<int>>& sol) {
    return 0 <= x && x < N && 0 <= y && y < N && sol[x][y] == -1;
}

void printSolution(const vector<vector<int>>& sol) {
    for (const auto& row : sol) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

bool isClosedMove(int x, int y, int start_row, int start_col) {
    return (abs(x - start_row) == 2 && abs(y - start_col) == 1) ||
           (abs(x - start_row) == 1 && abs(y - start_col) == 2);
}

bool solveKTUtil(int x, int y, int movei, vector<vector<int>>& sol,
                 const int xMove[], const int yMove[], int start_row, int start_col) {
    if (movei == N * N && isClosedMove(x, y, start_row, start_col)) {
        return true;
    }

    vector<pair<int, int>> next_moves = findWarnsdorffMove(x, y, sol, xMove, yMove);

    for (const auto& move : next_moves) {
        int k = move.second;
        int next_x = x + xMove[k];
        int next_y = y + yMove[k];
        sol[next_x][next_y] = movei;
        if (solveKTUtil(next_x, next_y, movei + 1, sol, xMove, yMove, start_row, start_col)) {
            return true;
        }
        sol[next_x][next_y] = -1;
    }

    return false;
}

vector<pair<int, int>> findWarnsdorffMove(int x, int y, const vector<vector<int>>& sol,
                                          const int xMove[], const int yMove[]) {
    vector<pair<int, int>> next_moves;
    for (int k = 0; k < 8; ++k) {
        int next_x = x + xMove[k];
        int next_y = y + yMove[k];
        if (isSafe(next_x, next_y, sol)) {
            int count = 0;
            for (int i = 0; i < 8; ++i) {
                int new_x = next_x + xMove[i];
                int new_y = next_y + yMove[i];
                if (isSafe(new_x, new_y, sol)) {
                    count += 1;
                }
            }
            next_moves.push_back(make_pair(count, k));
        }
    }

    sort(next_moves.begin(), next_moves.end());
    return next_moves;
}

bool findKnightTour(int start_row, int start_col) {
    vector<vector<int>> sol(N, vector<int>(N, -1));
    sol[start_row][start_col] = 0;

    if (solveKTUtil(start_row, start_col, 1, sol, xMove, yMove, start_row, start_col)) {
        cout << "Knight's Tour found starting from position: (" << start_row + 1 << ", " << start_col + 1 << ")\n";
        printSolution(sol);
        return true;
    } else {
        cout << "Knight's Tour not found for the given starting position.\n";
        return false;
    }
}