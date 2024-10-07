#pragma once
/*
 - Define basic screen structures
 - Need row min and max, and col min and max
 - Center needed for starting robot
 - ECED 3401
 - 3 Oct 2024
*/

typedef struct scr_coord
{
int col;
int row;
}SCR_COORD;

typedef struct screen
{
SCR_COORD min;
SCR_COORD max;
SCR_COORD center;
} SCREEN;

extern SCREEN screen;

/* Entry points for functions */
extern int draw_object(int col, int row, int symbol);
extern void print_msg(char* msg);
extern void screen_init();
