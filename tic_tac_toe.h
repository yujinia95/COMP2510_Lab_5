/**
* Author: Yujin Jeong
* Date: 12th Oct 2024
* tic_tac_toe.h
* Purpose: Making a header file to share declarations between multiple c files without duplicating code.
*/
#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#define MIN_PLAYERS 2
#define MAX_PLAYERS 8
#define STARTING_SIZE 3

typedef struct {
    char **board;
    int game_size;
    int current_player;
    int num_players;
    char user_unique_symbols[MAX_PLAYERS];
    int *players_moves;
    int players_wins[8];
} Game;

// Function prototypes
Game* init_game();
void display_board(const Game *game);
int make_move(Game *game, int row, int col);
char check_winner(const Game *game);
void free_game(Game *game);

#endif