#include "Piece.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Piece::Piece(char type, char colour, int row, int col) {
    this->type = type;
    this->colour = colour;
    this->row = row;
    this->col = col;
    previousRow = row;
    previousCol = col;
    hasMoved = false;
    isFirstMove = false;

    setPosition(row, col);

    chessPieces.loadFromFile("../assets/ChessPieces.png");
    chessPieces.setSmooth(true);
}

Piece::Piece() : Piece('e', ' ', -1, -1) {}

char Piece::getType() {
    return type;
}

char Piece::getColour() {
    return colour;
}

void Piece::makeMove(Piece* board[8][8], int row, int col) {
    // move piece in board
    board[row][col] = this;
    board[this->row][this->col] = nullptr;

    // set new position
    previousRow = this->row;
    previousCol = this->col;
    this->row = row;
    this->col = col;
    setPosition(row, col);

    if (!hasMoved) {
        hasMoved = true;
        isFirstMove = true;
    } else if (isFirstMove) {
        isFirstMove = false;
    }
}

int Piece::getRow() {
    return row;
}

int Piece::getCol() {
    return col;
}

int Piece::getPreviousRow() {
    return previousRow;
}

int Piece::getPreviousCol() {
    return previousCol;
}

void Piece::setIndexes(int row, int col) {
    this->row = row;
    this->col = col;
}

bool Piece::getIsFirstMove() {
    return isFirstMove;
}

bool Piece::getHasMoved() {
    return hasMoved;
}

void Piece::lastMoved() {
    if (isFirstMove) {
        isFirstMove = false;
    }
}

void Piece::setPosition(int row, int col) {
    position = Vector2f(col * 75, row * 75);
    sprite.setPosition(position);
}

void Piece::draw(sf::RenderTarget& target, RenderStates states) const {
    target.draw(sprite);
}
