#include "Header.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

int main() 
{
    srand(time(0));
    int playerScore = 0;
    int computerScore = 0;
    vector<string> playerDice;
    vector<string> computerDice;
    char firstTurn;

    cout << "Do you want to go first? (y/n): ";
    cin >> firstTurn;

    for (int i = 0; i < 5; ++i) {
        if ((firstTurn == 'y' && i % 2 == 0) || (firstTurn == 'n' && i % 2 != 0)) {
            playTurn(playerScore, playerDice, "Your");
        }
        else {
            playTurn(computerScore, computerDice, "Computer");
        }
    }
    determineWinner(playerScore, computerScore, playerDice, computerDice);
    return 0;
}