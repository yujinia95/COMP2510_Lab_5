/**
* Author: Yujin Jeong
* Date: 12th Oct 2024
* Purpose: Implementing functions for a TIC-TAC-TOE game.
*/
#include <stdio.h>
#include <stdlib.h>
#include "tic_tac_toe.h"
char unique_symbols[8] = {'X', 'O', 'A', 'B', 'C', 'D', 'E', 'F'};

// Creating board
Game* init_game() {

    Game *game = (Game*)malloc(sizeof(Game));
    printf("Enter the number of players (Min: 2 / Max: 8): ");
    scanf("%d",&game -> num_players);

    // If invalid number of players reject them
    if (game -> num_players < MIN_PLAYERS || game -> num_players > MAX_PLAYERS) {
        printf("Invalid number of players.");
        free(game);
        return NULL;
    }

    // Allocating memory for the players moves array. One int for each player.
    game -> players_moves = (int*)malloc(game->num_players * sizeof(int));

    // Assign the unique symbol to players
    for (int i = 0; i < game -> num_players; i++) {
        game -> user_unique_symbols[i] = unique_symbols[i];
    }

    // Setting board size based on number of players (e.g. 6players then board size 7x7)
    game -> game_size = STARTING_SIZE + game -> num_players - 2;
    game -> board = (char **)malloc(game -> game_size * sizeof(char *));
    for (int p = 0; p < game -> game_size; p++) {
        game -> board[p] = (char *)malloc(game -> game_size * sizeof(char));
    }

    for (int i = 0; i < game -> game_size; i++) {
        for (int j = 0; j < game -> game_size; j++) {
            game ->board[i][j] = ' ';
        }
    }
    game -> current_player = 0;
    return game;
}

// Creating a visual representation of the Tic-Tac-Toe board.
void display_board(const Game *game) {
    for (int i = 0; i < game -> game_size; i++) {
        for (int j = 0; j< game -> game_size; j++) {
            printf(" %c ", game -> board[i][j]);
            if (j < game -> game_size - 1) {
                printf("|");
            }
        }
        printf("\n");
        if ( i < game -> game_size -1) {
            for (int k = 0; k < game -> game_size; k++) {
                printf("---");
                if (k < game -> game_size -1) {
                    printf("|");
                }
            }
            printf("\n");
        }
    }
}

// Making a move on the board
int make_move(Game *game, int row, int col) {
    if ( row < 0 || row >= game -> game_size || col < 0 || col >= game -> game_size || game-> board[row][col] != ' ') {
        return 0;
    }

    // Getting a current player's symbol
    char current_symbol = game -> user_unique_symbols[game -> current_player];

    // Current player's mark on the board at the specified row and column.
    game -> board[row][col] = current_symbol;

    // Increasing the number of move for the current player
    // (e.g. player 1 is in the index0 in players_moves array as initialized 0. Then increment that number)
    game -> players_moves[game -> current_player]++;

    printf("Total number of moves for player%d: %d\n", game -> current_player + 1,
        game -> players_moves[game -> current_player]);

    game -> current_player = (game -> current_player + 1) % game -> num_players;
    return 1;
}

// Checks for a winner by iterating through each row, column, and diagonal.
char check_winner(const Game *game) {
    int size = game -> game_size;

    // Checking row
    for (int i = 0; i < size; i++) {
        char rows_with_column_0 = game -> board[i][0];

        if(rows_with_column_0 != ' ') {
            int all_rows = 1;

            // Checking if all row and column has the same symbol as row[i] and column 0.
            for (int j = 1; j < size; j++) {
                if(game -> board[i][j] != rows_with_column_0) {
                    all_rows = 0;    // The entire row doesn't have the same symbols.
                    break;
                }
            }

            if (all_rows) {
                return rows_with_column_0;
            }
        }
    }

    //Checking column
    for (int x = 0; x < size; x++) {
        char row_0_with_columns = game -> board[0][x];

        if(row_0_with_columns != ' ') {
            int all_columns = 1;

            for (int y = 1; y < size; y++) {
                if(game -> board[x][y] != row_0_with_columns) {
                    all_columns = 0;
                    break;
                }
            }
            if (all_columns) {
                return row_0_with_columns;
            }
        }
    }

    //Checking first diagonal.
    //Diagonal with the same index(from left top to right bottom)
    char row_0_and_column_0 = game -> board[0][0];

    if (row_0_and_column_0 != ' ') {
        int all_diagonal_1 = 1;

        for (int p = 1; p < size; p++) {
            if (game -> board[p][p] != row_0_and_column_0) {
                all_diagonal_1 = 0;
                break;
            }
        }

        if (all_diagonal_1) {
            return row_0_and_column_0;
        }
    }

    //Checking second diagonal.
    //Diagonal from right top to left bottom.
    char row_0_and_end_column = game -> board[0][size-1];

    if(row_0_and_end_column != ' ') {
        int all_diagonal_2 = 1;

        for (int q = 1; q < size; q++) {
            if(game -> board[q][size-q-1] != row_0_and_end_column) {
                all_diagonal_2 = 0;
                break;
            }
        }

        if (all_diagonal_2) {
            return row_0_and_end_column;
        }
    }


    return ' ';
}

// Freeing the memory allocated for the game.
void free_game(Game *game) {

    for(int i = 0; i < game -> game_size; i++) {
        free(game -> board[i]);
    }

    free(game-> board);


    free(game -> players_moves);

    free(game);
}