/*
   cc pruncurses.c -lncurses -o pruncurses
*/
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

WINDOW *win; /** manejaremos una única ventana de pantalla completa **/

main () {

	win=initscr(); /* Crea la ventana */
	clear();  /* Borra la pantalla entera bajo ncurses */
	refresh(); /* Actualiza la ventana con los cambios */
	noecho();
	cbreak();
	keypad(win, TRUE);

	move(7, 30); /* x , y */
	printw("Ctrl-C  para terminar");
	for(;;){
		move(12, 30); /* x , y */
		printw("%3d", getch());
        refresh();
	}

	refresh();
	endwin();
}
