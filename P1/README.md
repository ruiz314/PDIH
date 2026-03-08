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

Para colocar el cursor en una posición determinada se usa la entrada $AH=2$. Además, es necesario usar:
- DH: número de la fila
- DL: número de columna
- BH = 0

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

Esta función es proporcionada por el profesor, pero para hacerla más dinámica en el _main_ se solicita al usuario las coordenadas $x$ e $y$.

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

Ejecución para $x=3$ e $y=3$: ![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/1gotoxy.png)

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
	setvideomode(GRAFICO);  //0x04

	printf("Presiona una tecla para volver a modo texto...");
    mi_pausa();

    // Volver a modo texto antes de salir
    setvideomode(TEXTO); //0x03

	return 0;
}
```

Se han definido dos variables globales para cambiar los modos:
- _TEXTO_: Modo $AL = 03h$, con resolución $80x25$, 16 colores.
- _GRAFICO_: Modo $AL = 04h$, con resolución $320x200$, 4 colores.

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

Fichero completo: [modovideo.c](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/modovideo.c)

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


Se necesitan variables que guarden los colores deseados para que todas las funciones de escritura lo sepan, como por ejemplo:

```c
unsigned char colorActualTexto = 7; // Gris claro
```

Luego hay que usar esas variables dentro de la función _cputchar()_ para imprimir el caracter.

Para este ejercicio solo se muestra la implementación de la función que cambia el color del texto(_textcolor()_). Al final del ejercicio 6 se mostrará la implementación de un programa que cambie el color del caracter y lo muestre por pantalla.

```c
unsigned char colorActualTexto = 7; // Gris claro

void textcolor(int nuevo_color) {
    colorActualTexto = nuevo_color;
}
```

6. `textbackground()`: modifica el color de fondo con que se mostrarán los caracteres.

Es importante mencionar que los **colores de fondo sólo pueden tomar valores entre el 0 y el 7**. Esto se menciona en el documento de la práctica proporcionado por el profesor.

Una opción para usar las dos funciones anteriores (_textcolor()_ y _textbackground()_) en una sola sería la propuesta por el profesor:

```c
#include <stdio.h>
#include <dos.h>

unsigned char cfondo;
unsigned char ctexto;

void escribir_char_con_color(char c){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;	// Funcion escribir caracter
	inregs.h.al = c;    //una funcion mas general debe recibir el caracter a imprimir
	inregs.h.bl = cfondo << 4 | ctexto; // Fusion de color de texto y fondo en un solo byte
	inregs.h.bh = 0x00;
	inregs.x.cx = 1; // Numero de veces que se repite el caracter
	int86(0x10,&inregs,&outregs);
	return;
}

int main(){
	printf("\nc.fondo=rojo, c.texto=azul => ");
	cfondo=4; ctexto=1; // cfondo=4=rojo , ctexto=1=azul
	escribir_char_con_color('H'); 

	printf("\nc.fondo=verde, c.texto=negro => ");
	cfondo=2; ctexto=0; // cfondo=2=verde , ctexto=0=negro
	escribir_char_con_color('O'); 
	
	printf("\nc.fondo=gris claro, c.texto=cian => ");
	cfondo=7; ctexto=3; // cfondo=7=gris claro , ctexto=13=cian
	escribir_char_con_color('L'); 

	printf("\nc.fondo=magenta, c.texto=verde claro => ");
	cfondo=5; ctexto=10; // cfondo=5=magenta , ctexto=10=verde claro 
	escribir_char_con_color('A'); 

	return 0;
}
```

Ejecución para ver la palabra 'HOLA' con distintos colores:

![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/6color.png)

Otra opción sería definir una función para cambiar el color de fondo y combinarla con la función _textcolor()_ y con la función _cputchar()_ del ejercicio 8.

```c
unsigned char colorActualFondo = 7; // Gris claro

void textbackground(int nuevo_color) {
    colorActualFondo = nuevo_color;
}
```

7. `clrscr()`: borra toda la pantalla.

8. `cputchar()`: escribe un carácter en pantalla con el color indicado actualmente.

Esta es la función que completa la funcionalidad de cambiar el color del texto y el color del fondo del texto que se solicita en los ejercicio 5 y 6.

La propuesta de la función es la siguiente:
```c
unsigned char colorActualTexto = 4; // Rojo
unsigned char colorActualFondo = 7; // Gris claro

void cputchar(char c){
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;	// Funcion 9: escribir caracter y atributo
    inregs.h.al = c;    // Caracter a imprimir
    inregs.h.bl = (colorActualFondo << 4) | colorActualTexto; // Fusion de color de texto y fondo
    inregs.h.bh = 0x00; // Pagina de video
    inregs.x.cx = 1;    // Numero de veces que se repite el caracter
    int86(0x10, &inregs, &outregs);
}
```

Entonces, combinando las funciones _textcolor()_ y _textbackground()_ se puede implementar el siguiente programa:

```c
#include <stdio.h>
#include <dos.h>

unsigned char colorActualTexto = 4; // Rojo
unsigned char colorActualFondo = 7; // Gris claro

// Funcion para cambiar el color del texto
void textcolor(int nuevo_color) { colorActualTexto = nuevo_color;}

// Funcion para cambiar el color de fondo
void textbackground(int nuevo_color) { colorActualFondo = nuevo_color;}

// Funcion para escribir el carácter
void cputchar(char c){ 
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;	// Función 9: escribir caracter y atributo
    inregs.h.al = c;    // Caracter a imprimir
    inregs.h.bl = (colorActualFondo << 4) | colorActualTexto; // Fusión
    inregs.h.bh = 0x00; 
    inregs.x.cx = 1;   
    int86(0x10, &inregs, &outregs);
}

int main(){
    printf("\nc.fondo=rojo, c.texto=azul => ");
    colorActualTexto = 1; colorActualFondo = 4; // Texto Azul; Fondo Rojo
    textbackground(colorActualFondo); textcolor(colorActualTexto);
    cputchar('P'); 

    printf("\nc.fondo=gris claro, c.texto=cian => ");
    colorActualTexto = 3; colorActualFondo = 7; // Texto Cian; Fondo Gris claro
    textbackground(colorActualFondo); textcolor(colorActualTexto);
    cputchar('D'); 
    
    printf("\nc.fondo=magenta, c.texto=verde claro => ");
    colorActualTexto = 10; colorActualFondo = 5; // Texto verde claro; Fondo Magenta
    textbackground(colorActualFondo); textcolor(colorActualTexto);
    cputchar('I'); 

    printf("\nc.fondo=verde, c.texto=negro => ");
    colorActualTexto = 0; colorActualFondo = 2; // Texto negro; Fondo Verde
    textbackground(colorActualFondo); textcolor(colorActualTexto);
    cputchar('H'); 

    return 0;
}
```

Fichero: [colores.c](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/colores.c)

En la siguiente imagen podemos ver las dos soluciones propuestas, la del profesor con la palabra 'HOLA' y la segunda propuesta con la palabra 'PDIH'.

![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/8colores.png)

9. `getche()`: obtiene un carácter de teclado y lo muestra en pantalla.

Para gestionar el teclado se usa la interrupción de la BIOS $16h$. La subfunción 1 detectar la pulsación de una tecla. La entrada es $AH = 1$. La salida es $0$ si hay una tecla en el búfer,  y $1$ si el búfer está vacío.

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
