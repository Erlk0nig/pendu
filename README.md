# Hangman Game in C

This is a simple Hangman game implemented in C that selects a word to guess from multiple word list files. Players must guess the word letter by letter, and the game tracks the top 10 scores, sorted by the number of attempts used to guess the word. The scores are stored in a `scores.txt` file.

## Features
- The game selects a random word from a set of multiple text files containing word lists.
- Players have to guess the word by inputting one letter at a time.
- A `scores.txt` file tracks the scores. The score is based on how quickly the player guesses the word, with fewer attempts resulting in a better score.
- The top 10 scores are displayed at the end of the game, sorted in ascending order of attempts.
  
## Prerequisites
- A C compiler (e.g., GCC) to compile the code.
- The game expects at least one word list file. You can add more word list files to increase the word pool.
