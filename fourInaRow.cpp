#include <iostream>
#include "fourInaRow.h"
#include <iomanip>
#include <limits>
#include <cstdlib>
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

// Board6x7 class implementation
Board6x7::Board6x7() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

bool Board6x7::is_valid_cell(int x, int y) {
    // if the user chooses the last row or chooses a row that has a used row underneath it
    if((x == (this->rows - 1) || this->board[x+1][y] != 0)) {
        return true;
    }
    return false;
}

bool Board6x7::update_board(int x, int y, char symbol) {
    if(!(x < 0 || x > this->rows || y < 0 || y > this->columns)
    && (this->board[x][y] == 0 || symbol == 0) && is_valid_cell(x,y)) {
        if(symbol == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }
        std::cout << "\x1b[13A";
        return true;
    }
    return false;
}

void Board6x7::display_board() {
//    std::system("cls");
    std::cout << std::string(65,'-') << std::endl;
    for (int i = 0; i < this->rows; ++i) {
        std::cout << "| ";
        for (int j = 0; j < this->columns; ++j) {
            std::cout << '(' << i << ',' << j << ')';
            std::cout << std::setw(2) << (this->board[i][j] ? this->board[i][j]: ' ') << " |";
        }
        std::cout << std::endl;
        std::cout << std::string(65,'-') << std::endl;
    }
}

bool Board6x7::is_win() {
    int counter;
    // check vertically
    // fix the rows and search every possible column for a win
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < 4; ++j) {
            counter = 1;
            // a counter to be added for the column to make it easier rather than making a big condition
            for (int k = 1; k < 4; ++k) {
                if(this->board[i][j] == this->board[i][j + k]) {
                    if(this->board[i][j] == 0)
                    {
                        break;
                    }
                    ++counter;
                }
            }
            if(counter == 4) {
                return true;
            }
        }
    }

    // check horizontally
    // fix the columns and search every possible row for a win
    for (int j = 0; j < this->columns; ++j) {
        for (int i = 0; i < 3; ++i) {
            counter = 1;
            // a counter to be added for the column to make it easier rather than making a big condition
            for (int k = 1; k < 4; ++k) {
                if(this->board[i][j] == this->board[i+k][j]) {
                    if(this->board[i][j] == 0)
                    {
                        break;
                    }
                    ++counter;
                }
            }
            if(counter == 4) {
                return true;
            }
        }
    }

    // check the principal diagonal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            counter = 1;
            // a counter to be added for the column to make it easier rather than making a big condition
            for (int k = 1; k < 4; ++k) {
                if(this->board[i][j] == this->board[i+k][j+k]) {
                    if(this->board[i][j] == 0)
                    {
                        break;
                    }
                    ++counter;
                }
                if(counter == 4) {
                    return true;
                }
            }
        }
    }

    //check the secondary diagonal
    for (int i = 0; i < 3; ++i) {
        for (int j = this->columns; j > 2 ; --j) {
            counter = 1;
            // a counter to be added for the column to make it easier rather than making a big condition
            for (int k = 1; k < 4; ++k) {
                if(this->board[i][j] == this->board[i+k][j-k]) {
                    if(this->board[i][j] == 0)
                    {
                        break;
                    }
                    ++counter;
                }
                if(counter == 4) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board6x7::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

bool Board6x7::game_is_over() {
    return is_win() || is_draw();
}

// End Board6x7 class
/*************************************/
// Four_In_A_Row_Player class implementation

Four_In_A_Row_Player::Four_In_A_Row_Player(std::string name, char symbol) : Player<char>(name, symbol) {}
Four_In_A_Row_Player::Four_In_A_Row_Player(char symbol) : Player<char>(symbol) {}

void Four_In_A_Row_Player::getmove(int &x, int &y) {
    do{
        std::cout << "Please enter a your move x (0 to 5) and y (0 to 6) separated by spaces: ";
        std::cin >> x >> y;
    } while(inputStreamFailing());
    std::cout << "\x1b[1A";
    std::cout << "\x1b[K";
}

// End Four_In_A_Row_Player class
/*************************************/

Four_In_A_Row_Random_Player::Four_In_A_Row_Random_Player(char symbol) : RandomPlayer<char>(symbol) {}

void Four_In_A_Row_Random_Player::getmove(int &x, int &y) {
    std::srand(std::time(nullptr));
    x = std::rand() % 6;
    y = std::rand() % 7;
}
