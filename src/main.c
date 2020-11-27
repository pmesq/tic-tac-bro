#include <stdio.h>
#include "game.h"
#include "bot/brandom.h"

#define PLAYER_TYPE_COUNT 2

typedef enum {
    HUMAN_USER,
    BOT_BRANDOM
} PlayerType;

Square (*bot_functions[])(const char**) = {
    brandom_bot
};

char is_human(const PlayerType player_type);
void print_line();
void print_player_options();
void print_board(const char** board);

int main() {
    unsigned player_types[2];

    puts("WELCOME TO TIC TAC TOE!");

    do {
        print_player_options();
        printf("Select first player (X): ");
        scanf("%u", &player_types[0]);
    } while(player_types[0] >= PLAYER_TYPE_COUNT);

    do {
        print_player_options();
        printf("Select second player (O): ");
        scanf("%u", &player_types[1]);
    } while(player_types[1] >= PLAYER_TYPE_COUNT);

    Game* game = create_game();

    GameState state = game_state(game);

    do {
        print_board(game_board(game));
        Square square;
        do {
            if (is_human(player_types[state])) {
                unsigned square_id;
                printf("Player %c plays: ", state == X_TURN ? 'X' : 'O');
                scanf("%u", &square_id);
                square_id--;
                square = create_square(square_id / 3, square_id % 3);
            } else {
                square = bot_functions[player_types[state] - 1](game_board(game));
            }
        } while(game_play(game, square));
        state = game_state(game);
    } while(game_state_running(state));

    print_board(game_board(game));

    if (state == X_WIN) puts("PLAYER X WIN!");
    else if (state == O_WIN) puts("PLAYER O WIN!");
    else puts("DRAW!");

    destroy_game(game);

    return 0;
}

char is_human(const PlayerType player_type) {
    return player_type == HUMAN_USER;
}

void print_line() {
    puts("===========================");
}

void print_player_options() {
    print_line();
    puts("0- [Human] User");
}

void print_board(const char** board) {
    char i;
    print_line();
    for (i = 0; i < 3; i++) {
        printf(
            "|%c|%c|%c|    |%d|%d|%d|\n",
            board[i][0],
            board[i][1],
            board[i][2],
            i * 3 + 1,
            i * 3 + 2,
            i * 3 + 3
        );
    }
}

/**
 * Impressão minha ou eu fiz polimorfismo ali no bot_functions?
 */
