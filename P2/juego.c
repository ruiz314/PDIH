#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 45000          // Velocidad de la pelota
#define LONGITUD_PALA 5      // Altura de las palas
#define PUNTOS_PARA_GANAR 5  // Puntos necesarios para ganar la partida

/* Juego pong con pantalla de inicio y pantalla de fin. */
// Funcion de pantalla de bienvenida
void pantalla_bienvenida(int max_y, int max_x){
    nodelay(stdscr, FALSE); // Para que getch() espere la pulsacion de una tecla
    clear();

    // Dibujar marco de presentacion
    attron(COLOR_PAIR(4));
    for(int i = 0; i < max_x; i++) { // Techo y suelo
        mvprintw(0, i, "-"); mvprintw(max_y - 1, i, "-"); 
    }
    for(int i = 0; i < max_y; i++) { // Paredes
         mvprintw(i, 0, "|"); mvprintw(i, max_x - 1, "|"); 
    }
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(3));
    mvprintw(max_y/2 - 5, max_x/2 - 6, "JUEGO PONG");
    attroff(COLOR_PAIR(3));
        
    mvprintw(max_y/2 - 3, max_x/2 - 15, "Autora: Ines Ruiz Sanchez");
    mvprintw(max_y/2 - 1, max_x/2 - 20, "J1 (Pala Izquierda): W (Arriba) / S (Abajo)");
    mvprintw(max_y/2 + 1, max_x/2 - 20, "J2 (Pala Derecha): Flecha Arriba / Abajo");
    mvprintw(max_y/2 + 4, max_x/2 - 18, "Pulsa cualquier tecla para empezar ...");
        
    refresh();
    getch(); // Esperar tecla
}

// Funcion de pantalla de finalizacion
int pantalla_final(int max_y, int max_x, int ganador, int puntos_j1, int puntos_j2)
    nodelay(stdscr, FALSE); // sperar a que el usuario responda
    clear();

    // Marco de la pantalla final
    attron(COLOR_PAIR(4));
    for(int i = 0; i < max_x; i++) { mvprintw(0, i, "-"); mvprintw(max_y - 1, i, "-"); } // Techo y suelo
    for(int i = 0; i < max_y; i++) { mvprintw(i, 0, "|"); mvprintw(i, max_x - 1, "|"); } // Paredes
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(3));
    mvprintw(max_y/2 - 4, max_x/2 - 8, "Fin del juego");
    attroff(COLOR_PAIR(3));

    if (ganador == 1) {
        mvprintw(max_y/2 - 2, max_x/2 - 15, "Felicidades Jugador 1, has ganado!");
    } else if (ganador == 2) {
        mvprintw(max_y/2 - 2, max_x/2 - 15, "Felicidades Jugador 2, has ganado!");
    } else {
        mvprintw(max_y/2 - 2, max_x/2 - 10, "Partida cancelada");
    }

    mvprintw(max_y/2, max_x/2 - 15, "Marcador Final");
    mvprintw(max_y/2, max_x/2 - 16, "J1: %d puntos |  J2: %d puntos", puntos_j1, puntos_j2);
    mvprintw(max_y/2 + 3, max_x/2 - 17, "Pulsa S para volver a jugar y N para terminar. ");
    refresh();

    // Captar respuesta
    int respuesta;
    while(1) {
        respuesta = getch();
        if (respuesta == 'n' || respuesta == 'N' || respuesta == 'q' || respuesta == 'Q') {
            return 0;
        } else if (respuesta == 's' || respuesta == 'S') {
            return 1;
        }
    }
}

