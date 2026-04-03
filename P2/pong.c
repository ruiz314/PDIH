#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 50000 // Velocidad de la pelota
#define LONGITUD_PALA 5 // Altura de las palas

int main(int argc, char *argv[]) {
 // Dimensiones del tablero
 int max_y=30, max_x=60;

 // Inicializar entorno de ncurses
 initscr();
 start_color(); // Activar soporte de color
 cbreak();
 noecho(); // Para no mostrar por pantalla las teclas que se pulsan
 keypad(stdscr, TRUE);
 curs_set(FALSE); // Ocultar el cursor
 nodelay(stdscr, TRUE);

 // Configurar los colores
 init_pair(1, COLOR_WHITE, COLOR_BLACK);
 init_pair(2, COLOR_GREEN, COLOR_BLACK);
 init_pair(3, COLOR_YELLOW, COLOR_BLACK);
 init_pair(4, COLOR_CYAN, COLOR_BLACK);

 getmaxyx(stdscr, max_y, max_x); // Obtiene dimensiones dinamicamente

 // Variables del juego
 int pelota_x = max_x /2;
 int pelota_y = max_y /2;
 int dir_x = 1;
 int dir_y = 1;

 // Posicion de las palas
 int pala_izq_y = (max_y /2) - (LONGITUD_PALA /2);
 int pala_der_y = (max_y /2) - (LONGITUD_PALA /2);

 // Puntuacion
 int puntos_j1 = 0;
 int puntos_j2 = 0;
 
 while(1) {
    // Leer entrada de teclado
    int tecla = getch();

    // Jugador 1
    if(tecla == 'w' || tecla == 'W'){
        if(pala_izq_y > 1){
            pala_izq_y--;
        }
    }
    if(tecla == 's' || tecla == 'S'){
        if(pala_izq_y < max_y - LONGITUD_PALA -1){
            pala_izq_y++;
        }
    }

    // Jugador 2
    if(tecla == KEY_UP){
        if(pala_der_y > 1){
            pala_der_y--;
        }
    }
    if(tecla == KEY_DOWN){
        if(pala_der_y < max_y - LONGITUD_PALA -1){
            pala_der_y++;
        }
    }

    // Salir del juego
    if(tecla == 'q' || tecla == 'Q'){
        break;
    }

    // Actualizar posicion de la pelota
    pelota_x += dir_x;
    pelota_y += dir_y;

    // Colisiones
    // Rebote en techo y suelo
    if(pelota_y <=1 || pelota_y >= max_y -2){
        dir_y *= -1;
    }
    
 	// Rebote en la pala izquierda
    if (pelota_x == 3 && pelota_y >= pala_izq_y && pelota_y < pala_izq_y + LONGITUD_PALA) {
        dir_x *= -1;
    }
    
    // Rebote en la pala derecha
    else if (pelota_x == max_x - 4 && pelota_y >= pala_der_y && pelota_y < pala_der_y + LONGITUD_PALA) {
        dir_x *= -1;
    }

    // Puntuación
    if (pelota_x <= 0) { // Punto para el jugador 2
            puntos_j2++;
            pelota_x = max_x / 2; pelota_y = max_y / 2; 
            dir_x = 1; 
    } else if (pelota_x >= max_x - 1) { // Punto para el jugador 1
            puntos_j1++;
            pelota_x = max_x / 2; pelota_y = max_y / 2; 
            dir_x = -1;
    }

    // Dibujar los elementos en pantalla
        clear();

        // Marco
        attron(COLOR_PAIR(4));
        for(int i = 0; i < max_x; i++) {
            mvprintw(0, i, "-");          // Techo
            mvprintw(max_y - 1, i, "-");  // Suelo
        }
        for(int i = 0; i < max_y; i++) { // Paredes
            mvprintw(i, 0, "|");          // Pared izquierda
            mvprintw(i, max_x - 1, "|");  // Pared derecha
        }
        for(int i = 1; i < max_y - 1; i++) {// La red del centro
            mvprintw(i, max_x/2, "|");
        }
        attroff(COLOR_PAIR(4));

        // Marcador
        attron(COLOR_PAIR(3));
        mvprintw(1, max_x/2 - 15, " Jugador 1: %d ", puntos_j1);
        mvprintw(1, max_x/2 + 2, " Jugador 2: %d ", puntos_j2);
        attroff(COLOR_PAIR(3));

        // Palas
        attron(COLOR_PAIR(2));
        for(int i = 0; i < LONGITUD_PALA; i++) {
            mvprintw(pala_izq_y + i, 2, "#");         // Pala izquierda
            mvprintw(pala_der_y + i, max_x - 3, "#"); // Pala derecha
        }
        attroff(COLOR_PAIR(2));

        // Pelota
        attron(COLOR_PAIR(1));
        mvprintw(pelota_y, pelota_x, "o");
        attroff(COLOR_PAIR(1));
 	refresh();

 	usleep(DELAY); // Pausa para que nos de tiempo a ver la pelota

 }

 // Finalizar
 endwin();
 return 0;
}
