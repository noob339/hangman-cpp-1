# Hangman (C++)

## Gameplay

The goal is to guess the hidden word one letter at a time before the hangman drawing is completed.

- The game randomly selects a Washington State city.
- The first letter is revealed as a hint.
- Each incorrect guess adds another part to the hangman.
- The player wins by revealing the complete word before making six incorrect guesses.

## Project Structure

```
hangman-cpp/
├── README.md
└── src/
    ├── Dictionary.h
    ├── Dictionary.cpp
    ├── Drawing.h
    ├── Drawing.cpp
    ├── Game.h
    ├── Game.cpp
    └── main.cpp
```

### File Overview

| File | Description |
|------|-------------|
| `main.cpp` | Program entry point |
| `Game` | Controls the game loop and user interaction |
| `Dictionary` | Stores the list of possible words and selects one randomly |
| `Drawing` | Displays the ASCII hangman based on the number of incorrect guesses |

## Building

This project requires a C++17 (or later)

Compile the project using:

```bash
g++ -std=c++17 src/*.cpp -o hangman
```

Run the program:

```bash
./hangman
```
