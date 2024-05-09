#include "Piece.h"
#include "Bishop.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Bishop::Bishop(char colour, int row, int col) : Piece('b', colour, row, col) {
    if (colour == 'w') {
        sprite = Sprite(chessPieces, Rect(240, 60, 60, 60));
    } else {
        sprite = Sprite(chessPieces, Rect(240, 0, 60, 60));
    }
    sprite.setScale(1.2, 1.2);
    sprite.setPosition(position);
}

void Bishop::findMovesHelper(int r, int c, Piece* board[8][8], bool validMoves[8][8], Vector2i direction) {
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

void Bishop::findMoves(Piece* board[8][8], bool validMoves[8][8], bool check) {
    findMovesHelper(row, col, board, validMoves, Vector2i(-1, -1)); // left up
    findMovesHelper(row, col, board, validMoves, Vector2i(1, -1)); // right up
    findMovesHelper(row, col, board, validMoves, Vector2i(-1, 1)); // left down
    findMovesHelper(row, col, board, validMoves, Vector2i(1, 1)); // right down
}