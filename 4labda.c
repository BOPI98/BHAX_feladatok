#include <stdio.h>
#include <curses.h>
#include <unistd.h>
int main(void)
{
WINDOW *ablak;
    ablak = initscr ();

    int x = 0,y = 0;
    int xnov = 1,ynov = 1;
    int mx,my,sarok=0;

    for ( ;; ) {

        getmaxyx ( ablak, my , mx );

        mvprintw ( y, x, "O" );

        refresh ();
        usleep ( 50000 );

	clear();

        x = x + xnov;
        y = y + ynov;

        if ( x>=mx-1 )
	{
            xnov = xnov * -1;
        }
        if ( x<=0 ) {
            xnov = xnov * -1;
        }
        if ( y<=0 ) {
            ynov = ynov * -1;
        }
        if ( y>=my-1 )
	{
            ynov = ynov * -1;
        }
	if((x<=0 && y<=0) || (x>=mx-1 && y>=my-1) || (x<=0 && y>=my) || (x>=mx && y<=0)) sarok++;

	mvprintw(my-1,1,"SAROK HIT: %i",sarok);
    }

return 0;
}
