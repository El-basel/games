#include <iostream>
#include "pyramidXO.h"
#include <iomanip>
using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    PyramidBoard<char>* Board = new PyramidBoard<char>();
    string playerXName, playerYName;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[0] = new Pyramid_X_O_Player<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new Pyramid_X_O_Random_Player<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Set up player 2
    cout << "Enter Player O name: ";
    cin >> playerYName;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new Pyramid_X_O_Player<char>(playerXName, 'O');
        break;
    case 2:
        players[1] = new Pyramid_X_O_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(Board, players);
    x_o_game.run();

    // Clean up
    delete Board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}