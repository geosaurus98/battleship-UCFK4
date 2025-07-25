/**
    @file screen.h
    @author Daniel Cayford & George Johnson
    @date 15 October 2024
    @brief LED MATRIX screen support
**/

#ifndef SCREEN_H
#define SCREEN_H

#include "system.h"
#include "tinygl.h"
#include "../fonts/font5x5_1.h"
#include "pacer.h"
#include "ir_uart.h"
#include "setup.h"

#define BLINKING 100
#define PACER_RATE 500
#define MESSAGE_RATE 10
#define X_MAX 5
#define Y_MAX 7
#define LOSE 'l'
#define TOTAL_HITS 9

void inititalise_tinygl(void); // Initialise tinygl for Matrix

void process_shot (int board[7][5], int x_cord, int y_cord, int* count); // Processes a shot on the opponent's board.

void display_shots(int board[7][5]); // Display Hits and misses

void winner_display(int*); // Display Winner

void loser_display(void); // Display Loser

#endif
