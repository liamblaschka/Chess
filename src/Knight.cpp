#include "Piece.h"
#include "Knight.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Knight::Knight(char colour, int row, int col) : Piece('n', colour, row, col) {
    if (colour == 'w') {
        sprite = Sprite(chessPieces, Rect(180, 60, 60, 60));
    } else {
        sprite = Sprite(chessPieces, Rect(180, 0, 60, 60));
    }
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(position);
}

void Knight::findMoves(Piece* board[8][8], bool validMoves[8][8], bool check) {
    // top
    if (row - 2 >= 0) {
        // top left
        if (col - 1 >= 0 && (board[row - 2][col - 1] == nullptr || colour != board[row - 2][col - 1]->getColour())) {
            validMoves[row - 2][col - 1] = true;
        }

        // top right
        if (col + 1 <= 7 && (board[row - 2][col + 1] == nullptr || colour != board[row - 2][col + 1]->getColour())) {
            validMoves[row - 2][col + 1] = true;
        }
    }

    // bottom
    if (row + 2 <= 7) {
        // bottom left
        if (col - 1 >= 0 && (board[row + 2][col - 1] == nullptr || colour != board[row + 2][col - 1]->getColour())) {
            validMoves[row + 2][col - 1] = true;
        }

        // bottom right
        if (col + 1 <= 7 && (board[row + 2][col + 1] == nullptr || colour != board[row + 2][col + 1]->getColour())) {
            validMoves[row + 2][col + 1] = true;
        }
    }

    // left
    if (col - 2 >= 0) {
        // left top
        if (row - 1 >= 0 && (board[row - 1][col - 2] == nullptr || colour != board[row - 1][col - 2]->getColour())) {
            validMoves[row - 1][col - 2] = true;
        }

        // left bottom
        if (row + 1 <= 7 && (board[row + 1][col - 2] == nullptr || colour != board[row + 1][col - 2]->getColour())) {
            validMoves[row + 1][col - 2] = true;
        }
    }

    // right
    if (col + 2 <= 7) {
        // right top
        if (row - 1 >= 0 && (board[row - 1][col + 2] == nullptr || colour != board[row - 1][col + 2]->getColour())) {
            validMoves[row - 1][col + 2] = true;
        }

        // right bottom
        if (row + 1 <= 7 && (board[row + 1][col + 2] == nullptr || colour != board[row + 1][col + 2]->getColour())) {
            validMoves[row + 1][col + 2] = true;
        }
    }
}
