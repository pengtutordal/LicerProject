/*
 - Reads kb
 - Decides on action:
	- Robot move
	- Screen move

 - ESC sequences:
	- [ + H - home
	- [ + A|B|C|D - U, D, L, R

 - ECED 3401
 -  3 Oct 2024 - Original

 - Source:
	- https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#input-sequences
*/
#include "VT100.h"
#include "robot.h"

void go_robot_go()
{
int done;
char ch;

done = FALSE;

while (!done)
{
	while (_kbhit() == 0); /* Busy wait */
	
	if ((char)_getch() == ESCAPE)
	{
		if ((char)_getch() == '[')
		{
			switch ((ch = (char)_getch()))
			{
			case 'H':
				done = TRUE;
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
				robot_move(ch);
				break;
			}
		}
	}
}

}