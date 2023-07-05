#include "GameClass.h"

GameClass::GameClass(int boardSize, int symbolsToWin) : size(boardSize), symbolsNeeded(symbolsToWin) {
    board.resize(size, vector<int>(size, EMPTY));
}

bool GameClass::isEmpty(int row, int col) {
    if (board[row][col] == EMPTY)
        return true;
    return false;
}

bool GameClass::isFull() {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

bool GameClass::isWinner(int player) {
    // Check rows
    for (int row = 0; row < size; row++) {
        int count = 0;
        for (int col = 0; col < size; col++) {
            if (board[row][col] == player) {
                count++;
                if (count == symbolsNeeded) {
                    return true;
                }
            }
            else {
                count = 0;
            }
        }
    }

    // Check columns
    for (int col = 0; col < size; col++) {
        int count = 0;
        for (int row = 0; row < size; row++) {
            if (board[row][col] == player) {
                count++;
                if (count == symbolsNeeded) {
                    return true;
                }
            }
            else {
                count = 0;
            }
        }
    }

    // Check diagonals
    for (int row = 0; row <= size - symbolsNeeded; row++) {
        for (int col = 0; col <= size - symbolsNeeded; col++) {
            bool diag1 = true;
            bool diag2 = true;
            for (int i = 0; i < symbolsNeeded; i++) {
                if (board[row + i][col + i] != player) {
                    diag1 = false;
                }
                if (board[row + i][col + symbolsNeeded - 1 - i] != player) {
                    diag2 = false;
                }
            }
            if (diag1 || diag2) {
                return true;
            }
        }
    }

    return false;
}

bool GameClass::isTerminal() {
    return isFull() || isWinner(PLAYER_X) || isWinner(PLAYER_O);
}

void GameClass::makeMove(int player, Move move) {
    board[move.row][move.col] = player;
}

void GameClass::undoMove(Move move) {
    board[move.row][move.col] = EMPTY;
}

int GameClass::evaluate() {
    if (isWinner(PLAYER_X)) {
        return SCORES[PLAYER_X];
    }
    else if (isWinner(PLAYER_O)) {
        return SCORES[PLAYER_O];
    }
    else {
        return SCORES[EMPTY];
    }
}

int GameClass::minimax(int depth, int player, int alpha, int beta, int maxDepth) {
    if (isWinner(PLAYER_X)) {
        return SCORES[PLAYER_X];
    }
    else if (isWinner(PLAYER_O)) {
        return SCORES[PLAYER_O];
    }
    else if (isFull()) {
        return SCORES[EMPTY];
    }
    else if (depth == maxDepth) {
        return evaluate();
    }

    if (player == PLAYER_X) {
        int maxEval = -1;
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                if (board[row][col] == EMPTY) {
                    Move move{ row, col };
                    makeMove(player, move);
                    int eval = minimax(depth + 1, PLAYER_O, alpha, beta, maxDepth);
                    undoMove(move);
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = 1;
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                if (board[row][col] == EMPTY) {
                    Move move{ row, col };
                    makeMove(player, move);
                    int eval = minimax(depth + 1, PLAYER_X, alpha, beta, maxDepth);
                    undoMove(move);
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return minEval;
    }
}

Move GameClass::getBestMove(int maxDepth) {
    int bestScore = -2;
    Move bestMove;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == EMPTY) {
                Move move{ row, col };
                makeMove(PLAYER_X, move);
                int score = minimax(0, PLAYER_O, -1, 1, maxDepth);
                undoMove(move);
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }
        }
    }
    return bestMove;
}

void GameClass::printBoard() {
    for (int row = size - 1; row >= 0; row--) {
        for (int col = 0; col < size; col++) {
            char symbol;
            switch (board[row][col]) {
            case EMPTY:
                symbol = '-';
                break;
            case PLAYER_X:
                symbol = 'X';
                break;
            case PLAYER_O:
                symbol = 'O';
                break;
            }
            cout << symbol << " ";
        }
        cout << endl;
    }
}
