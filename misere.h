
#ifndef MISERE_H
#define MISERE_H

#include "BoardGame_Classes.h"

template <typename T>
class misere_board: public Board<T> {
private:
    bool win;
public:
    misere_board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class misere_Player : public Player<T> {
public:
    misere_Player (string name, T symbol,Board<T>* bptr);
    void getmove(int& x, int& y) ;

};

template <typename T>
class misere_Random_Player : public RandomPlayer<T>{
public:
    misere_Random_Player (T symbol,Board<T>* bptr);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for misere_board
template <typename T>
misere_board<T>::misere_board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    this->win = false;
}

template <typename T>
bool misere_board<T>::update_board(int x, int y, T symbol) {
    if(this->win) return true;
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns)
    && (this->board[x][y] == 0 || symbol == 0)) {
        if (symbol == 0){
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

// Display the board and the pieces on it
template <typename T>
void misere_board<T>::display_board() {
    cout << "   ";
    for (int i = 0; i < this->columns; ++i) {
        cout << setw(2) << left << i + 1 << '|';
    }
    cout <<"\n   " << string(9,'-') << '\n';
    for (int i = 0; i < this->rows; ++i) {
        cout << setw(2) << left << i + 1 << '|';
        for (int j = 0; j < this->columns; ++j) {
            if(this->board[i][j] !=0) cout << setw(2) << left << this->board[i][j] << '|';
            else cout << "  |";
        }
        cout << '\n';
        cout <<"   " <<string(9,'-') << '\n';
    }
}

// Returns true if there is any winner
template <typename T>
bool misere_board<T>::is_win() {
    // Check rows and columns
    if(win) return true;
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            win = true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        win = true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool misere_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool misere_board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for misere_Player
template <typename T>
misere_Player<T>::misere_Player(string name, T symbol,Board<T>* bptr) : Player<T>(name, symbol) {
    this->setBoard(bptr);
}
template <typename T>
void misere_Player<T>::getmove(int& x, int& y) {
    if(this->boardPtr->is_win()) return;
    string choice = "";
    cout << "please enter the row of your choice(1-3): ";
    getline(cin >> ws, choice);
    while (choice.size() != 1 || !isdigit(choice[0])) {
        cout << "please enter a number that is between(1-3): ";
        getline(cin >> ws, choice);
    }
    x = stoi(choice);
    cout << "please enter the column of your choice(1-3): ";
    getline(cin >> ws, choice);
    while (choice.size() != 1 || !isdigit(choice[0])) {
        cout << "please enter a number that is between(1-3): ";
        getline(cin >> ws, choice);
    }
    y = stoi(choice);
    --x;--y;
}

// Constructor for misere_Random_Player
template <typename T>
misere_Random_Player<T>::misere_Random_Player(T symbol,Board<T>* bptr) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    this->setBoard(bptr);
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void misere_Random_Player<T>::getmove(int& x, int& y) {
    if(this->boardPtr->is_win()) return;
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //MISERE_H


