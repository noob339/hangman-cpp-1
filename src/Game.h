#ifndef GAME_H
#define GAME_H

#include "Dictionary.h"

#include <string>
#include <vector>

class Game {
public:
    Game();

    void newGame();
    void play();
    void playLoop();
    void scoreboard();

private:

    static const int maxErrors = 6;

    Dictionary dictionary;
    std::string wordToFind;
    std::vector<char> wordFound;
    int numberOfErrors;
    std::vector<std::string> guessedLetters;
    
    int numOfGames;
    unsigned int wins;
    unsigned int losses;

    void processGuess(const std::string& userInput);
    bool isWordFound() const;
    std::string wordFoundContent() const;
    int findLetters(char userInput);
    void processGuessWord(std::string userInput);
};

#endif