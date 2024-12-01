#ifndef GAMES_NUMERICAL_TIC_TAC_TOE_H
#define GAMES_NUMERICAL_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <vector>

class Board3x3 : public Board<int> {
public:
    Board3x3();
    bool update_board(int x, int y, int symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};
class Numerical_Tic_Tac_Toe_Player : public Player<int> {
protected:
    std::vector<int> validMoves;
    char evenOrOdd;
public:
    Numerical_Tic_Tac_Toe_Player(std::string n, int symbol);
    Numerical_Tic_Tac_Toe_Player(int symbol);
    void getmove(int& x, int& y) override;
    bool is_valid();
};

class Numerical_Tic_Tac_Toe_Random_Player : public RandomPlayer<int>{
protected:
    std::vector<int> validMoves;
    char evenOrOdd;
public:
    Numerical_Tic_Tac_Toe_Random_Player(int symbol);
    void getmove(int& x, int& y) override;
    bool is_valid();
};
#endif //GAMES_NUMERICAL_TIC_TAC_TOE_H
