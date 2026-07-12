#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    std::srand(std::time(nullptr));

    std::cout << "=======================================" << std::endl;
    std::cout << " Hangman Game" << std::endl;
    std::cout << "=======================================" << std::endl;
    

    Game game;
    game.playLoop();

    return 0;
}