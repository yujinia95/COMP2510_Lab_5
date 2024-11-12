/**
* Author: Yujin Jeong
* Date: 12th Oct 2024
* Purpose: Making a Tic-Tac-TOE Game.
*/

#include <stdio.h>
#include <stdlib.h>
#include "tic_tac_toe.h" //declarations for the Tic_Tac_Toe game functions and structures.

int main(void) {
    char play_again = 'y';
    int draws = 0;

    while (play_again == 'y') {
        Game *game = init_game();
        int row, col;
        char winner = ' ';
        int move_count = 0;

        printf("***Welcome to Tic-Tac-Toe!***\n");
        printf("Enter your move as row and column numbers between 0, 1, 2.\n");

        //Main game loop.
        while (winner == ' ' && move_count < game -> game_size * game -> game_size) {
            display_board(game);

            // Determine which player is making the move.
            printf("Player %d, enter your move(row and column): ", game -> current_player + 1);

            // Get user input for row and column.
            scanf("%d %d", &row, &col);

            // Validate and make the move.
            if (!make_move(game, row, col)) {
                printf("Invalid move! Try again.\n");
                continue;
            }

            winner = check_winner(game); ;

            if (winner != ' ') {
                break;
            }

            move_count++;
        }

        // Announce the result and update win/loss statistics
        if (winner != ' ') {
            for (int i = 0; i < game -> num_players; i++) {
                if (winner == game -> user_unique_symbols[i]) {
                    printf("=== Player %d wins!===\n", i+1 );
                    game-> players_wins[i]++;
                    break;
                }
            }
        } else {
            printf("===Draw!===");
            draws++;
        }
        free_game(game);

        // Show current win/loss stats
        printf("\nCurrent Stats:\n");
        for (int j = 0; j < game -> num_players; j++) {
            printf("===The number of player%d won===: %d\n", j+1, game -> players_wins[j]);
        }
        printf("===Draws===: %d\n", draws);

        // Ask the user if they want to play again
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &play_again);
    }
    printf("Thanks for playing!\n");
    return 0;
}

