#ifndef GAME_H
#define GAME_H

typedef enum {
    X_TURN,
    O_TURN,
    DRAW,
    X_WIN,
    O_WIN
} GameState;

typedef struct {
    unsigned char row;
    unsigned char col;
} Square;

typedef struct {
    char** _board;
    Square* _moves;
    char _move_count;
    GameState _state;
} Game;

Game* create_game();
const char** game_board(const Game* game);
GameState game_state(const Game* game);
const Square* game_moves(const Game* game, char* move_count);
char game_play(Game* game, const Square square);
void destroy_game(Game* game);

char game_state_running(const GameState game_state);

Square create_square(const unsigned char row, const unsigned char col);

GameState _calculate_game_state(const Game* game);

#endif
