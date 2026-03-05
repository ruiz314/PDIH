# Práctica 1. Entrada/Salida utilizando interrupciones con lenguaje C

## Requisitos mínimos

Realizar las siguientes 10 funciones, que deben diseñarse e implementarse de forma que se puedan reutilizar fácilmente en otros programas. El programa debe utilizar de todas esas funciones para comprobar su correcto funcionamiento. 

Hay una función genérica, dada por el profesor:
```c


void mi_pausa(){
	union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}
```

Además, se usan las cabeceras:
```c
#include <stdio.h>
#include <dos.h>
```

1. `gotoxy()`: coloca el cursor en una posición determinada.

```c
void xy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10,&inregs,&outregs);
	return;
}
```

Esta función es proporcionada por el profesor, pero para hacerla más dinámica en el main se solicita al usuario las coordenadas $x$ e $y$.

```c
int main(){
	int pos_x, pos_y; //Guardar posición determinada

	// Solicitar coordenadas
	printf("Introduce la posicion x (columna)");
	scanf("%d", &pos_x);
	printf("Introduce la posicion y (fila)");
	scanf("%d", &pos_y);

	xy(pos_x,pos_y); // Llamada a la función
 
	printf("*"); // Imprimir asterisco en la posición

	mi_pausa();

	return 0;
}
```

Fichero: [GOTOXY_PARAM.C](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/GOTOXY_PARAM.C)

Ejecución: ![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/1gotoxy.png)

2. `setcursortype()`: fijar el aspecto del cursor, debe admitir tres valores: _INVISIBLE_, _NORMAL_ y _GRUESO_.

Función proporcionada por el profesor:
```c
void setcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	
	}
	int86(0x10, &inregs, &outregs);
}
```

Se ha cambiado el _main_ para que el usuario pueda elegir el tipo de cursor por teclado:

```c
int main(){
	int tmp;

	printf("\nTipos de cursor. \n");
	printf("\tTipo 0: invisible \tTipo 1: normal \tTipo 2: grueso \n\nIntroduce solo el numero: ");
	scanf("%d", &tmp); // Leer de teclado

	printf("\nHas elegido tipo: %d\n", tmp); //Mostrar elección

   	setcursortype(tmp);
   	mi_pausa();   	

	return 0;
}
```
Fichero: [CURSOR.C](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/cursor.C)

Ejecución para cursor normal: ![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/2cursor1.png)

Ejecución para cursor grueso: ![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/2cursor2.png)

Ejecución para cursor invisible: ![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/2cursor0.png)

3. `setvideomode()`: fija el modo de video deseado.

Para implementar esta función hay que usar la interrupción $10h$ de la BIOS, específicamente la función $00h$ (que se carga en el registro AH).

```c
#define TEXTO 0x03
#define GRAFICO 0x04 // O 0x13 para 320x200 256 colores

void setvideomode(unsigned char modo){
	union REGS inregs, outregs; 
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs); 
	return;
}

int main(){

	printf("Modo gráfico para dibujar");
	setvideomode(GRAFICO);  

	printf("Presiona una tecla para volver a modo texto...");
    mi_pausa();

    // Volver a modo texto antes de salir
    setvideomode(TEXTO);

	return 0;
}
```

Fichero: [modovideo.c](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/modovideo.c)

4. `getvideomode()`: obtiene el modo de video actual.

Para implementar esta función getvideomode hay que consultar el estado actual del adaptador de vídeo. Según la documentación de la BIOS, esto se hace con la Interrupción $10h$, función $0Fh$.

Además, se hace uso de la función anterior (`setvideomode`).
```c
#define GRAFICO 0x04 

unsigned char getvideomode(){
	union REGS inregs, outregs; 
   inregs.h.ah = 0x0F; // Obtener modo de video actual
   int86(0x10,&inregs,&outregs); 
   return outregs.h.al;
}

int main(){
   unsigned char modo_original;
   modo_original = getvideomode();
   printf("Modo: %c\n", modo_original);
	
   printf("Cambiar a modo gráfico para dibujar");
   setvideomode(GRAFICO);  // GRAFICO = 0x04
   mi_pausa();

	printf("Presiona una tecla para volver a modo original...");

   // Volver al modo original, sea cual sea
   setvideomode(modo_original);

	return 0;
}
```

Fichero: [modovideo.c](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/modovideo.c)

5. `textcolor()`: modifica el color de primer plano con que se mostrarán los caracteres.

Para escribir un carácter en pantalla se usa la interrupción _10h_, con el número de función _9 = AH_.

No tiene salida. Como parámetros de entrada tenemos:
- AH = 9  
- AL = código ASCII del carácter  
- BL = color
	- el primer cuarteto fija el color de fondo
 	- el segundo cuarteto el color del carácter
- BH = 0  
- CX = número de repeticiones  


Se necesita una variable que guarde el color actual para que todas las funciones de escritura lo sepan:

```c
unsigned char color_actual_texto = 7; // Gris claro
```

6. `textbackground()`: modifica el color de fondo con que se mostrarán los caracteres.

7. `clrscr()`: borra toda la pantalla.

8. `cputchar()`: escribe un carácter en pantalla con el color indicado actualmente.

9. `getche()`: obtiene un carácter de teclado y lo muestra en pantalla.

```c
void getche(){
	union REGS inregs, outregs;
	int caracter;

	// Solicitar
	printf("\nPulsa una tecla...  ");
	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs);

	caracter = outregs.h.al;

	// Mostrar
	printf("\nHas pulsado: ");
	inregs.h.ah = 2;
	inregs.h.dl = caracter;
	int86(0x21, &inregs, &outregs);
	
}

int main(){
	// Lamada a la función
	getche();
   	mi_pausa();

	return 0;
}
```

Fichero: [GET_CHAR.C](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/GET_CHAR.C)

Ejecución: ![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/9getche.png)

10. `pixel()`: dibujar un pixel en modo gráfico (la función recibirá la coordinada _x,y_ y el color del punto). 



## Requisitos ampliados  
1. Implementar una función que permita dibujar un recuadro en la pantalla en modo texto. Recibirá como parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y el color de fondo.

2. Implementar en lenguaje C un programa que establezca modo gráfico CGA (_modo=4_) para crear dibujos sencillos en pantalla.

3. Implementar un programa sencillo que realice un dibujo sencillo de tipo “ascii art”. En el ANEXO al final de este guión se proponen algunos diseños. 
