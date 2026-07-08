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

private:

    static const int maxErrors = 6;

    Dictionary dictionary;
    std::string wordToFind;
    std::vector<char> wordFound;
    int numberOfErrors;
    std::vector<std::string> guessedLetters;

    void processGuess(const std::string& userInput);
    bool isWordFound() const;
    std::string wordFoundContent() const;
};

#endif