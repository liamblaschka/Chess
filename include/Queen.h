#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Queen : public Piece {
    private:
        void findMovesHelper(int r, int c, Piece* board[8][8], bool validMoves[8][8], sf::Vector2i direction);
    public:
        Queen(char colour, int row, int col);
        void findMoves(Piece* board[8][8], bool validMoves[8][8], bool check) override;
};