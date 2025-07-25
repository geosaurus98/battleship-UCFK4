/**
    @file gameplay.h
    @author Daniel Cayford & George Johnson
    @date 15 October 2024
    @brief Logic controlling gameplay module
**/

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x5_1.h"
#include "setup.h"

#define HIT 'h'
#define MISS 'm'
#define GO 'g'
#define FIRST_CHAR '6'
#define LAST_CHAR 'X'
#define WIDTH 5
#define X_MAX 5
#define Y_MAX 7

// Order changed:
void ready_signal(void);         // Signals readiness for gameplay
int allocate_players(void);      // Determines whose turn it is
void sending(int*, int*, char*); // Sends a point during gameplay
void receiving(int*, int*, char*, int*, int*); // Receives a point during gameplay
void update_board(int, int, int*); // Updates the game board based on input
void cursor_movement(int*, int*);   // Handles cursor movement in the game

#endif
