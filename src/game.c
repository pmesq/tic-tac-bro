#include "game.h"

#include <stdlib.h>

Game* create_game() {
    char i, j;
    Game* game = (Game*) malloc(sizeof(Game));
    game->_board = (char**) malloc(3 * sizeof(char*));
    for (i = 0; i < 3; i++) {
        game->_board[i] = (char*) malloc(3 * sizeof(char));
        for (j = 0; j < 3; j++) {
            game->_board[i][j] = ' ';
        }
    }
    game->_moves = NULL;
    game->_move_count = 0;
    game->_state = X_TURN;
    return game;
}

const char** game_board(const Game* game) {
    return (const char**) game->_board;
}

GameState game_state(const Game* game) {
    return game->_state;
}

const Square* game_moves(const Game* game, char* move_count) {
    *move_count = game->_move_count;
    return game->_moves;
}

char game_play(Game* game, const Square square) {
    if (!game_state_running(game->_state)) return -1;
    const unsigned char row = square.row, col = square.col;
    if (row >= 3 || col >= 3 || game->_board[row][col] != ' ') return -1;
    game->_board[row][col] = game->_state == X_TURN ? 'X' : 'O';
    game->_moves = (Square*) realloc(
        game->_moves,
        ++(game->_move_count) * sizeof(Square)
    );
    game->_moves[game->_move_count - 1] = square;
    game->_state = _calculate_game_state(game);
    return 0;
}

void destroy_game(Game* game) {
    char i;
    for (i = 0; i < 3; i++) {
        free(game->_board[i]);
    }
    free(game->_board);
    free(game->_moves);
    free(game);
}

char game_state_running(const GameState game_state) {
    return game_state <= 1;
}

Square create_square(const unsigned char row, const unsigned char col) {
    Square square;
    square.row = row;
    square.col = col;
    return square;
}

GameState _calculate_game_state(const Game* game) {
    const Square square = game->_moves[game->_move_count - 1];
    const unsigned char row = square.row, col = square.col;
    const char symbol = game->_board[row][col];
    if (
        game->_board[row][0] == symbol &&
        game->_board[row][1] == symbol &&
        game->_board[row][2] == symbol ||
        game->_board[0][col] == symbol &&
        game->_board[1][col] == symbol &&
        game->_board[2][col] == symbol ||
        game->_board[1][1] == symbol &&
        (
            game->_board[0][0] == symbol &&
            game->_board[2][2] == symbol ||
            game->_board[0][2] == symbol &&
            game->_board[2][0] == symbol
        )
    ) return symbol == 'X' ? X_WIN : O_WIN;
    if (game->_move_count == 9) return DRAW;
    return symbol == 'X' ? O_TURN : X_TURN;
}

/**
 * Fato divertido:
 * escrevi esse código aí em uma noite,
 * depois de meses sem pôr a mão em qualquer projeto.
 * Então, se achar que está ruim, talvez eu concorde.
 *
 * Sinceramente, nem eu sabia que eu ainda conseguia
 * manipular tanto ponteiro, após anos sem mexer com
 * alocação dinâmica...
 * Malloc não me deixa malluco mais.
 *
 * Fiquei em dúvida sobre como nomear o tipo da casa:
 * Square ou Homie? Acabei por escolher a nomenclatura
 * mais formal.
 */
