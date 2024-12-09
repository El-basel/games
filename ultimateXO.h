#ifndef GAMES_ULTIMATEXO_H
#define GAMES_ULTIMATEXO_H
#include "BoardGame_Classes.h"
#include <vector>
template<typename T>
class ultimate_board : public Board<T>{
private:
    //this shows the status of each board
    T** status;
    int board;

public:
    ultimate_board();
    //checks win on the status board
    bool is_win() override;
    //checks draw on the status board
    bool is_draw() override;
    bool update_board(int x, int y, T symbol) override;
    //displays the main board
    void display() override;
    bool game_is_over() override;
    void display_status();
    //checks if there is a win on the given subboard
    //if a win is found it updates the status board with the player symbol
    bool check_win(int&, T symbol);
    //checks if there is a draw on the given subboard
    //if a draw is found it updates the status board with 'd'
    bool check_draw(int&, T symbol);
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
















#endif //GAMES_ULTIMATEXO_H
