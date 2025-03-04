#include <iostream>
#include <iomanip>
#include <limits>
#include "numericalTicTacToe.h"
#include <ctime>

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

// Board3x3 class implementation
Board3x3::Board3x3() {
    this->rows = 3;
    this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

Board3x3::~Board3x3()
{
    for (int i = 0; i < this->rows; ++i) {
        delete [] this->board[i];
    }
    delete [] this->board;
}

bool Board3x3::is_valid(std::vector<int>& validMoves, int symbol, int x, int y) {
    if(board[x][y] == 0)
    {
        for (auto i = validMoves.begin(); i != validMoves.end() ; ++i) {
            if(symbol == *i)
            {
                validMoves.erase(i);
                return true;
            }
        }
    }
    return false;
}

bool Board3x3::update_board(int x, int y, int symbol) {
    if(!(x < 0 || x > this->rows || y < 0 || y > this->columns) &&
            (this->board[x][y] == 0 || symbol == 0))
    {
        if(symbol == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else
        {
            this->n_moves++;
            this->board[x][y] = symbol;
        }
        std::cout << "\x1b[7A";
        return true;
    }
    return false;
}

void Board3x3::display_board() {
    std::cout << std::string(28, '-') << std::endl;
    for (int i = 0; i < this->rows; ++i) {
        std::cout << "| ";
        for (int j = 0; j < this->columns; ++j) {
            std::cout << '(' << i << ',' << j << ')';
            std::cout << std::setw(2) << (this->board[i][j] ? char(this->board[i][j] + '0') : ' ') << "| ";
        }
        std::cout << std::endl;
        std::cout << std::string(28, '-') << std::endl;
    }
}

bool Board3x3::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        if(this->board[i][0] &&  this->board[i][1] && this->board[i][2] &&
                (this->board[i][0] +  this->board[i][1] + this->board[i][2] == 15))
        {
            return true;
        }
    }
    for (int j = 0; j < this->columns; ++j) {
        if(this->board[0][j] &&  this->board[1][j] && this->board[2][j] &&
                (this->board[0][j] +  this->board[1][j] + this->board[2][j] == 15))
        {
            return true;
        }
    }
    if((this->board[0][0] && this->board[1][1] && this->board[2][2]) ||
            (this->board[0][2] && this->board[1][1] && this->board[2][0]))
    {
        if(this->board[0][0] + this->board[1][1] + this->board[2][2] == 15
            || this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)
        {
            return true;
        }
    }
    return false;
}

bool Board3x3::is_draw() {
    return (this->n_moves == 8 && !is_win());
}

bool Board3x3::game_is_over() {
    return is_win() || is_draw();
}
// End Board3x3 class
/**************************************/
// Numerical_Tic_Tac_Toe_Player class implementation

Numerical_Tic_Tac_Toe_Player::Numerical_Tic_Tac_Toe_Player(std::string n, int symbol)
: Player<int>(n,symbol) {
    validMoves.resize(4);
    if(symbol == 2) {
        validMoves[0] = 2;
        validMoves[1] = 4;
        validMoves[2] = 6;
        validMoves[3] = 8;
        evenOrOdd = 'E';
    }
    else
    {
        validMoves[0] = 1;
        validMoves[1] = 3;
        validMoves[2] = 5;
        validMoves[3] = 7;
        evenOrOdd = 'O';
    }
}

Numerical_Tic_Tac_Toe_Player::Numerical_Tic_Tac_Toe_Player(int symbol)
: Player<int>(symbol) {
    validMoves.resize(4);
    if(symbol == 2) {
        validMoves[0] = 2;
        validMoves[1] = 4;
        validMoves[2] = 6;
        validMoves[3] = 8;
        evenOrOdd = 'E';
    }
    else
    {
        validMoves[0] = 1;
        validMoves[1] = 3;
        validMoves[2] = 5;
        validMoves[3] = 7;
        evenOrOdd = 'O';
    }
}

void Numerical_Tic_Tac_Toe_Player::getmove(int &x, int &y) {
    Board3x3* board = dynamic_cast<Board3x3*>(boardPtr);
    do{
        std::cout << "Please enter a your move x (0 to 3) and y (0 to 3) and ";
        std::cout << (evenOrOdd == 'E' ? "Even" : "Odd") << " numbers separated by spaces: ";
        std::cin >> x >> y >> symbol;
        std::cout << "\x1b[1A";
        std::cout << "\x1b[K";
    } while(inputStreamFailing() || !board->is_valid(validMoves, symbol, x, y));
}
// End Numerical_Tic_Tac_Toe_Player class
/**************************************/
// Numerical_Tic_Tac_Toe_Random_Player class implementation
Numerical_Tic_Tac_Toe_Random_Player::Numerical_Tic_Tac_Toe_Random_Player(int symbol)
: RandomPlayer<int>(symbol) {
    validMoves.resize(4);
    if(symbol == 2) {
        validMoves[0] = 2;
        validMoves[1] = 4;
        validMoves[2] = 6;
        validMoves[3] = 8;
        evenOrOdd = 'E';
    }
    else
    {
        validMoves[0] = 1;
        validMoves[1] = 3;
        validMoves[2] = 5;
        validMoves[3] = 7;
        evenOrOdd = 'O';
    }
}


void Numerical_Tic_Tac_Toe_Random_Player::getmove(int &x, int &y) {
    Board3x3* board = dynamic_cast<Board3x3*>(boardPtr);
    std::srand(std::time(nullptr));
    do {
        x = std::rand() % 3;
        y = std::rand() % 3;
        symbol = std::rand() % 9;
    }while(!board->is_valid(validMoves, symbol, x, y));
}
// End Numerical_Tic_Tac_Toe_Random_Player class