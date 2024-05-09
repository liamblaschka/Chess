#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>

class King : public Piece {
    public:
        King(char colour, int row, int col);
        void findMoves(Piece* board[8][8], bool validMoves[8][8], bool check) override;
        void makeMove(Piece* board[8][8], int row, int col) override;
};