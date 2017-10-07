//
//  Game.cpp
//  Ultimate Tic Tac Toe
//
//  Created by Olivia Roscoe on 2017-10-02.
//  Copyright © 2017 Olivia Roscoe. All rights reserved.
//

#include "Game.hpp"
#include "ResourcePath.hpp"


Game::Game():mBoard1(), mBoard2(), mBoard3(), mBoard4(), mBoard5(),
    mBoard6(), mBoard7(), mBoard8(), mBoard9() {
        
        
    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    mWindow.create(sf::VideoMode(1500, 1500, desktop.bitsPerPixel), "Ultimate Tic Tac Toe");
        
    mWindow.setFramerateLimit(60);
    
    mBoard1.setSize(sf::Vector2f(500, 500));
    mBoard1.setFillColor(sf::Color(153, 230, 255, 255));
    mBoard1.setPosition(0, 0);

    mBoard2.setSize(sf::Vector2f(500, 500));
    mBoard2.setFillColor(sf::Color(153, 230, 255, 255));
    mBoard2.setPosition(500, 0);
    
    mBoard3.setSize(sf::Vector2f(500, 500));
    mBoard3.setFillColor(sf::Color(153, 230, 255, 255));
    mBoard3.setPosition(1000, 0);
    
    mBoard4.setSize(sf::Vector2f(500, 500));
    mBoard4.setFillColor(sf::Color(153, 230, 255, 255));
    mBoard4.setPosition(0, 500);
    
    mBoard5.setSize(sf::Vector2f(500, 500));
    mBoard5.setFillColor(sf::Color(153, 230, 255, 255));
    mBoard5.setPosition(500, 500);
    
    mBoard6.setSize(sf::Vector2f(500, 500));
    mBoard6.setFillColor(sf::Color(153, 230, 255, 255));
    mBoard6.setPosition(1000, 500);
    
    mBoard7.setSize(sf::Vector2f(500, 500));
    mBoard7.setFillColor(sf::Color(153, 230, 255, 255));
    mBoard7.setPosition(0, 1000);
    
    mBoard8.setSize(sf::Vector2f(500, 500));
    mBoard8.setFillColor(sf::Color(153, 230, 255, 255));
    mBoard8.setPosition(500, 1000);
    
    mBoard9.setSize(sf::Vector2f(500, 500));
    mBoard9.setFillColor(sf::Color(153, 230, 255, 255));
    mBoard9.setPosition(1000, 1000);
    
    for (int i = 0; i < 9; i++){
        std::vector<char> init (9, ' ');
        boardVect.push_back(init);
    }
    
    turn = 'x';
    currentBoard = 0;
    numWon = 0;
    gameOver = false;
    start = true;
    player1X = true;
        recentWin = false;
}

void Game::run(){
    // Start the game loop
    
    
    while (mWindow.isOpen()) {
        
        processEvents();
        render();

    }
}

void Game::processEvents(){
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        
        
        // Close window: exit
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            mWindow.close();
        }
        
        // R pressed: reset
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            gameReset();
        }
        /*
        bool controlPressed;
        // is control pressed
        if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl)){
            controlPressed = true;
        }
        
        // was control released
        if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::LControl || event.key.code == sf::Keyboard::RControl)){
            controlPressed = false;
        }
        */
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z && !start && undone == false){
            undone = true;
            if (recentWin){
                recentWin = false;
                fullBoard[mostRecentMove.first] = ' ';
                
            }
            
            boardVect[mostRecentMove.first][mostRecentMove.second] = ' ';
            curBoard(sf::Color(153, 230, 255, 255));
            currentBoard = mostRecentMove.first;
            
            if (turn == 'x'){
                turn = 'o';
            } else {
                turn = 'x';
            }
            
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // get the position that it was clicked
            sf::Vector2i pos = sf::Mouse::getPosition(mWindow);
            
            if (!gameOver){
                takeTurn(currentBoard, pos);
                undone = false;
            }
            
            if (start && (pos.x >= 283 && pos.x <= 1220 && pos.y >= 1314 && pos.y <= 1414)){
                if (player1X){
                    turn = 'x';
                } else {
                    turn = 'o';
                }
                start = false;
            }
        }
        
        if (event.type == sf::Event::MouseMoved && start){
            sf::Vector2i pos = sf::Mouse::getPosition(mWindow);

            if ((pos.x >= 165 && pos.x <= 392 && pos.y >= 630 && pos.y <= 782) || (pos.x >= 1108 && pos.x <= 1334 && pos.y >= 1090 && pos.y <= 1242)) {
                // Player 1 X or Player 2 O
                player1X = true;
                hoverStart = false;
            } else if ((pos.x >= 1108 && pos.x <= 1334 && pos.y >= 640 && pos.y <= 792) || (pos.x >= 165 && pos.x <= 392 && pos.y >= 1080 && pos.y <= 1232)) {
                // Player 1 O or Player 2 X
                player1X = false;
                hoverStart = false;
            } else if (pos.x >= 283 && pos.x <= 1220 && pos.y >= 1314 && pos.y <= 1414){
                hoverStart = true;
            } else {
                hoverStart = false;
            }
            
        }
        
        if (event.type == sf::Event::MouseMoved){
            sf::Vector2i pos = sf::Mouse::getPosition(mWindow);
            
            
        }
    }
    
}


