#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

class Piece : public sf::Drawable {
    protected:
        char type;
        char colour;
        sf::Texture chessPieces;
        sf::Sprite sprite;
        sf::Vector2f position;
        int row;
        int col;
        int previousRow;
        int previousCol;
        bool isFirstMove;
        bool hasMoved;
    public:
        Piece();
        Piece(char type, char colour, int row, int col);
        char getType();
        char getColour();
        virtual void findMoves(Piece* board[8][8], bool validMoves[8][8], bool check) = 0;
        virtual void makeMove(Piece* board[8][8], int row, int col);
        int getRow();
        int getCol();
        int getPreviousRow();
        int getPreviousCol();
        void setIndexes(int row, int col);
        bool getIsFirstMove();
        bool getHasMoved();
        void lastMoved();
        void setPosition(int row, int col);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};