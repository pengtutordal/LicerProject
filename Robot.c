/*
 - Robot
	- robot_init - initialize robot to center of screen and draw starting symbol
	- robot_move - move the robot if possible

 - ECED 3401
 -  3 Oct 2024
*/

#include "VT100.h"
#include "screen.h"
#include "robot.h"

#define START_SYM	'*'

enum direction { NORTH, SOUTH, EAST, WEST, IDLE };

/* Tunnel symbol to display [new dir][old dir] */
char cell_sym[4][5] = {
/*	Old: NO  SO  ET  WT  IDL    New:*/
		{VR, VR, LR, LL, VR}, /* NO */
		{VR, VR, UR, UL, VR}, /* SO */
		{UL, LL, HR, HR, HR}, /* ET */
		{UR, LR, HR, HR, HR}  /* WT */
};

short del_y[] = { -1, 1, 0, 0 };
short del_x[] = { 0, 0, 1, -1 };

ROBOT mylice;

/* ASCII-to-DEC graphic characters */
enum symbol asc_dec[] = {
	'j', 'k', 'l', 'm', 'n', 'q', 't', 'u', 'v', 'w', 'x', ' ' };

void robot_init()
{
/*
 - Initialize robot to center of screen
 - Show robot at center of screen
*/
mylice.x = screen.center.col;
mylice.y = screen.center.row;
mylice.curr_dir = IDLE;

printf(CSI "%dm" CSI "%dm", BGYELLOW, FGBLACK);

draw_object(mylice.x, mylice.y, START_SYM);
}

void robot_move(char ch)
{
enum direction new_dir;
enum symbol new_off; /* Offset into asc_dec[] */
char new_sym;	/* Symbol from asc_dec[] */
int new_x;
int new_y;

/* DEC Keypad sequence (U, D, R, L) */
new_x = mylice.x + del_x[ch - 'A'];
new_y = mylice.y + del_y[ch - 'A'];

/* Should check for edge of world */

/* New direction? */
if (new_y < mylice.y)
	new_dir = NORTH;
else
if (new_y > mylice.y)
	new_dir = SOUTH;
else
if (new_x < mylice.x)
	new_dir = WEST;
else
	new_dir = EAST;

/* Get symbol offset */
new_off = cell_sym[new_dir][mylice.curr_dir];
new_sym = asc_dec[new_off];

/* Draw symbol if possible */

EDLDM /* Enable DEC line drawing mode */

if (draw_object(mylice.x, mylice.y, new_sym) == 0)
{
	/* Draw worked */
	/* Remember last valid position */
	mylice.oldx = mylice.x;
	mylice.oldy = mylice.y;
	mylice.old_dir = mylice.curr_dir; 
	mylice.curr_dir = new_dir;
	/* Possible overshoot to invalid position */
	mylice.x = new_x;
	mylice.y = new_y;
}
else
{
	/* Restore robot to last valid position */
	mylice.x = mylice.oldx;
	mylice.y = mylice.oldy;
	mylice.curr_dir = mylice.old_dir;
}

EAM /* Enable ASCII mode */
}