void Game::render(){
    // Clear screen
    mWindow.clear();
    
    if (start) {
        drawStart();
    } else {
        curBoard(sf::Color(179, 179, 255));
        // Draw the first board
        mWindow.draw(mBoard1);
        mWindow.draw(mBoard2);
        mWindow.draw(mBoard3);
        mWindow.draw(mBoard4);
        mWindow.draw(mBoard5);
        mWindow.draw(mBoard6);
        mWindow.draw(mBoard7);
        mWindow.draw(mBoard8);
        mWindow.draw(mBoard9);
        
        drawGrid();
        
        for (int i = 0; i < 9; i++){
            if (fullBoard[i] == ' '){
                updateGameBoard(boardVect[i], i);
                checkWin(boardVect[i], i);
            } else if (fullBoard[i] == 'x'){
                updateGameBoard(boardVect[i], i);
                drawXWin(i);
            } else if (fullBoard[i] == 'o'){
                updateGameBoard(boardVect[i], i);
                drawOWin(i);
            } else if (fullBoard[i] == 'c'){
                updateGameBoard(boardVect[i], i);
                drawCWin(i);
            }
        }
        
        if (gameOver){
            endGame(winner);
        }
    }
    // Update the window
    mWindow.display();
    
}

void Game::updateGameBoard(std::vector<char> board, int boardNum){

    for (int i = 0; i < 9; i++){
            if (boardVect[boardNum][i] == 'x'){
                drawX(i+1, boardNum);
            } else if (boardVect[boardNum][i] == 'o'){
                drawO(i+1, boardNum, false);
            }
        }

}

void Game::drawGrid(){
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            sf::RectangleShape line1(sf::Vector2f(460, 5));
            line1.setPosition(i*500 + 20, j*500 + 160);
            sf::RectangleShape line2(sf::Vector2f(460, 5));
            line2.setPosition(i*500 + 20, j*500 + 320);
            sf::RectangleShape line3(sf::Vector2f(460, 5));
            line3.setPosition(j*500 + 160, i*500 + 20);
            line3.rotate(90);
            sf::RectangleShape line4(sf::Vector2f(460, 5));
            line4.setPosition(j*500 + 320, i*500 + 20);
            line4.rotate(90);
            
            mWindow.draw(line1);
            mWindow.draw(line2);
            mWindow.draw(line3);
            mWindow.draw(line4);
        }
    }
    
    // Big game grid
    sf::RectangleShape line1(sf::Vector2f(1450, 10));
    line1.setPosition(20, 495);
    line1.setFillColor(sf::Color(191, 191, 191, 255));
    sf::RectangleShape line2(sf::Vector2f(1450, 10));
    line2.setPosition(20, 995);
    line2.setFillColor(sf::Color(191, 191, 191, 255));
    sf::RectangleShape line3(sf::Vector2f(1450, 10));
    line3.setPosition(505, 20);
    line3.rotate(90);
    line3.setFillColor(sf::Color(191, 191, 191, 255));
    sf::RectangleShape line4(sf::Vector2f(1450, 10));
    line4.setPosition(1005,20);
    line4.rotate(90);
    line4.setFillColor(sf::Color(191, 191, 191, 255));
    
    mWindow.draw(line1);
    mWindow.draw(line2);
    mWindow.draw(line3);
    mWindow.draw(line4);
}


