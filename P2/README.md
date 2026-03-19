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

Para instalar la librería en Linux sólo tenemos que usar el sistema de gestión de paquetes correspondiente para Ubuntu: 
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev 
```

![1instalacion.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/1instalacion.png)

Pulsamos la tecla S para continuar.

![1instalacion2.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/1instalacion2.png)

## ej1 

Ejemplo proporcionado por el profesor y compilado con:

```bash
gcc hello.c -o hello -lncurses 
```

![2hello.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/2hello.png)

El fichero completo: [hello.c](https://github.com/ruiz314/PDIH/blob/main/P2/hello.c)

Ejecución:

![2hello2.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/2hello2.png)

## ej2

Se trata del fichero [ventana.c](https://github.com/ruiz314/PDIH/blob/main/P2/ventana.c)

![3ventana.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/3ventana.png)

Compilar con la orden:

```bash
gcc ventana.c -o ventana -lncurses
```

![3ventana2.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/3ventana2.png)

Ejecución:

![3ventana3.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/3ventana3.png)

Una modificación de ese ejemplo sería: [ventanaModif.c](https://github.com/ruiz314/PDIH/blob/main/P2/ventanaModif.c)

Las lñineas que se han cambiado con respecto al fichero inicial son:

```c
WINDOW *window = newwin(rows,cols,2,2); //Modificación
wbkgd(window, COLOR_PAIR(1)); // Cambio de colores: caracteres amarillos y fondo verde
box(window, '*', '*'); // Modificación de marco
```

![4ventanaM.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/4ventanaM.png)

Ejecución:

![4ventanaM2.png](https://github.com/ruiz314/PDIH/blob/main/P2/img/4ventanaM2.png)

Se pueden observar los cambios:
- color verde para el fondo y amarillo para los caracteres
- caracteres para el marco: `*`

## ej3

## Juego sencillo tipo “pong”
