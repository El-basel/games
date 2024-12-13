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
    void display_board() override;
    bool game_is_over() override;
    void display_status();
    int board_finder(int&,int&);
    //checks if there is a win on the given indices subboard
    bool check_win(int&,int&);
    //checks if there is a draw on the given indices subboard
    bool check_draw(int&,int&);
};

template<typename T>
class ultimate_Player: public Player<T>{
public:
    ultimate_Player(const string&,T);
    void getmove(int&,int&) override;
    //checks if the given string is a valid postive number
};

template<typename T>
class ultimate_Random: public RandomPlayer<T>{
public:
    ultimate_Random(T symbol);
    void getmove(int&,int&) override;
};


//--------------------------------------- IMPLEMENTATION
#include <string>
template<typename T>
ultimate_board<T>::ultimate_board() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->status = new char*[3];
    for (int i = 0; i < 3; i++) {
        this->status[i] = new char[3];
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
        display_status();
    }
    else return false;
    return true;
}

template<typename T>
void ultimate_board<T>::display_board() {
    cout << "  || ";
    for(int i = 0;i < 9;++i){
        cout << i+1 << " | ";
        if((i+1)%3 == 0 && i != 8) cout << "   " << "| ";
    }
    cout << '\n' << string(65,'-') << '\n';
    for(int i = 0; i < this->rows;++i){
        cout << i + 1 << " || ";
        for(int j = 0; j < this->columns;++j){
            cout << (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << " | ";
            if((j+1)%3 == 0 && j != 8)cout << "   " << "| ";
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

template<typename T>
bool ultimate_board<T>::is_win() {
    // Check rows and columns of status board
    for (int i = 0; i < 3; i++) {
        if ((this->status[i][0] == this->status[i][1] && this->status[i][1] == this->status[i][2] && this->status[i][0] != 0) ||
            (this->status[0][i] == this->status[1][i] && this->status[1][i] == this->status[2][i] && this->status[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals of status board
    if ((this->status[0][0] == this->status[1][1] && this->status[1][1] == this->status[2][2] && this->status[0][0] != 0) ||
        (this->status[0][2] == this->status[1][1] && this->status[1][1] == this->status[2][0] && this->status[0][2] != 0)) {
        return true;
    }

    return false;
}

template<typename T>
bool ultimate_board<T>::is_draw() {
    //if all moves in the main board is played
    //and theres no win in the status board
    //game is a draw
    return (this->n_moves == 81 && !is_win());
}

template<typename T>
bool ultimate_board<T>::game_is_over() {
    return (is_win() || is_draw());
}

template<typename T>
bool ultimate_board<T>::check_win(int& x, int& y) {
    //Adjust x and y to be on the top left corner of the sub board
    int xc = (x / 3) * 3;
    int yc = (y / 3) * 3;
    //check rows and colums of the given subboard index for a win
    for (int i = 0; i < 3; i++) {
        if ((this->board[xc + i][yc] == this->board[xc + i][yc + 1] && this->board[xc + i][yc + 1] == this->board[xc + i][yc + 2] && this->board[xc + i][yc] != 0) ||
            (this->board[xc][yc + i] == this->board[xc + 1][yc + i] && this->board[xc + 1][yc + i] == this->board[xc + 2][yc + i] && this->board[xc][yc + i] != 0)) {

            return true;
        }
    }

    //check diagonals of the given subboard index for a win
    if ((this->board[xc][yc] == this->board[xc + 1][yc + 1] && this->board[xc + 1][yc + 1] == this->board[xc + 2][yc + 2] && this->board[xc][yc] != 0) ||
        (this->board[xc][yc + 2] == this->board[xc + 1][yc + 1] && this->board[xc + 1][yc + 1] == this->board[xc + 2][yc] && this->board[xc][yc + 2] != 0)) {

        return true;
    }

    return false;
}

template<typename T>
bool ultimate_board<T>::check_draw(int& x, int& y) {
    //Adjust x and y to be on the top left corner of the sub board
    int xc = (x / 3) * 3;
    int yc = (y / 3) * 3;

    //loop through each sub board slot and check if theyre all filled or not
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->board[xc + i][yc + j] == 0) {
                return false;
            }
        }
    }
    
    return !check_win(x, y);
}
//---------------------------------------------
template<typename T>
ultimate_Player<T>::ultimate_Player(const string& name , T symbol) : Player<T>(name,symbol){}

template<typename T>
void ultimate_Player<T>::getmove(int& x, int& y) {
    string choice;
    cout << "please enter the row of your choice(1-5): ";
    getline(cin >> ws, choice);
    while (choice.size() != 1 && isdigit(choice[0])) {
        cout << "please enter a number that is between(1-5): ";
        getline(cin >> ws, choice);
    }
    x = stoi(choice);
    cout << "please enter the column of your choice(1-5): ";
    getline(cin >> ws, choice);
    while (choice.size() != 1 && isdigit(choice[0])) {
        cout << "please enter a number that is between(1-5): ";
        getline(cin >> ws, choice);
    }
    y = stoi(choice);
    --x;--y;
}
//---------------------------------------------
template<typename T>
ultimate_Random<T>::ultimate_Random(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(NULL)));  // Seed the random number generator
}

template<typename T>
void ultimate_Random<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}


#endif //GAMES_ULTIMATEXO_H
