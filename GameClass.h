#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <iostream>
#include <vector>

using namespace std;

// Constants for players
const int EMPTY = 0;
const int PLAYER_X = 1;
const int PLAYER_O = 2;

// Evaluation scores
const int SCORES[3] = { 0, 1, -1 };

struct Move {
    int row;
    int col;
};

class GameClass {
private:
    int size;
    int symbolsNeeded;
    vector<vector<int>> board;

public:
    GameClass(int boardSize, int symbolsToWin);
    bool isEmpty(int row, int col);
    bool isFull();
    bool isWinner(int player);
    bool isTerminal();
    void makeMove(int player, Move move);
    void undoMove(Move move);
    int evaluate();
    int minimax(int depth, int player, int alpha, int beta, int maxDepth);
    Move getBestMove(int maxDepth);
    void printBoard();
};

#endif


