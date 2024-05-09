#pragma once
#include "Board.h"
#include <SFML/Graphics.hpp>

class Game {
    private:
        sf::RenderWindow window;
        Board board;
    public:
        Game();
        void run();
};