int main(int argc, char *argv[]) {
    // Dimensiones del tablero fijo
    int max_y = 30, max_x = 60;
    
    int jugar_de_nuevo = 1;

    // Inicializar entorno de ncurses
    initscr();
    start_color(); // Activar soporte de color
    cbreak();
    noecho(); // Para no mostrar por pantalla las teclas que se pulsan
    keypad(stdscr, TRUE); // Para detectar las flechas de direccion
    curs_set(FALSE); // Ocultar el cursor

    // Configurar los colores
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    // Bucle principal (Permite volver a jugar al terminar una partida)
    while (jugar_de_nuevo) {

        // Pantalla de bienvenida
        pantalla_bienvenida(max_y, max_x);

        // Variables del juego
        int pelota_x = max_x / 2;
        int pelota_y = max_y / 2;
        int dir_x = 1;
        int dir_y = 1;

        // Posicion de las palas
        int pala_izq_y = (max_y / 2) - (LONGITUD_PALA / 2); // Pala izq
        int pala_der_y = (max_y / 2) - (LONGITUD_PALA / 2); // Pala der

        // Puntuacion
        int puntos_j1 = 0;
        int puntos_j2 = 0;
        int ganador = 0; // 0 = Ninguno, 1 = J1, 2 = J2

        // Modo no bloqueante para el juego
        nodelay(stdscr, TRUE); 

        // Logica del juego
        while (1) {
            // Leer entrada del teclado
            int tecla = getch();

            // Jugador 1 (W/S)
            if((tecla == 'w' || tecla == 'W') && (pala_izq_y > 1)){ pala_izq_y--; }
            if((tecla == 's' || tecla == 'S') && (pala_izq_y < max_y - LONGITUD_PALA - 1)){ pala_izq_y++; }

            // Jugador 2 (Flechas)
            if((tecla == KEY_UP) && (pala_der_y > 1)){ pala_der_y--; }
            if((tecla == KEY_DOWN) && (pala_der_y < max_y - LONGITUD_PALA - 1)){ pala_der_y++; }

            // Salir del juego
            if(tecla == 'q' || tecla == 'Q'){ break; }

            // Actualizar posicion de la pelota
            pelota_x += dir_x;
            pelota_y += dir_y;

            // Colisiones
            // Rebote en techo y suelo
            if(pelota_y <= 1 || pelota_y >= max_y - 2){
                dir_y *= -1;
            }
            
            // Rebote en pala izquierda
            if (pelota_x == 3 && pelota_y >= pala_izq_y && pelota_y < pala_izq_y + LONGITUD_PALA) {
                dir_x *= -1;
            } 
            // Rebote en pala derecha
            else if (pelota_x == max_x - 4 && pelota_y >= pala_der_y && pelota_y < pala_der_y + LONGITUD_PALA) {
                dir_x *= -1;
            }

            // Puntuacion
            if (pelota_x <= 0) { // Punto para el ugador 2
                puntos_j2++;
                pelota_x = max_x / 2; pelota_y = max_y / 2; 
                dir_x = 1; 
                if (puntos_j2 >= PUNTOS_PARA_GANAR) { ganador = 2; break; }
            } else if (pelota_x >= max_x - 1) { // Punto ppara jugador 1
                puntos_j1++;
                pelota_x = max_x / 2; pelota_y = max_y / 2; 
                dir_x = -1;
                if (puntos_j1 >= PUNTOS_PARA_GANAR) { ganador = 1; break; }
            }

            // Dibujar
            clear();

            // Marco
            attron(COLOR_PAIR(4));
            for(int i = 0; i < max_x; i++) { mvprintw(0, i, "-"); mvprintw(max_y - 1, i, "-"); } // Techo
            for(int i = 0; i < max_y; i++) { mvprintw(i, 0, "|"); mvprintw(i, max_x - 1, "|"); } // Paredes
            for(int i = 1; i < max_y - 1; i++) { mvprintw(i, max_x/2, "|"); } // Red del centro
            attroff(COLOR_PAIR(4));

            // Marcador
            attron(COLOR_PAIR(3));
            mvprintw(1, max_x/2 - 15, " Jugador 1: %d ", puntos_j1);
            mvprintw(1, max_x/2 +  2, " Jugador 2: %d ", puntos_j2);
            attroff(COLOR_PAIR(3));

            // Palas
            attron(COLOR_PAIR(2));
            for(int i = 0; i < LONGITUD_PALA; i++) {
                mvprintw(pala_izq_y + i, 2, "#");
                mvprintw(pala_der_y + i, max_x - 3, "#");
            }
            attroff(COLOR_PAIR(2));

            // Pelota
            attron(COLOR_PAIR(1));
            mvprintw(pelota_y, pelota_x, "o");
            attroff(COLOR_PAIR(1));

            refresh();
            usleep(DELAY);
        }

        // Pantalla final
        jugar_de_nuevo = pantalla_final(max_y, max_x, ganador, puntos_j1, puntos_j2);
    }

    // Finalizar
    endwin();
    return 0;
}
