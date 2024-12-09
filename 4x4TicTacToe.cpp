#include "4x4TicTacToe.h"
#include <iomanip>
#include <iostream>
#include <limits>

inline bool inputStreamFailing()
{
    if(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return true;
    }
    return false;
}

// Board4x4 class implementation
Board4x4::Board4x4() {
    this->rows = 4;
    this->columns = 4;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->board[0][1] = this->board[0][3] = this->board[3][0] = this->board[3][2] = 'X';
    this->board[0][0] = this->board[0][2] = this->board[3][1] = this->board[3][3] = 'O';
    this->n_moves = 0;
}

void Board4x4::display_board() {
    std::cout << std::string(32,'-') << std::endl;
    for (int i = 0; i < this->rows; ++i) {
        std::cout << "| ";
        for (int j = 0; j < this->columns; ++j) {
            std::cout << '(' << i << ',' << j << ')';
            std::cout << std::setw(2) << (this->board[i][j] ? this->board[i][j]: ' ') << " |";
        }
        std::cout << std::endl;
        std::cout << std::string(32,'-') << std::endl;
    }
}

bool Board4x4::update_board(int x, int y, char symbol) {
    if(!(x < 0 || x > this->rows || y < 0 || y > this->columns)
       && (this->board[x][y] == 0 || symbol == 0))
    {
        if(symbol == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = symbol;
            this->board[oldX][oldY] = 0;
        }
        return true;
    }
    return false;
}

bool Board4x4::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        if(this->board[i][0] ==  this->board[i][1] && this->board[i][1] == this->board[i][2])
        {
            return true;
        }
    }
    for (int j = 0; j < this->columns; ++j) {
        if(this->board[0][j] &&  this->board[1][j] && this->board[1][j] == this->board[2][j] )
        {
            return true;
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if(this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2])
            {
                return true;
            }
        }
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = this->columns-1; j > 1; --j) {
            if(this->board[i][j] == this->board[i+1][j-1] && this->board[i+1][j-1] == this->board[i+2][j-2])
            {
                return true;
            }
        }
    }
    return false;
}

bool Board4x4::is_valid_cell(int newX, int newY, int oldX, int oldY, char symbol)
{
    if(newX == oldX - 1 || newX == oldX + 1)
    {
        if(newY == oldY + 1 || newY == oldY - 1)
        {
            return false;
        }
    }
    if(newX > oldX + 1 || newX < oldX - 1 || newY > oldY + 1 || newY < oldY - 1)
    {
        return false;
    }
    if(board[newX][newY] != symbol)
    {
        return false;
    }
    return true;
}

void Board4x4::setOldX(int x) {
    oldX = x;
}
void Board4x4::setOldY(int y) {
    oldY = y;
}

bool Board4x4::is_draw() {
    // check the conditions of draw again (the number of moves)
    return (this->n_moves == 42 && !is_win());
}

bool Board4x4::game_is_over() {
    return is_win() || is_draw();
}
// End Board4x4 class

// Player4x4 class implementation

Player4x4::Player4x4(std::string n, char symbol) : Player(n, symbol){}
Player4x4::Player4x4(char symbol) : Player(symbol){}

void Player4x4::getmove(int &x, int &y) {
    int oldX, oldY;
    Board4x4* board4X4 = dynamic_cast<Board4x4*>(boardPtr);
    do {
        std::cout << "Enter the Token Position as x (0 to 3) and y (0 to 3) separated by spaces: ";
        std::cin >> oldX >> oldY;
        std::cout << "Enter the New Position as x (0 to 3) and y (0 to 3) separated by spaces: ";
        std::cin >> x >> y;

    } while(inputStreamFailing() || !(board4X4->is_valid_cell(x, y, oldX, oldY, symbol)));
    board4X4->setOldX(oldX);
    board4X4->setOldY(oldY);
}

// End Player4x4 class
// Random_Player4x4 class implementation

Random_Player4x4::Random_Player4x4(char symbol) : RandomPlayer(symbol){}

void Random_Player4x4::getmove(int &x, int &y) {
    int oldX, oldY;
    Board4x4* board4X4 = dynamic_cast<Board4x4*>(boardPtr);
    do {
        std::srand(std::time(nullptr));
        oldX = std::rand() % 4;
        oldY = std::rand() % 4;
        x = std::rand() % 4;
        y = std::rand() % 4;


    } while(!(board4X4->is_valid_cell(x, y, oldX, oldY, symbol)));
    board4X4->setOldX(oldX);
    board4X4->setOldY(oldY);
}
// End Random_Player4x4 class