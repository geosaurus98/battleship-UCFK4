/**
    @file setup.c
    @author Daniel Cayford & George Johnson
    @date 15 October 2024
    @brief Setting up boats support
**/

#include "setup.h"

/**
Initialises the game setup and manages boat placement
**/

void set_up(int* boat_layout) {
    // Initialises display with 1 second refresh rate
    tinygl_init(1000);
    // Define boats to include in game with size in setup.h
    int8_t boats[4] = {BOAT_L, BOAT_M, BOAT_S};

    // Loop through each boat and handle placement
    for (uint8_t i = 0; i < NUM_BOATS; i++) {
        int placed = 0; // Track if boat is placed
        uint8_t current_boat = boats[i]; // Get boat size

        // Initialise starting point for boat
        Ships_t points = boat_size(current_boat);

        // Draw line representing boat on matrix, 1 represents light on
        tinygl_draw_line(points.start, points.end, 1);

        // Loop until boat is placed
        while (placed != 1) {
            pacer_wait();
            points = boat_movement(points, boat_layout, &placed, current_boat); // Controlling Boat with Joystick
            display_boats(boat_layout); // Update Boat layout
            tinygl_update(); // refresh display
        }
    }
}

/**
Initializes coordinates for ship.

returns Ships_t Struct with start and end points of ship.
*/

Ships_t ships_init(int8_t start_x, int8_t end_x, int8_t start_y, int8_t end_y) {
    Ships_t points;
    points.start.x = start_x;
    points.end.x = end_x;
    points.start.y = start_y;
    points.end.y = end_y;
    return points;
}

/**
Rotates boat between vert and horizontal

returns Ships_t Struct updated start and end points
*/

Ships_t rotate(Ships_t points, uint8_t current_boat) {
    tinygl_clear(); // Clear display


    // If boat vertical, switch to horizontal.
    if (points.start.x == points.end.x && points.start.x) {
        points.start.y = points.end.y;
        points.start.x -= (current_boat - 1);
    // If boat horizontal, switch to vertical.
    } else if (points.start.y == points.end.y) {
        points.start.x = points.end.x;
        points.start.y += (current_boat - 1);
    }

    tinygl_draw_line(points.start, points.end, 1); //Redraw Boat
    return points;
}

/**
Handles boat movement with joystick

returns Ships_t updated coordinates
*/
Ships_t boat_movement(Ships_t points, int* boat_layout, int* placed, uint8_t current_boat) {
    navswitch_update();
    button_init();
    tinygl_draw_line(points.start, points.end, 1);

    // Move boat up if possible
    if (navswitch_push_event_p(NAVSWITCH_NORTH) && points.start.y != 0 && points.end.y != 0) {
        tinygl_clear();
        points.start.y--;
        points.end.y--;
    }

    // Move boat down if possible
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && points.end.y != 6 && points.start.y != 6) {
        tinygl_clear();
        points.start.y++;
        points.end.y++;
    }

    // Move boat right if possible
    if (navswitch_push_event_p(NAVSWITCH_EAST) && points.end.x != X_MAX - 1) {
        tinygl_clear();
        points.start.x++;
        points.end.x++;
    }

    // Move boat left if possible
    if (navswitch_push_event_p(NAVSWITCH_WEST) && points.start.x != 0) {
        tinygl_clear();
        points.start.x--;
        points.end.x--;
    }

    button_update();
    // Confirm boat placement with button
    if (button_push_event_p(0)) {
        // Loop checking if ship placement is free
        for (int i = 0; i < X_MAX; i++) {
            for (int j = 0; j < Y_MAX; j++) {
                tinygl_point_t t_point = tinygl_point(i, j);
                if (*(boat_layout + (WIDTH * j) + i) != 1 && tinygl_pixel_get(t_point) == 1) {
                    *(boat_layout + (WIDTH * j) + i) = 1;
                    *placed = 1;
                }
            }
        }
    }

    // Rotate boat with joystick click
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        points = rotate(points, current_boat);
    }

    return points;
}

Ships_t boat_size(uint8_t current_boat) {
    int8_t start_x = 0;
    int8_t end_x = current_boat - 1;
    int8_t start_y = 0;
    int8_t end_y = 0;

    return ships_init(start_x, end_x, start_y, end_y);
}

void display_boats(int* boat_layout) {
    for (uint8_t i = 0; i < X_MAX; i++) {
        for (uint8_t j = 0; j < Y_MAX; j++) {
            if (*(boat_layout + (WIDTH * j) + i) == 1) {
                display_pixel_set(i, j, 1);
            }
        }
    }
    display_update();
}
