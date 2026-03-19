// gcc hello.c -o hello -lncurses

#include <ncurses.h>
#include <stdio.h>
int main() {
	initscr(); // Reserva memoria para la ventana principal
	printw("Hello World!"); // Lo escribe en la memoria
	refresh(); // Pasa lo que hay en memoria a la pantalla para que se vea
	getch();
	endwin(); // Ciera el modo ncurses
	return 0;
}

