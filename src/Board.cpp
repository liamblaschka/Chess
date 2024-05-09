#include "Board.h"
#include "Square.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

using namespace sf;

void Board::setBoard() {
    // set squares
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Color colour;
            if ((row + col) % 2 == 0) {
                colour = Color(235, 212, 175);
            } else {
                colour = Color(185, 135, 97);
            }

            board[row][col] = Square(colour, row, col);
        }
    }

    // set pieces
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            pieces[row][col] = nullptr;
        }
    }

    // black
    for (int i = 0; i < 8; i++) {
        pieces[1][i] = new Pawn('b', 1, i);
    }
    pieces[0][0] = new Rook('b', 0, 0);
    pieces[0][7] = new Rook('b', 0, 7);
    pieces[0][1] = new Knight('b', 0, 1);
    pieces[0][6] = new Knight('b', 0, 6);
    pieces[0][2] = new Bishop('b', 0, 2);
    pieces[0][5] = new Bishop('b', 0, 5);
    pieces[0][3] = new Queen('b', 0, 3);
    pieces[0][4] = new King('b', 0, 4);
    kings[1] = pieces[0][4];

    // white
    for (int i = 0; i < 8; i++) {
        pieces[6][i] = new Pawn('w', 6, i);
    }
    pieces[7][0] = new Rook('w', 7, 0);
    pieces[7][7] = new Rook('w', 7, 7);
    pieces[7][1] = new Knight('w', 7, 1);
    pieces[7][6] = new Knight('w', 7, 6);
    pieces[7][2] = new Bishop('w', 7, 2);
    pieces[7][5] = new Bishop('w', 7, 5);
    pieces[7][3] = new Queen('w', 7, 3);
    pieces[7][4] = new King('w', 7, 4);
    kings[0] = pieces[7][4];


    // set variables
    selectedPiece = nullptr;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            validMoves[row][col] = false;
        }
    }
    turn = 'w';
    turnKing = kings[0];
    lastMovedPiece = nullptr;
    check = false;
    gameOver = false;
}

