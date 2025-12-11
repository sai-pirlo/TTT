#include "tictactoe.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void initGame(Game *game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        game->board[i] = ' ';
    }
    game->playerScore = 0;
    game->computerScore = 0;
    game->draws = 0;
    game->difficulty = MEDIUM;
    game->playerSymbol = 'X';
    game->computerSymbol = 'O';
}

void resetBoard(Game *game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        game->board[i] = ' ';
    }
}

void printHeader() {
    printf("\n");
    printf(CYAN BOLD "╔══════════════════════════════════════════════════════════╗\n" RESET);
    printf(CYAN BOLD "║" RESET);
    printf(YELLOW BOLD "           ⚡ ULTIMATE TIC-TAC-TOE CHAMPIONSHIP ⚡         " RESET);
    printf(CYAN BOLD "║\n" RESET);
    printf(CYAN BOLD "╚══════════════════════════════════════════════════════════╝\n" RESET);
    printf("\n");
}

void printBox(const char *text, const char *color) {
    int len = strlen(text);
    printf(color);
    printf("┌");
    for (int i = 0; i < len + 2; i++) printf("─");
    printf("┐\n");
    printf("│ %s │\n", text);
    printf("└");
    for (int i = 0; i < len + 2; i++) printf("─");
    printf("┘\n" RESET);
}

void printBoard(Game *game) {
    printf(BOLD "                    ╔═══════╦═══════╦═══════╗\n" RESET);
    for (int row = 0; row < ROWS; row++) {
        printf(BOLD "                    ║" RESET);
        for (int col = 0; col < COLS; col++) {
            int index = row * COLS + col;
            char cell = game->board[index];
            
            if (cell == game->playerSymbol) {
                printf("   " GREEN BOLD "%c" RESET "   " BOLD "║" RESET, cell);
            } else if (cell == game->computerSymbol) {
                printf("   " RED BOLD "%c" RESET "   " BOLD "║" RESET, cell);
            } else {
                printf("   " CYAN "%d" RESET "   " BOLD "║" RESET, index + 1);
            }
        }
        printf("\n");
        
        if (row < ROWS - 1) {
            printf(BOLD "                    ╠═══════╬═══════╬═══════╣\n" RESET);
        }
    }
    printf(BOLD "                    ╚═══════╩═══════╩═══════╝\n" RESET);
    printf("\n");
}

void printScoreboard(Game *game) {
    printf(MAGENTA BOLD "                    ┌─────────────────────────┐\n" RESET);
    printf(MAGENTA BOLD "                    │" RESET "      " BOLD "SCOREBOARD" RESET "       " MAGENTA BOLD "│\n" RESET);
    printf(MAGENTA BOLD "                    ├─────────────────────────┤\n" RESET);
    printf(MAGENTA BOLD "                    │" RESET GREEN " You:      %2d" RESET "          " MAGENTA BOLD "│\n" RESET, game->playerScore);
    printf(MAGENTA BOLD "                    │" RESET RED " Computer: %2d" RESET "          " MAGENTA BOLD "│\n" RESET, game->computerScore);
    printf(MAGENTA BOLD "                    │" RESET YELLOW " Draws:    %2d" RESET "          " MAGENTA BOLD "│\n" RESET, game->draws);
    printf(MAGENTA BOLD "                    └─────────────────────────┘\n" RESET);
    printf("\n");
}

void printDifficultyMenu() {
    printf(YELLOW BOLD "\n                    ┌─────────────────────────┐\n" RESET);
    printf(YELLOW BOLD "                    │" RESET "   SELECT DIFFICULTY   " YELLOW BOLD "│\n" RESET);
    printf(YELLOW BOLD "                    ├─────────────────────────┤\n" RESET);
    printf(YELLOW BOLD "                    │" RESET " 1. Easy    😊        " YELLOW BOLD "│\n" RESET);
    printf(YELLOW BOLD "                    │" RESET " 2. Medium  😐        " YELLOW BOLD "│\n" RESET);
    printf(YELLOW BOLD "                    │" RESET " 3. Hard    😈        " YELLOW BOLD "│\n" RESET);
    printf(YELLOW BOLD "                    └─────────────────────────┘\n" RESET);
    printf("\n                    " CYAN "Enter choice (1-3): " RESET);
}

