#include "bot/brandom.h"

#include <stdlib.h>
#include <time.h>

Square brandom_bot(const char** board) {
    Square avl_squares[9];
    unsigned avl_squares_count = 0;
    char i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                avl_squares[avl_squares_count++] = create_square(i, j);
            }
        }
    }
    if (avl_squares_count == 0) return create_square(0, 0);
    srand(time(NULL));
    return avl_squares[rand() % avl_squares_count];
}

/**
 * BOT BRANDOM
 *
 * Criei este bot há 2 anos atrás no Rattt. Ele faz jogadas aleatórias...
 * Espero que eu não precise explicar seu nome.
 *
 * Hoje, ele também pode ser visto como uma singela homenagem a um amigo meu.
 * Quem sabe, sabe.
 *
 * Nota: avl_squares é uma abreviação para available squares (do inglês,
 * casas disponíveis).
 */
