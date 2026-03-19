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
- con la función `newwin` se modifica el tamaño de la ventana indicando alto, anchoh, inicio de y, inicio de x

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
