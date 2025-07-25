/**
    @file game.c
    @author Daniel Cayford & George Johnson
    @date 15 October 2024
    @brief Game module - main control
**/

#include "setup.h"
#include "gameplay.h"
#include "screen.h"

// Reset Game after completed
void reset_game(int* x, int* y, int boat_layout[7][5], int shot_board[7][5], int* player, int* count) {
    // Reset Coordinates
    *x = *y = 0;
    *count = 0;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            boat_layout[i][j] = 0;
            shot_board[i][j] = 0;
        }
    }

    *player = allocate_players();
    set_up((int*)boat_layout);
    ready_signal();
    display_clear();
}

int main(void) {
    int x = 0;
    int y = 0;

    int boat_layout[7][5] = { {0} };
    int shot_board[7][5] = { {0} };

    char character_matrix[7][5] = {
        {'6', '7', '8', '9', ':'},
        {';', '<', '=', '>', '?'},
        {'@', 'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H', 'I'},
        {'J', 'K', 'L', 'M', 'N'},
        {'O', 'P', 'Q', 'R', 'S'},
        {'T', 'U', 'V', 'W', 'X'}
    };

    // Inititalise System
    system_init();
    pacer_init(PACER_RATE);
    display_init();
    ir_uart_init();
    inititalise_tinygl();
    navswitch_init();

    int count = 0;
    int player = allocate_players();

    set_up((int*)boat_layout);
    ready_signal();
    display_clear();

    while (1) {
        display_shots(shot_board);
        pacer_wait();
        tinygl_update();
        navswitch_update();

        // Player 1's Turn
        if (player == 1) {
            if (ir_uart_read_ready_p() && ir_uart_getc() == 'l') {
                loser_display();
            }

            tinygl_draw_point(tinygl_point(x, y), 1);
            cursor_movement(&x, &y);

            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                sending(&x, &y, (char*)character_matrix);
                player = 2;
            }
        }

        // Player 2's Turn
        if (ir_uart_read_ready_p() && player == 2) {
            char shot = ir_uart_getc();

            if (shot == HIT) {
                update_board(x, y, (int*)shot_board);
                process_shot(shot_board, x, y, &count);
                player = 0;
            } else if (shot == MISS) {
                process_shot(shot_board, x, y, &count);
                player = 0;
            }
        }

        // Waiting for Confirmation
        if (player == 0) {
            if (ir_uart_read_ready_p()) {
                receiving(&x, &y, (char*)character_matrix, (int*)boat_layout, &player);
            }
        }

        winner_display(&count); // Check for a winner

        // Reset game if all hits are made
        if (navswitch_push_event_p(NAVSWITCH_PUSH) && *count == TOTAL_HITS) {
            reset_game(&x, &y, boat_layout, shot_board, &player, &count);
        }

    }
}
