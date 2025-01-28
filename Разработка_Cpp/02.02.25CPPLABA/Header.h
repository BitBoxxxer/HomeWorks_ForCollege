#ifndef DICE_H
#define DICE_H

#include <string>
#include <vector>

int rollDice();
std::string diceToSymbol(int dice);
void playTurn(int& score, std::vector<std::string>& diceRolls, const std::string& playerName);
void determineWinner(int playerScore, int computerScore, const std::vector<std::string>& playerDice, const std::vector<std::string>& computerDice);

#endif