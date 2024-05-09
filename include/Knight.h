#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Knight : public Piece {
    public:
        Knight(char colour, int row, int col);
        void findMoves(Piece* board[8][8], bool validMoves[8][8], bool check) override;
};