void Game::drawX(int boxNum, int boardNum){
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Playtime.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text text('X', font, 200);
    
    text.setFillColor(sf::Color(117, 117, 163, 255));
    
    std::pair<int, int> index = boardToIndex(boardNum);
    
    // height = 114
    // width = 111
    sf::FloatRect bounds = text.getLocalBounds();
    
    switch (boxNum) {
        case 1:
            text.setPosition(index.first*500 + 20, index.second*500 + 20-bounds.height/2);
            break;
        case 2:
            text.setPosition(index.first*500 + 180, index.second*500 + 20-bounds.height/2);
            break;
        case 3:
            text.setPosition(index.first*500 + 340, index.second*500 + 20-bounds.height/2);
            break;
        case 4:
            text.setPosition(index.first*500 + 20, index.second*500 + 180-bounds.height/2);
            break;
        case 5:
            text.setPosition(index.first*500 + 180, index.second*500 + 180-bounds.height/2);
            break;
        case 6:
            text.setPosition(index.first*500 + 340, index.second*500 + 180-bounds.height/2);
            break;
        case 7:
            text.setPosition(index.first*500 + 20, index.second*500 + 340-bounds.height/2);
            break;
        case 8:
            text.setPosition(index.first*500 + 180, index.second*500 + 340-bounds.height/2);
            break;
        case 9:
            text.setPosition(index.first*500 + 340, index.second*500 + 340-bounds.height/2);
            break;
        default:
            break;
    }

    mWindow.draw(text);
}

void Game::drawO(int boxNum, int boardNum, bool hoverO){
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Playtime.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text text("O", font, 200);
    text.setFillColor(sf::Color(117, 117, 163, 255));
    sf::FloatRect bounds = text.getLocalBounds();
    
    std::pair<int, int> index = boardToIndex(boardNum);
    
    switch (boxNum) {
        case 1:
            text.setPosition(index.first*500 + 15, index.second*500 + 15-bounds.height/2);
            break;
        case 2:
            text.setPosition(index.first*500 + 175, index.second*500 + 15-bounds.height/2);
            break;
        case 3:
            text.setPosition(index.first*500 + 335, index.second*500 + 15-bounds.height/2);
            break;
        case 4:
            text.setPosition(index.first*500 + 15, index.second*500 + 175-bounds.height/2);
            break;
        case 5:
            text.setPosition(index.first*500 + 175, index.second*500 + 175-bounds.height/2);
            break;
        case 6:
            text.setPosition(index.first*500 + 335, index.second*500 + 175-bounds.height/2);
            break;
        case 7:
            text.setPosition(index.first*500 + 15, index.second*500 + 335-bounds.height/2);
            break;
        case 8:
            text.setPosition(index.first*500 + 175, index.second*500 + 335-bounds.height/2);
            break;
        case 9:
            text.setPosition(index.first*500 + 335, index.second*500 + 335-bounds.height/2);
            break;
        default:
            break;
    }
    
    
    mWindow.draw(text);
}

char Game::checkWin(std::vector<char> board, int boardNum){
    char win = 'u';

    // top row
    if (board[0] == board[1] && board[1] == board[2] && board[0] != ' ') {
        win = board[0];
    }// middle row
    else if (board[3] == board[4] && board[4] == board[5] && board[3] != ' ') {
        win = board[3];
    }// bottom row
    else if (board[6] == board[7] && board[7] == board[8] && board[6] != ' ') {
        win = board[6];
    }// left column
    else if (board[0] == board[3] && board[3] == board[6] && board[0] != ' ') {
        win = board[0];
    }// middle column
    else if (board[1] == board[4] && board[4] == board[7] && board[1] != ' ') {
        win = board[1];
    }// right column
    else if (board[2] == board[5] && board[5] == board[8] && board[2] != ' ') {
        win = board[2];
    }// diagonal 1
    else if (board[0] == board[4] && board[4] == board[8] && board[0] != ' ') {
        win = board[0];
    }// diagonal 2
    else if (board[2] == board[4] && board[4] == board[6] && board[2] != ' ') {
        win = board[2];
    } else if (board[0] != ' ' && board[1] != ' ' && board[2] != ' ' && board[3] != ' '
               && board[4] != ' ' && board[5] != ' ' && board[6] != ' ' && board[7] != ' '
               && board[8] != ' ') {
        win = 'c';
    }
    // if win is u, then it is unknown who won
    // if win is c, then it's a cats game
    // otherwise win indicates x or o based on who won
    if (win != 'u'){
        //printf("%c wins!\n", win);
        if (boardNum == 10){
            gameOver = true;
            winner = win;
        } else {
            fullBoard[boardNum] = win;
            recentWin = true;
            numWon++;
        }
    } else {
        recentWin = false;
    }
    
    return win;
}

