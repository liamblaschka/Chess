#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

using namespace sf;

Pawn::Pawn(char colour, int row, int col) : Piece('p', colour, row, col) {
    hasMoved = false;

    if (colour == 'w') {
        direction = -1;
        sprite = Sprite(chessPieces, Rect(300, 60, 60, 60));
    } else {
        direction = 1;
        sprite = Sprite(chessPieces, Rect(300, 0, 60, 60));
    }
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(position);
}

void Pawn::findMoves(Piece* board[8][8], bool validMoves[8][8], bool check) {
    // one space forward
    if (board[row + direction][col] == nullptr) {
        validMoves[row + direction][col] = true;

        // two spaces forward
        if (!hasMoved && board[row + (2 * direction)][col] == nullptr) {
            validMoves[row + (2 * direction)][col] = true;
        }
    }

    // attack left or en passant left
    if (col - 1 >= 0) {
        Piece* attackedPiece = board[row + direction][col - 1];
        Piece* enPassantPiece = board[row][col - 1];
        if ((attackedPiece != nullptr && colour != attackedPiece->getColour()) ||
            (enPassantPiece != nullptr && enPassantPiece->getType() == 'p' && enPassantPiece->getColour() != colour
            && enPassantPiece->getIsFirstMove() && (enPassantPiece->getRow() == 3 || enPassantPiece->getRow() == 4)))
        {
            validMoves[row + direction][col - 1] = true;
        }
    }

    // attack right or en passant right
    if (col + 1 <= 7) {
        Piece* attackedPiece = board[row + direction][col + 1];
        Piece* enPassantPiece = board[row][col + 1];
        if ((attackedPiece != nullptr && colour != attackedPiece->getColour()) ||
            (enPassantPiece != nullptr && enPassantPiece->getType() == 'p' && enPassantPiece->getColour() != colour
            && enPassantPiece->getIsFirstMove() && (enPassantPiece->getRow() == 3 || enPassantPiece->getRow() == 4)))
        {
            validMoves[row + direction][col + 1] = true;
        }
    }
}

void Pawn::makeMove(Piece* board[8][8], int row, int col) {
    // if attacking
    if (this->col != col) {
        // check if en passant
        Piece* piece = board[this->row][col];
        if (piece != nullptr && piece->getType() == 'p' && piece->getColour() != colour && piece->getIsFirstMove()
            && (piece->getRow() == 3 || piece->getRow() == 4))
        {
            delete piece;
            board[this->row][col] = nullptr;
        }
    }

    Piece::makeMove(board, row, col);
}
