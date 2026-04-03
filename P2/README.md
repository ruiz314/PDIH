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
Para crear el juego partimos del fichero [pelotita.c](https://github.com/ruiz314/PDIH/blob/main/P2/pong.c), pero hay que añadirle las palas y la lógica de la puntuación. Los cambios han sido:
- Añadir movimiento en el Eje Y para la pelota.
```c
  int pelota_x = max_x /2;
  int pelota_y = max_y /2;
  int dir_x = 1;
  int dir_y = 1;
  ...
  pelota_x += dir_x ;
  pelota_y += dir_y ;
```

- Añadir las dos palas, solo con movimiento en Eje Y.
```c
        int pala_izq_y = ( max_y /2) - ( LONGITUD_PALA /2) ;
        int pala_der_y = ( max_y /2) - ( LONGITUD_PALA /2) ;
```

- Capturar las teclas de juego con la función `getch()`
```c
        int tecla = getch();
        if (tecla == 'w' || tecla == 'W')
            if (pala_izq_y > 0) pala_izq_y--; 
        if (tecla == 's' || tecla == 'S') 
            if(pala_izq_y < max_y - LONGITUD_PALA) pala_izq_y++;
        if (tecla == KEY_UP)
            if (pala_der_y > 0) pala_der_y--; 
        if (tecla == KEY_DOWN)
            if (pala_der_y < max_y - LONGITUD_PALA) pala_der_y++; 
```

El _jugador1_ (pala izquierda) usa las teclas `W` y `S` para mover su pala. El _jugador2_ (pala derecha) usa las teclas con flechas para mover su pala.

 - Marcador de puntos
```c
        int puntos_j1 = 0;
        int puntos_j2 = 0;
        ...
        if ( pelota_x <= 0) { // Punto para el jugador 2
            puntos_j2 ++;
            pelota_x = max_x / 2; pelota_y = max_y / 2;
            dir_x = 1;
        } else if ( pelota_x >= max_x - 1) { // Punto para el jugador 1
            puntos_j1 ++;
            pelota_x = max_x / 2; pelota_y = max_y / 2;
            dir_x = -1;
        }
```

Fichero: [pong.c](https://github.com/ruiz314/PDIH/blob/main/P2/pong.c)

Para compilar y ejecutar hay que usar las ordenes: 

```bash
gcc pong.c -o pong -lncurses
./pong
```

![6pong.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/6pong.png)

## Juego con pantallas
Fichero: [juego.c](https://github.com/ruiz314/PDIH/blob/main/P2/juego.c)

Para tener un código más limpio y estructurado he separado la lógica del juego del diseño de las pantallas. Es por eso que la creación de cada pantalla está en una función, que será llamada en el main.

Parto del código de fichero pong.c y realizo los siguientes cambios:
- Disminuir la velocidad de la pelota para que sea más asequible el juego. Esto se hace modificando la constante $DELAY$ $50000$ al principio del fichero.
- Establecer un máximo de puntos para ganar con una constante: _PUNTOS_PARA_GANAR_ 5.

### Pantalla de bienvenida

La función desactiva el modo continuo con $nodelay(stdscr, FALSE)$ para esperar a la pulsación de una tecla con `getch()`. Al pulsar cualquier tecla la función termina y devuelve el control al _main_, devolviendo _nodelay_ a $TRUE$ para iniciar el movimiento de la pelota.

```c
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
```

Ejecución:

![7juego_ini.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/7juego_ini.png)

## Pantalla resumen

La función recibe como argumentos las dimensiones de la pantalla ($max_y$, $max_x$), la puntuación de ambos jugadores y un entero identificando al ganador.

Además de mostrar la información, la función entra en un bucle infinito con `getch()` bloqueante para preguntar si el usuario quiere volver a jugar o parar (teclas 'S' o 'N'). Si el usuario pulsa 'S' la función devuelve $1$, Si el usuario pulsa 'N' devuelve $0$. Ese valor se tiene en cuenta en el bucle del _main_ `while(jugar_de_nuevo)` para reiniciar partida o salir del programa.

```c
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
```

Ejecución:

![8juego_fin.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/8juego_fin.png)

## Memoria en LATEX
Link a la memoria que se incluye en este repositorio: [memoria](https://www.overleaf.com/read/tmtzspkbsdxt#9ac420)