int isValidMove(Game *game, int position) {
    return position >= 0 && position < BOARD_SIZE && game->board[position] == ' ';
}

int getPlayerMove(Game *game) {
    int move;
    printf("                    " CYAN BOLD "Your move (1-9): " RESET);
    scanf("%d", &move);
    return move - 1;
}

void makePlayerMove(Game *game, int position) {
    if (isValidMove(game, position)) {
        game->board[position] = game->playerSymbol;
    }
}

char checkWinner(Game *game) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (game->board[i*3] != ' ' && 
            game->board[i*3] == game->board[i*3+1] && 
            game->board[i*3+1] == game->board[i*3+2]) {
            return game->board[i*3];
        }
    }
    
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (game->board[i] != ' ' && 
            game->board[i] == game->board[i+3] && 
            game->board[i+3] == game->board[i+6]) {
            return game->board[i];
        }
    }
    
    // Check diagonals
    if (game->board[0] != ' ' && 
        game->board[0] == game->board[4] && 
        game->board[4] == game->board[8]) {
        return game->board[0];
    }
    
    if (game->board[2] != ' ' && 
        game->board[2] == game->board[4] && 
        game->board[4] == game->board[6]) {
        return game->board[2];
    }
    
    return ' ';
}

int isBoardFull(Game *game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (game->board[i] == ' ') {
            return 0;
        }
    }
    return 1;
}

int easyAI(Game *game) {
    int move;
    do {
        move = rand() % BOARD_SIZE;
    } while (!isValidMove(game, move));
    return move;
}

int mediumAI(Game *game) {
    // Try to win
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (isValidMove(game, i)) {
            game->board[i] = game->computerSymbol;
            if (checkWinner(game) == game->computerSymbol) {
                game->board[i] = ' ';
                return i;
            }
            game->board[i] = ' ';
        }
    }
    
    // Block player
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (isValidMove(game, i)) {
            game->board[i] = game->playerSymbol;
            if (checkWinner(game) == game->playerSymbol) {
                game->board[i] = ' ';
                return i;
            }
            game->board[i] = ' ';
        }
    }
    
    // Take center
    if (isValidMove(game, 4)) {
        return 4;
    }
    
    // Take corners
    int corners[] = {0, 2, 6, 8};
    for (int i = 0; i < 4; i++) {
        if (isValidMove(game, corners[i])) {
            return corners[i];
        }
    }
    
    // Take any available
    return easyAI(game);
}

int evaluateBoard(Game *game) {
    char winner = checkWinner(game);
    if (winner == game->computerSymbol) return 10;
    if (winner == game->playerSymbol) return -10;
    return 0;
}

int minimax(Game *game, int depth, int isMaximizing) {
    int score = evaluateBoard(game);
    
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (isBoardFull(game)) return 0;
    
    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (game->board[i] == ' ') {
                game->board[i] = game->computerSymbol;
                int val = minimax(game, depth + 1, 0);
                best = (val > best) ? val : best;
                game->board[i] = ' ';
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (game->board[i] == ' ') {
                game->board[i] = game->playerSymbol;
                int val = minimax(game, depth + 1, 1);
                best = (val < best) ? val : best;
                game->board[i] = ' ';
            }
        }
        return best;
    }
}

