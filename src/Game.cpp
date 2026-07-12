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

    std::cout << "Choose a city set: \n";
    std::cout << "1: for Washington State Cities\n";
    std::cout << "2: New York State Cities\n\noption: ";

    int option;
    std::cin >> option;

    if (option == 1){
        std::cout << "\nLet's guess a Washington State city!" << std::endl;
    } else {
        std::cout << "\nLet's guess a New York State city!" << std::endl;
    }    

    guessedLetters.clear();

    wordToFind = dictionary.getRandomWord(option); 

    wordFound = std::vector<char>(wordToFind.length(), '_'); 

    size_t index = wordToFind.find(" ");

    if(index != std::string::npos){
        wordFound[index] = ' ';
    }

    wordFound[0] = wordToFind[0]; 

    std::cout << "\nHint: the " << dictionary.getCategory(option)
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
        
    }
    while(userInput == "1");

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

int Game::findLetters(char userInput){

    if (wordToFind.find(userInput) != std::string::npos) { 
        size_t index = wordToFind.find(userInput); 

        while (index != std::string::npos) {
            wordFound[index] = userInput;
            index = wordToFind.find(userInput, index + 1); 
        }
        return 1;
    }

   guessedLetters.push_back(std::string(1, userInput));
   return 0;
}

void Game::processGuess(const std::string& userInput) {

    if (std::find(guessedLetters.begin(), guessedLetters.end(), userInput) != guessedLetters.end()) {
        std::cout << "You already guessed '" << userInput
                  << "'. Try another letter." << std::endl;
        return;
    }

    std::string str {};

    if (userInput[0] >= 65 && userInput[0] <= 90){
        
        char lowerCase = tolower(userInput[0]);
        str = std::string{lowerCase};
    } else {
        char upperCase = toupper(userInput[0]);
        str = std::string{upperCase};
    }

    if (findLetters(userInput[0]) == 1){
        findLetters(str[0]);
    } else{
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