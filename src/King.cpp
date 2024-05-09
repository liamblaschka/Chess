#include "Piece.h"
#include "King.h"
#include <SFML/Graphics.hpp>

using namespace sf;

King::King(char colour, int row, int col) : Piece('k', colour, row, col) {
    if (colour == 'w') {
        sprite = Sprite(chessPieces, Rect(60, 60, 60, 60));
    } else {
        sprite = Sprite(chessPieces, Rect(60, 0, 60, 60));
    }
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(position);
}

void King::findMoves(Piece* board[8][8], bool validMoves[8][8], bool check) {
    // top
    if (row - 1 >= 0) {
        // top left
        if (col - 1 >= 0 && (board[row - 1][col - 1] == nullptr || board[row - 1][col - 1]->getColour() != colour)) {
            validMoves[row - 1][col - 1] = true;
        }

        // top middle
        if (board[row - 1][col] == nullptr || board[row - 1][col]->getColour() != colour) {
            validMoves[row - 1][col] = true;
        }

        // top right
        if (col + 1 <= 7 && (board[row - 1][col + 1] == nullptr || board[row - 1][col + 1]->getColour() != colour)) {
            validMoves[row - 1][col + 1] = true;
        }
    }

    // middle left
    if (col - 1 >= 0 && (board[row][col - 1] == nullptr || board[row][col - 1]->getColour() != colour)) {
        validMoves[row][col - 1] = true;
    }

    // middle right
    if (col + 1 <= 7 && (board[row][col + 1] == nullptr || board[row][col + 1]->getColour() != colour)) {
        validMoves[row][col + 1] = true;
    }

    // bottom
    if (row + 1 <= 7) {
        // top left
        if (col - 1 >= 0 && (board[row + 1][col - 1] == nullptr || board[row + 1][col - 1]->getColour() != colour)) {
            validMoves[row + 1][col - 1] = true;
        }

        // top middle
        if (board[row + 1][col] == nullptr || board[row + 1][col]->getColour() != colour) {
            validMoves[row + 1][col] = true;
        }

        // top right
        if (col + 1 <= 7 && (board[row + 1][col + 1] == nullptr || board[row + 1][col + 1]->getColour() != colour)) {
            validMoves[row + 1][col + 1] = true;
        }
    }

    // castle
    if (!hasMoved && !check) {
        // kingside castle
        if (board[row][7] != nullptr && !board[row][7]->getHasMoved() && board[row][col + 1] == nullptr && board[row][col + 2] == nullptr) {
            validMoves[row][col + 2] = true;
        }

        // queenside castle
        if (board[row][0] != nullptr && !board[row][0]->getHasMoved() && board[row][col - 1] == nullptr && board[row][col - 2] == nullptr && board[row][col - 3] == nullptr) {
            validMoves[row][col - 2] = true;
        }
    }
}

void King::makeMove(Piece* board[8][8], int row, int col) {
    // kingside castle
    if (col == this->col + 2) {
        // move rook
        board[row][7]->makeMove(board, row, col - 1);

    // queenside castle
    } else if (col == this->col - 2) {
        // move rook
        board[row][0]->makeMove(board, row, col + 1);
    }

    // move king
    Piece::makeMove(board, row, col);
}