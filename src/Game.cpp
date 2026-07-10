#include "Game.h"
#include "Drawing.h"

#include <algorithm>
#include <iostream>

Game::Game() {
    numberOfErrors = 0;
    numOfGames = 0;
    wins = 0;
    losses = 0;
}

void Game::newGame() {
    numberOfErrors = 0;
 

    guessedLetters.clear();

    wordToFind = dictionary.getRandomWord();
    wordFound = std::vector<char>(wordToFind.length(), '_');
    wordFound[0] = wordToFind[0];

    std::cout << "\nHint: the " << dictionary.getCategory()
              << " starts with " << wordToFind[0] << std::endl;
}

void Game::playLoop(){

    std::string userInput;
    
    do{

        newGame();
        play();

        scoreboard();

        std::cout << "Press 1 to play again and continue, any other key to stop: ";

        std::cin >> userInput;

        std::cout << "\n";
        
    }while(userInput == "1");

}

void Game::play() {
    
    numOfGames++;

    while (numberOfErrors < maxErrors && !isWordFound()) {
        std::cout << "\nEnter a letter: ";

        std::string userInput;
        std::cin >> userInput;

        if (userInput.length() > 1) {
            userInput = userInput.substr(0, 1);
        }

        processGuess(userInput);

        std::cout << Drawing::getDrawing(numberOfErrors) << std::endl;
        std::cout << wordFoundContent() << std::endl;
        std::cout << "Remaining tries: " << maxErrors - numberOfErrors << std::endl;
    }

    if (isWordFound()) {
        std::cout << "\nCongratulations! You win!\n" << std::endl;
        wins++;
    } else {
        std::cout << "\nOh no! The hangman is complete." << std::endl;
        std::cout << "The city was: " << wordToFind << "\n" <<  std::endl;
        losses++;
    }


}

void Game::processGuess(const std::string& userInput) {
    if (std::find(guessedLetters.begin(), guessedLetters.end(), userInput) != guessedLetters.end()) {
        std::cout << "You already guessed '" << userInput
                  << "'. Try another letter." << std::endl;
        return;
    }

    guessedLetters.push_back(userInput);

    std::string str {};

    if (userInput[0] >= 65 && userInput[0] <= 90){
        
        char lowerCase = tolower(userInput[0]);
        str = std::string{lowerCase};
        guessedLetters.push_back(str);
    }


    if (wordToFind.find(tolower(userInput[0])) != std::string::npos) {
        size_t index = wordToFind.find(tolower(userInput[0]));

        while (index != std::string::npos) {
            wordFound[index] = tolower(userInput[0]);
            index = wordToFind.find(tolower(userInput[0]), index + 1);
        }
    } else {
        numberOfErrors++;
    }
}

bool Game::isWordFound() const {
    return wordToFind == std::string(wordFound.begin(), wordFound.end());
}

std::string Game::wordFoundContent() const {
    std::string content;

    for (size_t i = 0; i < wordFound.size(); i++) {
        content += wordFound[i];

        if (i < wordFound.size() - 1) {
            content += " ";
        }
    }

    return content;
}



void Game::scoreboard(){

    std::cout << "Scoreboard\n" 
        << "-----------------\n"
        << "Games played: " << numOfGames << "\n"
        << "Wins: " << wins << "\n"
        << "Losses: " << losses << "\n\n";
}