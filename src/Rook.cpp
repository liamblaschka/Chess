#include "Piece.h"
#include "Rook.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Rook::Rook(char colour, int row, int col) : Piece('r', colour, row, col) {
    if (colour == 'w') {
        sprite = Sprite(chessPieces, Rect(120, 60, 60, 60));
    } else {
        sprite = Sprite(chessPieces, Rect(120, 0, 60, 60));
    }
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(position);
}

void Rook::findMovesHelper(int r, int c, Piece* board[8][8], bool validMoves[8][8], Vector2i direction) {
    r += direction.y;
    c += direction.x;
    if (r < 0 || r > 7 || c < 0 || c > 7 || (board[r][c] != nullptr && colour == board[r][c]->getColour())) {
        return;
    } else {
        validMoves[r][c] = true;
        if (board[r][c] == nullptr) {
            findMovesHelper(r, c, board, validMoves, direction);
        }
    }
}

void Rook::findMoves(Piece* board[8][8], bool validMoves[8][8], bool check) {
    findMovesHelper(row, col, board, validMoves, Vector2i(-1, 0)); // left
    findMovesHelper(row, col, board, validMoves, Vector2i(1, 0)); // right
    findMovesHelper(row, col, board, validMoves, Vector2i(0, -1)); // up
    findMovesHelper(row, col, board, validMoves, Vector2i(0, 1)); // down
}