void Board::mouseClick(Vector2f point) {
    if (!gameOver) {
        Square square;
        for (int row = 0; row < 8; row ++) {
            for (int col = 0; col < 8; col++) {
                square = board[row][col];
                if (square.contains(point)) {
                    // make move
                    if (selectedPiece != nullptr && validMoves[row][col] == true) {
                        // remove any piece occupying destination
                        if (pieces[row][col] != nullptr) {
                            delete pieces[row][col];
                        }

                        // move piece
                        board[selectedPiece->getRow()][selectedPiece->getCol()].select(false);
                        selectedPiece->makeMove(pieces, row, col);
                        selectedPiece = nullptr;
                        resetValidMoves();

                        // promote pawn
                        if (pieces[row][col]->getType() == 'p' && (row == 0 || row == 7)) {
                            // update window with pawn move
                            window->clear();
                            draw();
                            window->display();

                            Piece* temp = pieces[row][col];
                            char colour = temp->getColour();
                            
                            bool validInput = false;
                            while (!validInput) {
                                std::string choice;
                                std::cout << "Promote pawn (Rook, Knight, Bishop, Queen): ";
                                std::cin >> choice;
                                std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
                                
                                if (choice == "rook") {
                                    pieces[row][col] = new Rook(colour, row, col);
                                    validInput = true;
                                } else if (choice == "knight") {
                                    pieces[row][col] = new Knight(colour, row, col);
                                    validInput = true;
                                } else if (choice == "bishop") {
                                    pieces[row][col] = new Bishop(colour, row, col);
                                    validInput = true;
                                } else if (choice == "queen") {
                                    pieces[row][col] = new Queen(colour, row, col);
                                    validInput = true;
                                }

                                if (!validInput) {
                                    std::cout << "Invalid option." << std::endl;
                                }
                            }

                            delete temp;
                        }


                        // update last moved piece
                        if (lastMovedPiece != nullptr) {
                            lastMovedPiece->lastMoved();
                        }
                        lastMovedPiece = pieces[row][col];

                        alternateTurn();

                        // see if check
                        check = isCheck(turn);

                        // see if checkmate/stalemate/insufficient material
                        int knights[2] = { 0, 0 };
                        int bishops[2] = { 0, 0 };
                        int otherPieces[2] = { 0, 0 };
                        bool mateResult = true;
                        // loop through each piece
                        for (int i = 0; i < 8; i++) {
                            for (int j = 0; j < 8; j++) {
                                Piece* piece = pieces[i][j];
                                if (piece != nullptr) {
                                    if (piece->getColour() == turn) {

                                        // to see if insufficient material
                                        switch (piece->getType()) {
                                            case 'n':
                                                knights[0]++;
                                                break;
                                            case 'b':
                                                bishops[0]++;
                                                break;
                                            case 'k':
                                                break;
                                            default:
                                                otherPieces[0]++;
                                        }


                                        // to see if stalemate/checkmate
                                        // loop through each move piece can make
                                        if (mateResult) {
                                            piece->findMoves(pieces, validMoves, check);
                                            for (int k = 0; k < 8; k++) {
                                                for (int l = 0; l < 8; l++) {
                                                    if (validMoves[k][l]) {
                                                        // if the move can be made (doesnt cause check of own king), it is neither checkmate or stalemate
                                                        if (!tryMove(piece, k, l)) {
                                                            mateResult = false;
                                                            break;
                                                        }
                                                    }
                                                }
                                                if (!mateResult) {
                                                    break;
                                                }
                                            }
                                            resetValidMoves();
                                        }

                                    } else {
                                        switch (piece->getType()) {
                                            case 'n':
                                                knights[1]++;
                                                break;
                                            case 'b':
                                                bishops[1]++;
                                                break;
                                            case 'k':
                                                break;
                                            default:
                                                otherPieces[1]++;
                                        }
                                    }
                                }
                            }
                        }

                        // determine if draw by insufficient material
                        bool insufficientMaterial = false;
                        if (!mateResult && otherPieces[0] == 0 && otherPieces[1] == 0) {
                            if (knights[0] + bishops[0] <= 1 && knights[1] + bishops[1] <= 1)
                            {
                                insufficientMaterial = true;
                            }
                        }

                        // show which king in check
                        if (check || mateResult) {
                            board[turnKing->getRow()][turnKing->getCol()].setCheck(true);
                        }

                        // if game is over
                        if (mateResult) {
                            if (check) {
                                std::string winner;
                                if (lastMovedPiece->getColour() == 'w') {
                                    winner = "White";
                                } else {
                                    winner = "Black";
                                }
                                std::cout << winner << " wins by checkmate." << std::endl;
                            } else { // need draw by  insufficient material, by repetition
                                std::cout << "Draw by stalemate." << std::endl;
                            }
                            gameOver = true;
                        } else if ((otherPieces[0] == 0 && otherPieces[1] == 0)
                                    && ((knights[0] + bishops[0] <= 1 && knights[1] + bishops[1] <= 1)
                                    || ((knights[0] == 2 && knights[1] + bishops[1] == 0) || (knights[1] == 2 && knights[0] + bishops[0] == 0))))
                        {
                            std::cout << "Draw by insufficient material." << std::endl;
                            gameOver = true;
                        } else if (check) {
                            std::cout << "Check." << std::endl;
                        } else {
                            // remove check outline from king
                            int index;
                            if (turn == 'w') {
                                index = 1;
                            } else {
                                index = 0;
                            }
                            board[kings[index]->getPreviousRow()][kings[index]->getPreviousCol()].setCheck(false);
                            board[kings[index]->getRow()][kings[index]->getCol()].setCheck(false);
                        }

                    // select piece
                    } else if (pieces[row][col] != nullptr && pieces[row][col]->getColour() == turn) {
                        if (selectedPiece != nullptr) {
                            board[selectedPiece->getRow()][selectedPiece->getCol()].select(false);
                        }
                        selectedPiece = pieces[row][col];
                        board[row][col].select(true);
                        resetValidMoves();
                        selectedPiece->findMoves(pieces, validMoves, check);
                        for (int i = 0; i < 8; i++) {
                            for (int j = 0; j < 8; j++) {
                                if (validMoves[i][j]) {
                                    if (tryMove(selectedPiece, i, j)) {
                                        validMoves[i][j] = false;
                                    } else {
                                        board[i][j].activate(true);
                                    }
                                }
                            }
                        }

                        // implement castling rules
                        if (selectedPiece->getType() == 'k' && !selectedPiece->getHasMoved()) {
                            // kingside
                            if (validMoves[row][col + 2]) {
                                if (tryMove(selectedPiece, row, col + 1)) {
                                    validMoves[row][col + 2] = false;
                                    board[row][col + 2].activate(false);
                                }
                            }

                            // queenside
                            if (validMoves[row][col - 2]) {
                                if (tryMove(selectedPiece, row, col - 1)) {
                                    validMoves[row][col - 2] = false;
                                    board[row][col - 2].activate(false);
                                }
                            }
                        }
                        
                    } else if (selectedPiece != nullptr) {
                        board[selectedPiece->getRow()][selectedPiece->getCol()].select(false);
                        selectedPiece = nullptr;
                        resetValidMoves();
                    }

                    break;
                }
            }
            if (square.contains(point)) {
                break;
            }
        }
    }
}

void Board::resetValidMoves() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            validMoves[row][col] = false;
            board[row][col].activate(false);
        }
    }
}

bool Board::isCheck(char colour) {
    Piece* playerKing;
    Piece* opponentKing;
    if (colour == 'w') {
        playerKing = kings[0]; // white king
        opponentKing = kings[1]; // black king
    } else {
        playerKing = kings[1]; // black king
        opponentKing = kings[0]; // white king
    }

    bool moves[8][8];
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (pieces[row][col] != nullptr && pieces[row][col]->getColour() != colour) {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        moves[i][j] = false;
                    }
                }

                pieces[row][col]->findMoves(pieces, moves, check);

                if (moves[playerKing->getRow()][playerKing->getCol()]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::alternateTurn() {
    if (turn == 'w') {
        turn = 'b';
        turnKing = kings[1];
    } else {
        turn = 'w';
        turnKing = kings[0];
    }
}

bool Board::tryMove(Piece* piece, int row, int col) {
    bool result;

    // simulate move on board
    int originalRow = piece->getRow();
    int originalCol = piece->getCol();
    Piece* temp = pieces[row][col];
    pieces[row][col] = piece;
    pieces[row][col]->setIndexes(row, col);
    pieces[originalRow][originalCol] = nullptr;

    // see if there is check
    result = isCheck(turn);

    // return board to original state
    pieces[originalRow][originalCol] = pieces[row][col];
    pieces[originalRow][originalCol]->setIndexes(originalRow, originalCol);
    pieces[row][col] = temp;

    return result;
}

void Board::setWindow(sf::RenderWindow& window) {
    this->window = &window;
}

void Board::draw() {
    // draw squares
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            window->draw(board[row][col]);
        }
    }

    // draw pieces
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (pieces[row][col] != nullptr) {
                window->draw(*pieces[row][col]);
            }
        }
    }
}

Board::~Board() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            delete pieces[row][col];
        }
    }
}