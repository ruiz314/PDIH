# Práctica 1. Entrada/Salida utilizando interrupciones con lenguaje C

## Requisitos mínimos
Realizar las siguientes 10 funciones, que deben diseñarse e implementarse de forma que se puedan reutilizar fácilmente en otros programas. El programa debe utilizar de todas esas funciones para comprobar su correcto funcionamiento. 

1. `gotoxy()`: coloca el cursor en una posición determinada
```c
#include <stdio.h>
#include <dos.h>

void mi_pausa(){
	union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}

void xy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10,&inregs,&outregs);
	return;
}

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
Esta función es proporcionada por el profesor, pero para hacerla más dinámica en el main se solicita al usuario las coordenadas $x$ e $y$.

Fichero: [GOTOXY_PARAM.C](https://github.com/ruiz314/PDIH/blob/main/P1/GOTOXY_PARAM.C)

3. `setcursortype()`: fijar el aspecto del cursor, debe admitir tres valores: _INVISIBLE_, _NORMAL_ y _GRUESO_.
4. `setvideomode()`: fija el modo de video deseado
5. `getvideomode()`: obtiene el modo de video actual
6. `textcolor()`: modifica el color de primer plano con que se mostrarán los caracteres
7. `textbackground()`: modifica el color de fondo con que se mostrarán los caracteres
8. `clrscr()`: borra toda la pantalla
9. `cputchar()`: escribe un carácter en pantalla con el color indicado actualmente
10. `getche()`: obtiene un carácter de teclado y lo muestra en pantalla
11. `pixel()`: dibujar un pixel en modo gráfico (la función recibirá la coordinada _x,y_ y el color del punto). 



## Requisitos ampliados  
1. Implementar una función que permita dibujar un recuadro en la pantalla en modo texto. Recibirá como parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y el color de fondo.
2. Implementar en lenguaje C un programa que establezca modo gráfico CGA (_modo=4_) para crear dibujos sencillos en pantalla.
3. Implementar un programa sencillo que realice un dibujo sencillo de tipo “ascii art”. En el ANEXO al final de este guión se proponen algunos diseños. 
