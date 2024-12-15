#include "BoardGame_Classes.h"
#include <map>
#ifndef GAMES_4X4TIC_TAC_TOE_H
#define GAMES_4X4TIC_TAC_TOE_H

class Board4x4 : public Board<char> {
private:
    int oldX, oldY;
public:
    Board4x4();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_valid_cell(int newX, int newY, int oldX, int oldY, char symbol);
    void setOldX(int);
    void setOldY(int);
    ~Board4x4();
};

class Player4x4 : public Player<char> {
public:
    Player4x4(std::string n, char symbol);
    Player4x4(char symbol);
    void getmove(int& x, int& y) override;
};

class Random_Player4x4 : public RandomPlayer<char>{
private:
    std::map<int,std::pair<int,int>> recentMoves;
public:
    Random_Player4x4(char symbol);
    void getmove(int& x, int& y) override;
};

#endif //GAMES_4X4TIC_TAC_TOE_H
