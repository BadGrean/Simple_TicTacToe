#include <iostream>
#include "GameClass.h"

int main() {
    int size, symbolsToWin, maxDepth;
    cout << "Enter the size of the board: ";
    cin >> size;
    cout << "Enter the number of symbols in a row needed to win: ";
    cin >> symbolsToWin;
    cout << "Enter the maximum depth for minmax: ";
    cin >> maxDepth;

    GameClass game(size, symbolsToWin);

    while (!game.isTerminal()) {
        game.printBoard();

        bool flag = true;
        int row, col;
        do
        {
            row = -1, col = -1;
            cout << "Enter the row and column to make a move (index starts from 0): ";
            cin >> row >> col;
            if (row < size && row >= 0 && col >= 0 && col < size)
            {
                flag = !game.isEmpty(row, col);
            }
        } while (flag);

        Move playerMove{ row, col };
        game.makeMove(PLAYER_O, playerMove);

        if (!game.isTerminal()) {
            Move bestMove = game.getBestMove(maxDepth);
            game.makeMove(PLAYER_X, bestMove);
        }
    }

    game.printBoard();

    if (game.isWinner(PLAYER_X)) {
        cout << "You died!" << endl;
    }
    else if (game.isWinner(PLAYER_O)) {
        cout << "You won!" << endl;
    }
    else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}



