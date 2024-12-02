#include "BoardGame_Classes.h"
#include <iostream>
#include <cctype>
#include <iomanip>
#ifndef PYRAMID_X_O_H
#define PYRAMID_X_O_H
using namespace std;

inline bool inputStreamFailing()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }
    return false;
}

template <typename T>
class PyramidBoard : public Board<T> {
public:
	PyramidBoard();
	bool update_board(int x, int y, T symbol) override;
	bool check_move(int x, int y);
	void display_board() override;
	bool is_win() override;
	bool is_draw() override;
	bool game_is_over() override;
};

template <typename T>
class Pyramid_X_O_Player : public Player<T> {
public:
	Pyramid_X_O_Player(string name, T symbol);
	void getmove(int& x, int& y) override;
};

template <typename T>
class Pyramid_X_O_Random_Player : public RandomPlayer<T> {
public:
	Pyramid_X_O_Random_Player(T symbol);
	void getmove(int& x, int& y) override;
};


//============== IMPLEMENTATION ==============//

//===========Start of Pyramid Board===========//

template <typename T>
PyramidBoard<T>::PyramidBoard() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char* [this->rows];

    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns] {0};
    }

    this->n_moves = 0;
}

template <typename T>
bool PyramidBoard<T>::check_move(int x, int y) {
    //check if the selected move is available within the pyramid's borders
    if (!(x == 0 && (y < 0 || y > 0)) || !(x == 1 && (y < 0 || y > 2))) {
        return true;
    }

    return false;
}

template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol) {
    if (!(x < 0 || x >= this->rows || y < 0 || y > this->columns)
        && (this->board[x][y] == 0 || symbol == 0) && check_move(x, y)) {
        if (symbol == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }

        return true;
    }

    return false;
}

template <typename T>
void PyramidBoard<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {

        if (i == 0) {
            cout << setw(18) << "|(" << i << ',' << 0 << ')';
            cout << setw(2) << this->board[i][0] << " |";;
            cout << endl;
        }
        else if (i == 1) {
            cout << setw(9);
            cout << '|';

            for (int j = 0; j < 3; j++) {
                cout << "(" << i << ',' << j << ')';
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << endl;
        }
        else {
            cout << '|';
            for (int j = 0; j < 5; j++) {
                cout << "(" << i << ',' << j << ')';
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << endl;
        }
    }
}

template <typename T>
bool PyramidBoard<T>::is_win() {
    //Check rows and columns for winners
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[1][0] == this->board[1][1] && this->board[1][1] == this->board[1][2] && this->board[1][0] != 0) ||
        (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != 0) ||
        (this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != 0) ||
        (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != 0)) {
        return true;
    }

    //Check diagonals for winners
    if ((this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][0] != 0) ||
        (this->board[0][0] == this->board[1][2] && this->board[1][2] == this->board[2][4] && this->board[0][0] != 0)) {
        return true;
    }

    return false;
}

template <typename T>
bool PyramidBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();
}


//=========== Implementation of Pyramid_X_O_Player ===========

template <typename T>
Pyramid_X_O_Player<T>::Pyramid_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_X_O_Player<T>::getmove(int& x, int& y) {
    do {
        cout << "Enter your move (row [0-2] and column [0-4]): ";
        cin >> x >> y;
        if (inputStreamFailing() || (x == 0 && (y < 0 || y > 0)) || (x == 1 && (y < 0 || y > 2))) {
            cout << "Invalid input. Try again." << endl;
        }
    } while (inputStreamFailing() || (x == 0 && (y < 0 || y > 0)) || (x == 1 && (y < 0 || y > 2)));
}

//=========== Implementation of Pyramid_X_O_Random_Player ===========

template <typename T>
Pyramid_X_O_Random_Player<T>::Pyramid_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void Pyramid_X_O_Random_Player<T>::getmove(int& x, int& y) {
        x = rand() % 3;
        y = rand() % 5;
}

#endif