void Game::endGame(char winner){
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Playtime.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text text("Game over", font, 200);
    text.setPosition(160,500);
    
    std::string whoWon = " ";
    
    sf::Text text2(whoWon, font, 200);
    text2.setPosition(300,700);
    
    if (winner == 'c'){
        whoWon = "Cat's game";
        text2.setPosition(150, 700);
    } else if (winner == 'x'){
        whoWon = "X's won";
    } else {
        whoWon = "O's won";
    }
    

    text2.setString(whoWon);
    
    
    mWindow.draw(text);
    mWindow.draw(text2);

}

void Game::gameReset(){
    boardVect.clear();
    
    std::vector<char> reset(9, ' ');
    
    for (int i = 0; i < 9; i++){
        boardVect.push_back(reset);
        fullBoard[i] = ' ';
    }
    gameOver = false;
    curBoard(sf::Color(153, 230, 255, 255));
    currentBoard = 0;
    
    start = true;
    
}


void Game::takeTurn(int boardNum, sf::Vector2i pos){

    // get the size of the window
    sf::Vector2u windowSize = mWindow.getSize();
    int boxWidth = windowSize.x/3;
    int boxHeight = windowSize.y/3;
    
    bool taken = false;
    int startx, endx, starty, endy;
    startx = (boardNum%3)*boxWidth;
    endx =  startx+boxWidth;
    
    if (boardNum < 3){
        starty = 0;
    } else if (boardNum < 6){
        starty = boxHeight;
    } else {
        starty = 2*boxHeight;
    }
    
    endy = starty+boxHeight;
    
    boxWidth = boxWidth/3;
    boxHeight = boxHeight/3;
    
    if (pos.x >= startx && pos.y >= starty &&
        pos.y <= endy && pos.x <= endx){
    
    
        int offset = boardNum + 1;
        if (pos.x < (boxWidth + startx) && pos.y < (boxHeight+starty)){
            // box [0][0]
            if (boardVect[boardNum][0] == ' '){
                boardVect[boardNum][0] = turn;
                mostRecentMove = std::make_pair(boardNum, 0);
                curBoard(sf::Color(153, 230, 255, 255));
                currentBoard = nextValid(0);
                taken = true;
            }
        } else if (pos.x < (2*boxWidth + startx) && pos.y < (boxHeight + starty)){
            // box [0][1]
            if (boardVect[boardNum][1] == ' '){
                boardVect[boardNum][1] = turn;
                mostRecentMove = std::make_pair(boardNum, 1);
                curBoard(sf::Color(153, 230, 255, 255));
                currentBoard = nextValid(1);
                taken = true;
            }
        } else if (pos.x < (3*boxWidth + startx) && pos.y < (boxHeight + starty)) {
            // box [0][2]
            if (boardVect[boardNum][2] == ' '){
                boardVect[boardNum][2] = turn;
                mostRecentMove = std::make_pair(boardNum, 2);
                curBoard(sf::Color(153, 230, 255, 255));
                currentBoard = nextValid(2);
                taken = true;
            }
        } else if (pos.x < (boxWidth + startx) && pos.y < (2*boxHeight + starty)) {
            // box [1][0]
            if (boardVect[boardNum][3] == ' '){
                boardVect[boardNum][3] = turn;
                mostRecentMove = std::make_pair(boardNum, 3);
                curBoard(sf::Color(153, 230, 255, 255));
                currentBoard = nextValid(3);
                taken = true;
            }
        } else if (pos.x < (2*boxWidth + startx) && pos.y < (2*boxHeight + starty)) {
            // box [1][1]
            if (boardVect[boardNum][4] == ' '){
                boardVect[boardNum][4] = turn;
                mostRecentMove = std::make_pair(boardNum, 4);
                curBoard(sf::Color(153, 230, 255, 255));
                currentBoard = nextValid(4);
                taken = true;
            }
        } else if (pos.x < (3*boxWidth + startx) && pos.y < (2*boxHeight + starty)) {
            // box [1][2]
            if (boardVect[boardNum][5] == ' '){
                boardVect[boardNum][5] = turn;
                mostRecentMove = std::make_pair(boardNum, 5);
                curBoard(sf::Color(153, 230, 255, 255));
                currentBoard = nextValid(5);
                taken = true;
            }
        } else if (pos.x < (boxWidth + startx) && pos.y < (3*boxHeight + starty)) {
            // box [2][0]
            if (boardVect[boardNum][6] == ' '){
                boardVect[boardNum][6] = turn;
                mostRecentMove = std::make_pair(boardNum, 6);
                curBoard(sf::Color(153, 230, 255, 255));
                currentBoard = nextValid(6);
                taken = true;
            }
        } else if (pos.x < (2*boxWidth + startx) && pos.y < (3*boxHeight + starty)) {
            // box [2][2]
            if (boardVect[boardNum][7] == ' '){
                boardVect[boardNum][7] = turn;
                mostRecentMove = std::make_pair(boardNum, 7);
                curBoard(sf::Color(153, 230, 255, 255));
                currentBoard = nextValid(7);
                taken = true;
            }
        } else if (pos.x < (3*boxWidth + startx) && pos.y < (3*boxHeight + starty)) {
            // box [2][2]
            if (boardVect[boardNum][8] == ' '){
                boardVect[boardNum][8] = turn;
                mostRecentMove = std::make_pair(boardNum, 8);
                curBoard(sf::Color(153, 230, 255, 255));
                currentBoard = nextValid(8);
                taken = true;
            }
        }
        
        if (taken) {
            if (turn == 'x'){
                turn = 'o';
            } else {
                turn = 'x';
            }
        }
    }
    
    checkWin(boardVect[boardNum], boardNum);
    if (numWon > 2) {
        checkWin(fullBoard, 10);
    }
    currentBoard = nextValid(currentBoard);
}