int hardAI(Game *game) {
    int bestMove = -1;
    int bestVal = -1000;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (game->board[i] == ' ') {
            game->board[i] = game->computerSymbol;
            int moveVal = minimax(game, 0, 0);
            game->board[i] = ' ';
            
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    
    return bestMove;
}

void makeComputerMove(Game *game) {
    int move;
    
    printf(YELLOW "                    🤖 Computer is thinking..." RESET);
    fflush(stdout);
    
    // Simulate thinking time
    for (int i = 0; i < 3; i++) {
        #ifdef _WIN32
            Sleep(300);
        #else
            usleep(300000);
        #endif
        printf(".");
        fflush(stdout);
    }
    printf("\n\n");
    
    switch (game->difficulty) {
        case EASY:
            move = easyAI(game);
            break;
        case MEDIUM:
            move = mediumAI(game);
            break;
        case HARD:
            move = hardAI(game);
            break;
        default:
            move = mediumAI(game);
    }
    
    game->board[move] = game->computerSymbol;
    printf(RED BOLD "                    Computer chose position %d\n\n" RESET, move + 1);
}

void celebrateWin(char winner, Game *game) {
    if (winner == game->playerSymbol) {
        printf(GREEN BOLD "\n");
        printf("                    ╔════════════════════════════╗\n");
        printf("                    ║  🎉 CONGRATULATIONS! 🎉   ║\n");
        printf("                    ║      YOU ARE VICTORIOUS!   ║\n");
        printf("                    ╚════════════════════════════╝\n");
        printf(RESET "\n");
    } else if (winner == game->computerSymbol) {
        printf(RED BOLD "\n");
        printf("                    ╔════════════════════════════╗\n");
        printf("                    ║    😔 DEFEAT! 😔           ║\n");
        printf("                    ║   Computer wins this round ║\n");
        printf("                    ╚════════════════════════════╝\n");
        printf(RESET "\n");
    } else {
        printf(YELLOW BOLD "\n");
        printf("                    ╔════════════════════════════╗\n");
        printf("                    ║      🤝 IT'S A DRAW! 🤝    ║\n");
        printf("                    ║     Well played by both!   ║\n");
        printf("                    ╚════════════════════════════╝\n");
        printf(RESET "\n");
    }
}

void playGame(Game *game) {
    char winner = ' ';
    int moves = 0;
    
    resetBoard(game);
    
    while (winner == ' ' && !isBoardFull(game)) {
        clearScreen();
        printHeader();
        printScoreboard(game);
        printBoard(game);
        
        if (moves % 2 == 0) {
            // Player turn
            int move;
            do {
                move = getPlayerMove(game);
                if (!isValidMove(game, move)) {
                    printf(RED "                    ❌ Invalid move! Try again.\n\n" RESET);
                }
            } while (!isValidMove(game, move));
            
            makePlayerMove(game, move);
        } else {
            // Computer turn
            makeComputerMove(game);
            printf("                    Press Enter to continue...");
            getchar();
        }
        
        winner = checkWinner(game);
        moves++;
    }
    
    clearScreen();
    printHeader();
    printBoard(game);
    
    if (winner == game->playerSymbol) {
        game->playerScore++;
        celebrateWin(winner, game);
    } else if (winner == game->computerSymbol) {
        game->computerScore++;
        celebrateWin(winner, game);
    } else {
        game->draws++;
        celebrateWin(' ', game);
    }
}

int main() {
    Game game;
    int choice;
    char playAgain;
    
    srand(time(NULL));
    initGame(&game);
    
    clearScreen();
    printHeader();
    
    printf(CYAN "                    Welcome, Champion! What's your name? " RESET);
    char name[50];
    scanf("%s", name);
    getchar();
    
    printf(GREEN "\n                    Hello, %s! Ready to battle? 🎮\n" RESET, name);
    printf("                    Press Enter to continue...");
    getchar();
    
    // Difficulty selection
    clearScreen();
    printHeader();
    printDifficultyMenu();
    scanf("%d", &choice);
    getchar();
    
    if (choice >= 1 && choice <= 3) {
        game.difficulty = choice;
    }
    
    do {
        playGame(&game);
        
        printf("                    " CYAN "Play again? (y/n): " RESET);
        scanf(" %c", &playAgain);
        getchar();
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    clearScreen();
    printHeader();
    printScoreboard(&game);
    
    printf(MAGENTA BOLD "\n                    ╔════════════════════════════╗\n" RESET);
    printf(MAGENTA BOLD "                    ║  Thanks for playing, %s!" RESET, name);
    
    // Add spaces for alignment
    int nameLen = strlen(name);
    for (int i = nameLen; i < 6; i++) {
        printf(" ");
    }
    printf(MAGENTA BOLD "║\n" RESET);
    printf(MAGENTA BOLD "                    ╚════════════════════════════╝\n\n" RESET);
    
    return 0;
}
