/**
    @file setup.h
    @author Daniel Cayford & George Johnson
    @date 15 October 2024
    @brief Setting up boats support
**/


#ifndef SETUP_H
#define SETUP_H

#include "tinygl.h"
#include "button.h"
#include "pacer.h"
#include "gameplay.h"

#define NUM_BOATS 3
#define BOAT_S 2
#define BOAT_M 3
#define BOAT_L 4

//Initializes where the start and end points of the ships are
typedef struct {
    tinygl_point_t start;
    tinygl_point_t end;
} Ships_t;

Ships_t ships_init(int8_t, int8_t, int8_t, int8_t); // Initializes the ships

Ships_t rotate(Ships_t, uint8_t); //Rotates the orientation of the ships when navswitch is pressed

Ships_t boat_movement(Ships_t , int* , int*, uint8_t); // controlls the movement/placement of the ships

Ships_t boat_size(uint8_t i); //Setups the size

void display_boats(int*); //Displays the ships

void set_up(int*); //Main stup loop runs until all ships are placed




#endif