std::pair<int, int> Game::boardToIndex(int board){

    switch (board) {
        case 0:
            return std::make_pair(0, 0);
            break;
        case 1:
            return std::make_pair(1, 0);
            break;
        case 2:
            return std::make_pair(2, 0);
            break;
        case 3:
            return std::make_pair(0, 1);
            break;
        case 4:
            return std::make_pair(1, 1);
            break;
        case 5:
            return std::make_pair(2, 1);
            break;
        case 6:
            return std::make_pair(0, 2);
            break;
        case 7:
            return std::make_pair(1, 2);
            break;
        case 8:
            return std::make_pair(2, 2);
            break;
            
        default:
            return std::make_pair(0, 0);
            break;
    }
    
}

sf::RectangleShape Game::curBoard(sf::Color colour){
    sf::RectangleShape result;
    switch (currentBoard) {
        case 0:
            mBoard1.setFillColor(colour);
            result = mBoard1;
            break;
        case 1:
            mBoard2.setFillColor(colour);
            result = mBoard2;
            break;
        case 2:
            mBoard3.setFillColor(colour);
            result = mBoard3;
            break;
        case 3:
            mBoard4.setFillColor(colour);
            result = mBoard4;
            break;
        case 4:
            mBoard5.setFillColor(colour);
            result = mBoard5;
            break;
        case 5:
            mBoard6.setFillColor(colour);
            result = mBoard6;
            break;
        case 6:
            mBoard7.setFillColor(colour);
            result = mBoard7;
            break;
        case 7:
            mBoard8.setFillColor(colour);
            result = mBoard8;
            break;
        case 8:
            mBoard9.setFillColor(colour);
            result = mBoard9;
            break;
            
        default:
            break;
    }
    
    return result;
}

