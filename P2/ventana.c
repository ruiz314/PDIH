// 
// gcc ventana.c -o ventana -lncurses
// 

#include <stdlib.h>
#include <ncurses.h>

int main(void) {
    int rows, cols;

    initscr();

    if (has_colors() == FALSE) { // Comprobar soporte de color
    	endwin();
    	printf("Your terminal does not support color\n");
    	exit(1);
	}

    start_color(); // Activar soporte color
    
    // Crear combinación de colores
    init_pair(1, COLOR_YELLOW, COLOR_GREEN); // Texto amarillo, fondo verde
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3,COLOR_WHITE,COLOR_BLUE);
    clear();

    refresh();
    getmaxyx(stdscr, rows, cols); 

    WINDOW *window = newwin(rows,cols,0,0); // Crea una ventana del tamaño de la terminal
    wbkgd(window, COLOR_PAIR(3));
    box(window, '|', '-'); // Dibuja el marco de la ventana

    mvwprintw(window, 10, 10, "una cadena");
    wrefresh(window);

    getch(); 
    endwin();
    return 0;
}
