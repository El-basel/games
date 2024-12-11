#ifndef GAMES_ULTIMATEXO_H
#define GAMES_ULTIMATEXO_H
#include "BoardGame_Classes.h"
#include <vector>
#include <set>
template<typename T>
class ultimate_board : public Board<T>{
private:
    //this shows the status of each board
    T** status;
    set<int>played;
public:
    ultimate_board();
    //checks win on the status board
    bool is_win() override;
    //checks draw on the status board
    bool is_draw() override;
    bool update_board(int, int, T) override;
    //displays the main board
    void display() override;
    bool game_is_over() override;
    void display_status();
    int board_finder(int&,int&);
    //checks if there is a win on the given indices subboard
    bool check_win(int&,int&,T);
    //checks if there is a draw on the given indices subboard
    bool check_draw(int&,int&,T);
};

template<typename T>
class ultimate_Player: public Player<T>{
public:
    ultimate_Player(string,T);
    void getmove(int&,int&) override;
    //checks if the given string is a valid postive number
    bool isvalid(const string&);
};

template<typename T>
class ultimate_Random: public RandomPlayer<T>{
public:
    ultimate_Random();
    void getmove(int&,int&) override;
    bool isvalid(const string&);
};


//--------------------------------------- IMPLEMENTATION
#include <string>
template<typename T>
ultimate_board<T>::ultimate_board() {
    this->rows = this->columns = 81;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->status = new char*[3];
    for (int i = 0; i < 3; i++) {
        this->board[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            this->status[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool ultimate_board<T>::update_board(int x, int y, T symbol) {
    int b = board_finder(x,y);
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0) && !played.count(b)) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        if(check_win(x,y)){
            status[x/3][y/3] = toupper(symbol);
            played.insert(b);
        }
        else if(check_draw(x,y)){
            status[x/3][y/3] = 'd';
            played.insert(b);
        }
    }
    else return false;
    return true;
}

template<typename T>
void ultimate_board<T>::display() {
    cout << "  || ";
    for(int i = 0;i < 9;++i){
        cout << i << " | ";
        if((i+1)%3 == 0) cout << "   " << "| ";
    }
    cout << '\n' << string(65,'-');
    for(int i = 0; i < this->rows;++i){
        cout << i + 1 << " || ";
        for(int j = 0; j < this->columns;++j){
            cout << (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << " | ";
            if((j+1)%3 == 0)cout << "   " << "| ";
        }
        cout << '\n';
        if((i+1)%3 == 0) cout << string(65,'-') << '\n';
    }
}

template<typename T>
void ultimate_board<T>::display_status() {
    cout << string(9,'-') << '\n';
    for(int i = 0; i < 3;++i){
        cout << '|';
        for(int j = 0; j < 3;++j){
            cout << (this->status[i][j] == 0 ? ' ' : this->status[i][j]) << '|';
        }
        cout <<'\n' <<string(9,'-') <<'\n';

    }
}

template<typename T>
int ultimate_board<T>::board_finder(int& x, int& y) {
    int xb = x/3;
    int yb = y/3;
    return (xb*3+yb+1);
}










#endif //GAMES_ULTIMATEXO_H
