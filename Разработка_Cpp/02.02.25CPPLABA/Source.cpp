#include "Header.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

int rollDice() {
    return (rand() % 6) + 1;
}

string diceToSymbol(int dice) {
    switch (dice) 
    {
    case 1: return ".";
    case 2: return ":";
    case 3: return ".:";
    case 4: return "::";
    case 5: return "::.";
    case 6: return ":::";
    default: return "?";
    }
}

void playTurn(int& score, vector<string>& diceRolls, const string& playerName) {
    int dice1 = rollDice();
    int dice2 = rollDice();
    score += dice1 + dice2;
    diceRolls.push_back(diceToSymbol(dice1) + " " + diceToSymbol(dice2));
    cout << playerName << " roll: " << diceToSymbol(dice1) << " " << diceToSymbol(dice2) << endl;
}

void determineWinner(int playerScore, int computerScore, const vector<string>& playerDice, const vector<string>& computerDice) {
    double playerAvg = static_cast<double>(playerScore) / 5.0;
    double computerAvg = static_cast<double>(computerScore) / 5.0;

    cout << "\n--- Game Results ---" << endl;
    cout << "Your dice rolls: ";
    for (const auto& dice : playerDice) {
        cout << dice << "  ";
    }
    cout << "\nComputer dice rolls: ";
    for (const auto& dice : computerDice) {
        cout << dice << "  ";
    }

    cout << "\nYour total score: " << playerScore << endl;
    cout << "Computer total score: " << computerScore << endl;

    cout << "Your average score per roll: " << playerAvg << endl;
    cout << "Computer average score per roll: " << computerAvg << endl;

    if (playerScore > computerScore) {
        cout << "You win!" << endl;
    }
    else if (computerScore > playerScore) {
        cout << "Computer wins!" << endl;
    }
    else {
        cout << "It's a tie!" << endl;
    }
}