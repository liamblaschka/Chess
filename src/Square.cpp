#include "Square.h"
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;

Square::Square(Color colour, int row, int col) {
    this->row = row;
    this->col = col;
    isActivated = false;
    isSelected = false;
    isCheck = false;

    square = RectangleShape(Vector2f(75, 75));
    square.setPosition(Vector2f((col * 75), (row * 75)));
    square.setFillColor(colour);

    bounds = FloatRect(square.getPosition(), Vector2f(75, 75));
}

bool Square::contains(Vector2f point) {
    return bounds.contains(point);
}

void Square::activate(bool isActivated) {
    Color colour = square.getFillColor();
    if (isActivated && !this->isActivated) {
        colour.g += 40;
    } else if (!isActivated && this->isActivated) {
        colour.g -= 40;
    } 
    square.setFillColor(colour);

    this->isActivated = isActivated;
}

void Square::select(bool isSelected) {
    this->isSelected = isSelected;
    if (isSelected) {
        square.setOutlineColor(Color::White);
        square.setOutlineThickness(-4);
    } else if (isCheck) {
        square.setOutlineColor(Color(255, 120, 5));
        square.setOutlineThickness(-4);
    } else {
        square.setOutlineThickness(0);
    }
}

void Square::setCheck(bool isCheck) {
    this->isCheck = isCheck;
    if (isCheck) {
        square.setOutlineColor(Color(255, 120, 5));
        square.setOutlineThickness(-4);
    } else {
        square.setOutlineThickness(0);
    }
}

int Square::getRow() {
    return row;
}

int Square::getCol() {
    return col;
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(square);
}