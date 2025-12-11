#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Color codes for terminal
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"
#define BG_BLACK "\033[40m"
#define BG_CYAN "\033[46m"

// Game constants
#define BOARD_SIZE 9
#define ROWS 3
#define COLS 3

// Difficulty levels
#define EASY 1
#define MEDIUM 2
#define HARD 3

// Game structure
typedef struct {
    char board[BOARD_SIZE];
    int playerScore;
    int computerScore;
    int draws;
    int difficulty;
    char playerSymbol;
    char computerSymbol;
} Game;

// Function prototypes
void initGame(Game *game);
void clearScreen();
void printHeader();
void printBoard(Game *game);
void printMenu();
void printScoreboard(Game *game);
void printDifficultyMenu();
int getPlayerMove(Game *game);
void makePlayerMove(Game *game, int position);
void makeComputerMove(Game *game);
char checkWinner(Game *game);
int isBoardFull(Game *game);
int isValidMove(Game *game, int position);
void resetBoard(Game *game);
void playGame(Game *game);
void celebrateWin(char winner, Game *game);
void printBox(const char *text, const char *color);

// AI functions
int easyAI(Game *game);
int mediumAI(Game *game);
int hardAI(Game *game);
int minimax(Game *game, int depth, int isMaximizing);
int evaluateBoard(Game *game);

#endif
