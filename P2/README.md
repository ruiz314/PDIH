# Práctica 2. Uso de bibliotecas de programación de interfaces de usuario en modo texto

## Cuestiones a resolver 
El objetivo principal es conocer cómo utilizar la librería ncurses para realizar entrada/salida en terminales de texto bajo Linux. 

Como **requisitos mínimos** se deben realizar y documentar adecuadamente las siguientes tareas:  
1. Instalar la librería ncurses, crear los programas de ejemplo ofrecidos (ej1, ej2 y ej3), y comprobar su funcionamiento.
2. Crear un juego sencillo tipo “pong” partiendo del ejemplo del movimiento de la pelotita.  

Como **requisitos ampliados** (opcionales para subir nota) se propone: 

1. que al iniciar el juego se muestre una pantalla de bienvenida en la que se muestren los datos de quienes han realizado el juego y explicando los controles de juego (p.ej. un recuadro con la explicación). Tras una pausa o pulsación de tecla se iniciará el juego en sí mismo.
2. que al terminar cada partida se muestre una pantalla de resumen mostrando el marcador final y felicitando al ganador. Se dará la opción de volver a jugar o terminar el programa. 

## Instalación 
Esta práctica se realiza en una máquina virtual con Ubuntu 22.

Instalar la librería necesaria: 

```bash
sudo apt-get update
sudo apt-get install libncurses5-dev libncursesw5-dev 
```

![1instalacion.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/1instalacion.png)

Pulsamos la tecla S para continuar.

![1instalacion2.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/1instalacion2.png)

Instalación terminada satisfactoriamente.

## ej1 - Hola mundo

Ejemplo proporcionado por el profesor:

```c 
#include <ncurses.h>
#include <stdio.h>
int main() {
	initscr(); // Reserva memoria para la ventana principal
	printw("Hello World!"); // Lo escribe en la memoria
	refresh(); // Pasa lo que hay en memoria a la pantalla para que se vea
	getch();
	endwin(); // Cierra el modo ncurses
	return 0;
}
```

Orden para compilar: 

```bash
gcc hello.c -o hello -lncurses 
```

El fichero completo: [hello.c](https://github.com/ruiz314/PDIH/blob/main/P2/hello.c)

Ejecución:

![2hello2.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/2hello2.png)

## ej2 - Ventana

Se trata del fichero [ventana.c](https://github.com/ruiz314/PDIH/blob/main/P2/ventana.c)

```c
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
    box(window, '|', '-'); // Dibuja el marco de la ventana (WINDOW, caracter vertical, caracter horizontal)

    mvwprintw(window, 10, 10, "una cadena");
    wrefresh(window);

    getch(); 
    endwin();
    return 0;
}
```

![3ventana.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/3ventana.png)

Compilar con la orden:

```bash
gcc ventana.c -o ventana -lncurses
```

![3ventana2.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/3ventana2.png)

Ejecución:

![3ventana3.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/3ventana3.png)

Una modificación de ese ejemplo sería: [ventanaModif.c](https://github.com/ruiz314/PDIH/blob/main/P2/ventanaModif.c)

Las líneas que se han cambiado con respecto al fichero inicial son:

```c
	//getmaxyx(stdscr, rows, cols); 
    rows=10;
    cols=40;

    WINDOW *window = newwin(rows,cols,5,10); // Modificación del tamaño
    wbkgd(window, COLOR_PAIR(1)); // Cambio de colores: amarillo y verde
    box(window, '*', '*'); // Modificación de marco
```

Ejecución:

![4ventanaM2.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/4ventanaM2.png)

Se pueden observar los cambios:
- con la función `box` se cambian los caracteres para el marco: `*`
- con la función `wbkgd` se cambia el color de la ventana: verde para el fondo y amarillo para los caracteres
- con la función `newwin` se modifica el tamaño de la ventana indicando alto, ancho, inicio de y, inicio de x

## ej3 - Pelota

Fichero: [pelotita.c](https://github.com/ruiz314/PDIH/blob/main/P2/pelotita.c)

```c
#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main(int argc, char *argv[]) {
 int x = 0, y = 0;
 int max_y = 20, max_x = 20;
 int next_x = 0;
 int direction = 1;

 initscr();
 noecho(); // Para no mostrar por pantalla las teclas que se pulsan
 curs_set(FALSE); // Ocultar el cursor

 while(1) {
 	clear();
 	mvprintw(y, x, "o");
 	refresh();

 	usleep(DELAY); // Pausa para que nos de tiempo a ver la pelota

 	next_x = x + direction;

 	if (next_x >= max_x || next_x < 0) {
 		direction*= -1;
 	} else {
 		x+= direction;
 	}
 }

 endwin();
}
```

Compilar:

```bash
gcc pelotita.c -o pelotita -lncurses
```

Ejecución:

![5pelotita.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/5pelotita.png)


## Juego sencillo tipo “pong”
Fichero: [pelotita.c](https://github.com/ruiz314/PDIH/blob/main/P2/pong.c)
```c
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
 kpad(stdscr, TRUE);
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
 int pala_der_y = (max_x /2) - (LONGITUD_PALA /2);

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
        if(pala_derq_y > 1){
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
```
## Pantalla de inicio

## Pantalla resumen

## Memoria en LATEX
Link a la memoria que se incluye en este repositorio: [memoria](https://www.overleaf.com/read/tmtzspkbsdxt#9ac420)
