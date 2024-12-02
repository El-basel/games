#include <iostream>
#include "fourInaRow.h"
#include <string>
#include "numericalTicTacToe.h"

void getNameAndType(std::string& player1, std::string& player2, int& type1 , int& type2)
{
    std::string type1String, type2String;
    std::cout << "Choose Player 1 Name: ";
    std::cin >> player1;

    do {
        std::cout << "Choose Player 1 type: \n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        std::getline(std::cin >> std::ws, type1String);
    } while(type1String.length() > 1 || type1String[0] > '2' || type1String[0] < '1');
    type1 = type1String[0] - '0';

    std::cout << "Choose Player 2 Name: ";
    std::cin >> player2;

    do {
        std::cout << "Choose Player 2 type: \n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        std::getline(std::cin >> std::ws, type2String);
    } while(type2String.length() > 1 || type2String[0] > '2' || type2String[0] < '1');
    type2 = type2String[0] - '0';
}

void fourInaRow()
{
    int type1, type2;
    std::string player1Name, player2Name;
    Player<char>* players[2];
    Board<char>* board = new Board6x7();
    std::cout << "----------------------------\n";
    std::cout << "| Welcome to Four in a Row |\n";
    std::cout << "----------------------------\n";
    getNameAndType(player1Name,player2Name, type1, type2);

    switch(type1) {
        case 1:
            players[0] = new Four_In_A_Row_Player(player1Name, 'X');
            break;
        case 2:
            players[0] = new Four_In_A_Row_Random_Player('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    switch(type2) {
        case 1:
            players[1] = new Four_In_A_Row_Player(player2Name, 'O');
            break;
        case 2:
            players[1] = new Four_In_A_Row_Random_Player('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }
    GameManager<char> four_in_a_row(board, players);
    four_in_a_row.run();

    delete board;
    delete players[0];
    delete players[1];
}

void numericalTicTacToe()
{
    int type1, type2;
    std::string player1Name, player2Name;
    Player<int>* players[2];
    Board<int>* board = new Board3x3();
    std::cout << "------------------------------------\n";
    std::cout << "| Welcome to Numerical Tic Tac Toe |\n";
    std::cout << "------------------------------------\n";
    getNameAndType(player1Name, player2Name, type1, type2);
    switch(type1) {
        case 1:
            players[0] = new Numerical_Tic_Tac_Toe_Player(player1Name, 2);
            break;
        case 2:
            players[0] = new Numerical_Tic_Tac_Toe_Random_Player(2);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    switch(type2) {
        case 1:
            players[1] = new Numerical_Tic_Tac_Toe_Player(player2Name, 1);
            break;
        case 2:
            players[1] = new Numerical_Tic_Tac_Toe_Random_Player(1);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }
    GameManager<int> numerical_tic_tac_toe(board, players);
    numerical_tic_tac_toe.run();

    delete board;
    delete players[0];
    delete players[1];
}

int main() {
    std::cout << "-------------------------\n";
    std::cout << "| Welcome to Mini Games |\n";
    std::cout << "-------------------------\n";
    std::string choiceString;
    int choice;
    while (true)
    {
        std::cout << "Choose one of the following games to start playing or exit the program\n";
        std::cout << "1. Four in a Row\n";
        std::cout << "2. Numerical Tic Tac Toe\n";
        std::cout << "3. Exit\n";
        while (true)
        {
            std::cout << "Enter Your choice: ";
            std::getline(std::cin >> std::ws, choiceString);
            if(choiceString.length() != 1 || choiceString[0] > '3' || choiceString[0] < '1')
            {
                std::cout << "Invalid choice\n";
                continue;
            }
            break;
        }
        choice = choiceString[0] - '0';
        switch (choice) {
            case 1:
                fourInaRow();
                break;
            case 2:
                numericalTicTacToe();
                break;
            default:
                return 0;
        }
    }
}