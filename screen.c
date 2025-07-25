/**
    @file screen.c
    @author Daniel Cayford & George Johnson
    @date 15 October 2024
    @brief LED MATRIX SCREEN Control
**/

#include "screen.h"

// Initialise tinygl for Matrix
void inititalise_tinygl(void)
{
    tinygl_init(1750); // Set refresh rate
    tinygl_font_set(&font5x5_1); // Set font
    tinygl_text_speed_set(MESSAGE_RATE); // Set Speed text scrolls
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL); // Set to scroll mode
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE); // Set to rotate text direction
}

/**
Processes a shot on the opponent's board.
**/
void process_shot(int matrix[7][5], int x, int y, int* count)
{
    int (*ptr)[5] = matrix; // Update matrix with pointer
    tinygl_clear();

    if (matrix[y][x] == 1) // Hit detected
    {
        (*count)++;
        tinygl_text("H");
    }
    else if (matrix[y][x] == 0) // Miss
    {
        tinygl_text("M");
        ptr[y][x] = 2;
    }

    for (int i = 0; i < 2000; i++) // Display result
    {
        pacer_wait();
        tinygl_update();
    }

    tinygl_clear(); // Reset screen
}

/**
 Shows hits and misses on the matrix with blinking.
**/
void display_shots(int shot_board[7][5])
{
    int x = 0;
    int y = 0;

    static int blink_timer = 0; // Blink Timer
    static int led_state = 0; // LED state

    for (x = 0; x < X_MAX; x++)
    {
        for (y = 0; y < Y_MAX; y++)
        {
            if (shot_board[y][x] == 1)
            {
                if (blink_timer == BLINKING)
                {
                    tinygl_draw_point(tinygl_point(x, y), led_state); // Toggle Hit
                }
            }
            else if (shot_board[y][x] == 2)
            {
                tinygl_draw_point(tinygl_point(x, y), 1); // Miss LED
            }
        }
    }

    if (blink_timer == BLINKING)
    {
        blink_timer = 0;
        led_state = !led_state; // Toggle led_state
    }

    tinygl_update(); // Refresh Display
    blink_timer++;
}

/**
 Display winner
**/
void winner_display(int* count)
{
    if (*count == TOTAL_HITS)
    {
        tinygl_clear();
        tinygl_text("WINNER");
        ir_uart_putc(LOSE); // Notify opponent of loss

        while (*count == TOTAL_HITS) // Continue till reset
        {
            pacer_wait();
            tinygl_update();
        }
    }
}

/**
 Display Loser
**/
void loser_display(void)
{
    tinygl_clear();
    tinygl_text("LOSER");

    while (1)
    {
        pacer_wait();
        tinygl_update();
    }
}