void Game::drawStart(){
    sf::RectangleShape startScreen;
    startScreen.setSize(sf::Vector2f(1500, 1500));
    startScreen.setFillColor(sf::Color(230, 255, 247, 255));
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Playtime.ttf")) {
        return EXIT_FAILURE;
    }
    
    mWindow.draw(startScreen);
    centerText("Ultimate", 0, sf::Color(255, 255, 255, 255), 150);
    centerText("Tic Tac Toe", 150, sf::Color(255, 255, 255, 255), 150);
    
    leftText("Player One", 450, sf::Color(0, 153, 153, 255));
    centerText("X    or    O", 600, sf::Color(0, 153, 153, 255), 150);
    
    leftText("Player Two", 900, sf::Color(0, 153, 153, 255));
    centerText("X    or    O", 1050, sf::Color(0, 153, 153, 255), 150);

    sf::CircleShape ellipse;
    ellipse.setScale(3, 2);
    ellipse.setRadius(33);
    ellipse.setOutlineColor(sf::Color::Red);
    ellipse.setOutlineThickness(5);
    ellipse.setFillColor(sf::Color::Transparent);
    
    if (player1X){
        // player 1 x
        ellipse.setPosition(180, 640);
        mWindow.draw(ellipse);
        
        // player 2 o
        ellipse.setPosition(1123, 1100);
        mWindow.draw(ellipse);
        
    } else {
        // player 2 x
        ellipse.setPosition(180, 1090);
        mWindow.draw(ellipse);
        
        // player 1 o
        ellipse.setPosition(1123, 650);
        mWindow.draw(ellipse);
        
    }
    
    if (!hoverStart){
        centerText("click here to start", 1300, sf::Color::Red, 80);
    } else {
        centerText("click here to start", 1300, sf::Color(0, 153, 153, 255), 80);
    }
}

void Game::centerText(std::string message, float height, sf::Color colour, int size){
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Playtime.ttf")) {
        return EXIT_FAILURE;
    }
    
    
    sf::Text text(message, font, size);
    
    sf::FloatRect bounds = text.getLocalBounds();
    
    
    text.setFillColor(colour);
    text.setOutlineColor(sf::Color(0 ,0 ,0,255));
    text.setOutlineThickness(10);
    
    text.setPosition(750-bounds.width/2, 20 + height);
    
    sf::FloatRect bounds2 = text.getGlobalBounds();
    //printf("Bounds for %s are left: %f, top: %f, width: %f, height %f\n",
      //     message.c_str(), bounds2.left, bounds2.top, bounds2.width, bounds2.height);
    
    mWindow.draw(text);

}

void Game::leftText(std::string message, float height, sf::Color colour){
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Playtime.ttf")) {
        return EXIT_FAILURE;
    }
    
    
    sf::Text text(message, font, 150);
    
    text.setOutlineColor(colour);
    text.setOutlineThickness(10);
    
    text.setPosition(40, 20 + height);
    
    mWindow.draw(text);
}

void Game::drawXWin(int boardNum){
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Playtime.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text text("X", font, 800);
    text.setFillColor(sf::Color(117, 117, 163, 150));
    //text.setPosition(5,-220);
    
    std::pair<int, int> index = boardToIndex(boardNum);
    sf::FloatRect bounds = text.getLocalBounds();

    
    text.setPosition(index.first*500 + 5, index.second*500 + 15-bounds.height/2);


    
    mWindow.draw(text);
    
}

void Game::drawOWin(int boardNum){
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Playtime.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text text("O", font, 700);
    text.setFillColor(sf::Color(117, 117, 163, 150));
    text.setPosition(5,-220);
    
    std::pair<int, int> index = boardToIndex(boardNum);
    sf::FloatRect bounds = text.getLocalBounds();
    
    
    text.setPosition(index.first*500 + 10, index.second*500 + 25-bounds.height/2);
    
    mWindow.draw(text);
    
}

void Game::drawCWin(int boardNum){
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "Playtime.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text text("C", font, 700);
    text.setFillColor(sf::Color(117, 117, 163, 150));
    text.setPosition(5,-220);
    
    std::pair<int, int> index = boardToIndex(boardNum);
    sf::FloatRect bounds = text.getLocalBounds();
    
    
    text.setPosition(index.first*500 + 40, index.second*500 + 60-bounds.height/2);
    
    mWindow.draw(text);

}


int Game::nextValid(int boardNum){
    int count = 0;
    if (fullBoard[boardNum] == ' '){
        return boardNum;
    }
    
    while (fullBoard[boardNum] != ' ' && count < 9){
        if (boardNum < 8){
            boardNum++;
        } else {
            boardNum = 0;
        }
        count++;
    }
    
    if (count == 9){
        printf("All squares taken");
        gameOver = true;
    }
    return boardNum;

}
