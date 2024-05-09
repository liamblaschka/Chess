#include "Game.h"
#include "Board.h"
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;

Game::Game() {
    window.create(VideoMode(600, 600), "Chess", Style::Titlebar| Style::Close);
    window.setVerticalSyncEnabled(true);

    board.setWindow(window);
    board.setBoard();
}

void Game::run() {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                // window closed
                case Event::Closed:
                    window.close();
                    break;

                // mouse clicked
                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Left) {
                        board.mouseClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    break;

                default:
                    break;
            }
        }
        window.clear();
        board.draw();
        window.display();
    }
}