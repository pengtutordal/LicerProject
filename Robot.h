#pragma once
/* 
 - Basic robot structure and entry points
 - ECED 3401
 -  3 Oct 24 - Original
*/

struct robot
{
int x;
int y;
int curr_dir;	/* Current direction N, S, E, W */
/* Restore things if overshoot */
int oldx;
int oldy;
int old_dir;
};

typedef struct robot ROBOT;

extern void robot_init();
extern void robot_move(char);

/* In system.c: */
extern void go_robot_go();
