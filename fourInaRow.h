#include "BoardGame_Classes.h"
#ifndef GAMES_FOUR_IN_A_ROW_H
#define GAMES_FOUR_IN_A_ROW_H


class Board6x7 : public Board<char> {
public:
    Board6x7();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_valid_cell(int x, int y);
};

class Four_In_A_Row_Player : public Player<char> {
public:
    Four_In_A_Row_Player(std::string n, char symbol);
    Four_In_A_Row_Player(char symbol);
    void getmove(int& x, int& y) override;
};

class Four_In_A_Row_Random_Player : public RandomPlayer<char>{
public:
    Four_In_A_Row_Random_Player(char symbol);
    void getmove(int& x, int& y) override;
};

#endif //GAMES_FOUR_IN_A_ROW_H
