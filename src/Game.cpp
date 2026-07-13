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

    char option;

    do{
      
        std::cout << "Choose a city set: \n";
        std::cout << "1: for Washington State Cities\n";
        std::cout << "2: New York State Cities\n\noption: ";

        std::cin >> option;

        std::cin.ignore(10000, '\n');

    } while (option != '1' && option != '2');


    if (option == '1'){
        std::cout << "\nLet's guess a Washington State city!" << std::endl;
    } else if(option == '2'){
        std::cout << "\nLet's guess a New York State city!" << std::endl;
    } 

    guessedLetters.clear();

    wordToFind = dictionary.getRandomWord(std::stoi(std::string{option})); 

    wordFound = std::vector<char>(wordToFind.length(), '_'); 

    size_t index = wordToFind.find(" ");

    if(index != std::string::npos){
        wordFound[index] = ' ';
    }

    wordFound[0] = wordToFind[0]; 

    std::cout << "\nHint: the " << dictionary.getCategory(option)
              << " starts with " << wordToFind[0] << std::endl;
}

//if you enter a random letter when deciding which state to play with, it will enter a never ending loop


void Game::playLoop(){

    std::string userInput;
    char lowerCase;
    
    do {
        newGame();
        play();

        scoreboard();
        

        do {
            std::cout << "Play again? (y/n): ";
            std::cin >> userInput;

            lowerCase = std::tolower(static_cast<unsigned char>(userInput[0]));

            std::cout << "\n";

        } while(lowerCase != 'n' && lowerCase != 'y');
        
    } while(lowerCase == 'y');
}

void Game::play() {
    
    numOfGames++;

    while (numberOfErrors < maxErrors && !isWordFound()) {
        std::cout << "\nEnter a letter or a city name: ";

        std::string userInput {};
        std::getline(std::cin >> std::ws, userInput);

        if (userInput.length() > 1) {
            processGuessWord(userInput);
        } else{
            userInput = userInput.substr(0, 1);
            processGuess(userInput);
        }

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

void Game::processGuessWord(std::string userInput){
    bool result = wordToFind == userInput;

    if (result == false){
        numberOfErrors++;
    } else {
        wordFound.clear();
        wordFound.insert(wordFound.begin(), userInput.begin(), userInput.end());
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