//
//  Game.hpp
//  Ultimate Tic Tac Toe
//
//  Created by Olivia Roscoe on 2017-10-02.
//  Copyright © 2017 Olivia Roscoe. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <array>
#include <ComputerPlayer.hpp>

/*******************************************************
 
 Board Layout:
      |     |
   0  |  1  |  2
 _____|_____|____
      |     |
   3  |  4  |  5
 _____|_____|____
      |     |
   6  |  7  |  8
      |     |
 
 *******************************************************/

class Game {
public: Game();
    void run();
    
private:
    void processEvents();
    void render();
    
    // Initial Screen
    void drawStart();
    void endGame(char winner);
    
    // Basic drawing functions
    void drawGrid();
    void drawX(int boxNum, int boardNum);
    void drawO(int boxNum, int boardNum, bool hoverO);
    void drawXWin(int boardNum);
    void drawOWin(int boardNum);
    void drawCWin(int boardNum);
    
    void updateGameBoard(std::vector<char> board, int boardNum);
    char checkWin(std::vector<char> board, int boardNum);
    void gameReset();
    void takeTurn(int boardNum, sf::Vector2i pos);
    int nextValid(int boardNum);
    
    void centerText(std::string message, float height, sf::Color colour, int size);
    void leftText(std::string message, float height, sf::Color colour);
    
    // Convert the board number to a 2d array index eg. 3 becomes [0][1]
    std::pair<int, int> boardToIndex(int board);
    
    // Returns the rectangle for the current Board
    sf::RectangleShape curBoard(sf::Color colour);
    
    
private:
    sf::RenderWindow mWindow;
    sf::RectangleShape mBoard1, mBoard2, mBoard3, mBoard4, mBoard5, mBoard6, mBoard7, mBoard8, mBoard9;
    
    std::vector<std::vector<char>> boardVect;
    std::vector<char> fullBoard = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char turn;
    int currentBoard;
    std::pair<int, int> mostRecentMove;
    int numWon;
    bool gameOver, start, player1X, hoverStart, recentWin, undone, hoverO;
    char winner;
    
};

#endif /* Game_hpp */

