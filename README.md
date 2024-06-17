# Wordle Game

Welcome to Wordle, a simple word-guessing game!

## Description
Wordle is a game where you have to guess a five-letter word within a limited number of attempts.

## Getting Started
To play the game, follow these steps:

1. **Clone the Repository:**

`git clone https://github.com/ArihantGarg/wordle.git
cd wordle`


2. **Run the Game:**
In your terminal, type the following command:

`make play`

This will compile and run the game.

3. **Gameplay Instructions:**
- You have to guess the secret 5-letter word.
- After each guess, you will receive feedback on the correctness of each letter.
- Guess by entering a 5-letter word in lowercase (e.g., "apple").
- The letters will be marked as follows:
  - `+` for correct letters in the correct position by GREEN.
  - `-` for correct letters in the wrong position by YELLOW.
  - `*` for incorrect letters by BLACK.

4. **Ending the Game:**
- You win if you guess the word correctly.

5. **Restarting the Game:**
- To play again, simply run `make play` again in the terminal.

## Requirements
- This game requires a Unix-based operating system (Linux or macOS) with `bash` and `make` installed.
- Ensure you have a C++ compiler (e.g., `g++`) installed to compile the game.

## Contributions
Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or a pull request on [GitHub](https://github.com/ArihantGarg/wordle).
