/**
    @file gameplay.c
    @author Daniel Cayford & George Johnson
    @date 15 October 2024
    @brief Logic controlling gameplay module
**/

#include "gameplay.h"

/**
Signals readiness for gameplay
*/
void ready_signal(void) {
    int ready = 0;
    int received = 0;

    while (ready == 0) {
        ir_uart_putc('1'); // Send ready signal
        received = ir_uart_getc(); // Wait for confirmation

        if (received == '1') {
            pacer_wait();
            ready = 1; // set ready state
        }
    }
}

/**
Determines whose turn it is
Returns if player 1 or 2
*/
int allocate_players(void) {
    tinygl_text(" ENCE260 BATTLESHIPS");

    while (1) {
        navswitch_update();
        tinygl_update();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            display_clear();
            tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
            tinygl_update();
            ir_uart_putc(GO); // Sends signal indicating player 1
            return 1;
        }

        if (ir_uart_read_ready_p() && ir_uart_getc() == GO) {
            display_clear();
            tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
            tinygl_update();
            return 0; // Assign as player 2
        }
    }
}

/**
Sends a point during gameplay
*/
void sending(int* x, int* y, char* character_matrix) {
    char character = *(character_matrix + (WIDTH * *y) + *x);
    ir_uart_putc(character); // Send to opponent
}

/**
Receives a point during gameplay
*/
void receiving(int* x, int* y, char* character_matrix, int* boat_layout, int* player) {
    char r_character = ir_uart_getc(); // Recieve from opponent

    // Update coordinates
    if (r_character >= FIRST_CHAR && r_character <= LAST_CHAR) {
        for (int j = 0; j < Y_MAX; j++) {
            for (int i = 0; i < X_MAX; i++) {
                if (*(character_matrix + (WIDTH * j) + i) == r_character) {
                    *x = i;
                    *y = j;
                }
            }
        }
    }

    if (*(boat_layout + (WIDTH * *y) + *x) == 1) {
        ir_uart_putc(HIT); // Notify Hit
        *(boat_layout + (WIDTH * *y) + *x) = 0;
        tinygl_clear();
    } else {
        ir_uart_putc(MISS); // Notify Miss
    }
    *player = 1; // Switch turns
}

/**
Updates the game board based on input
*/
void update_board(int x, int y, int* shot_board) {
    *(shot_board + (WIDTH * y) + x) = 1; // Mark Shot on board
}

/**
Handles cursor movement in the game
*/
void cursor_movement(int* x, int* y) {
    // Move Up
    if (navswitch_push_event_p(NAVSWITCH_NORTH) && *y != 0) {
        tinygl_draw_point(tinygl_point(*x, *y), 0);
        *y -= 1;
    }
    // Move down
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && *y != 6) {
        tinygl_draw_point(tinygl_point(*x, *y), 0);
        *y += 1;
    }

    // Move Right
    if (navswitch_push_event_p(NAVSWITCH_EAST) && *x != 4) {
        tinygl_draw_point(tinygl_point(*x, *y), 0);
        *x += 1;
    }

    // Move Left
    if (navswitch_push_event_p(NAVSWITCH_WEST) && *x != 0) {
        tinygl_draw_point(tinygl_point(*x, *y), 0);
        *x -= 1;
    }
}
