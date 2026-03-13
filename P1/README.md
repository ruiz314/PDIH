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

En clase se propusieron varias ideas:

- Dar 25 retornos de carro con $printf("\n\n...\n");$. Al imprimir 25 saltos de línea se empuja el texto anterior hacia arriba hasta que desaparece de la ventana. La desventaja es que el cursor se quedaría en la parte de abajo de la pantalla, en vez de posicionarlo arriba como sería deseable. Si se usase este método se podría hacer uso de la función _gotoxy(0,0)_ para poner el cursor arriba del todo (en la coordenada 0,0).
- Llamar al modo de video usando la función _setvideomode(3)_ que provoca un parpadeo negro porque reinicia la tarjeta gráfica. La desventaja es que se pierde la configuración de colores que se hubiese establecido previamente.
- Usar la interrupción $10h$ y función $06h$ que se explica en el guión de la práctica para hacer _scroll vertical_.


La más acertada sería la tercera idea, usando la BIOS. Se borrará un recuadro que va desde la fila 0, columna 0, hasta la fila 24, columna 79 porque la pantalla en modo texto tiene 80 columnas y 25 filas.

La función número 6 tiene de entrada:
- AH = 6
- AL = número de líneas a desplazar. Si AL = 0 entonces no se desplaza, sino que borra esa zona.
- BH = color para los espacios en blanco
- CH = línea de la esquina superior izquierda
- CL = columna de la esquina superior izquierda
- DH = línea de la esquina inferior derecha
- DL = columna de la esquina inferior derecha

Entonces la implementación de la función clrscr() podría ser:

```c
unsigned char cfondo=0; // Negro
unsigned char ctexto=15; // Blanco

void clrscr() {
    union REGS inregs, outregs;
    
    inregs.h.ah = 0x06;      // Función 6: Desplazamiento hacia arriba (Scroll)
    inregs.h.al = 0x00;      // AL = 0 indica borrar toda la zona seleccionada
    
    // El color con el que se rellena la pantalla vacía
    inregs.h.bh = (cfondo << 4) | ctexto; 
    
    inregs.h.ch = 0;         // Fila de la esquina superior izquierda
    inregs.h.cl = 0;         // Columna de la esquina superior izquierda
    inregs.h.dh = 24;        // Fila de la esquina inferior derecha (25 filas en total)
    inregs.h.dl = 79;        // Columna de la esquina inferior derecha (80 columnas en total)
    
    int86(0x10, &inregs, &outregs); // Interrupción de vídeo
```

El código completo para ver un ejemplo está en el fichero: [limpiar.c](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/limpiar.c)

Ejemplo de compilación y ejecución de _clrscr()_:

![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/7limpiar1.png)

Justo antes de borrar se cambia el color de fondo a azul. Así se ve claramente cómo la función de la BIOS pinta todo el recuadro de la pantalla (las 80 columnas y 25 filas) de ese color de una sola vez.

![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/7limpiar2.png)

Al pulsar una tecla para salir se reestablece la pantalla con fondo negro:

![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/7limpiar3.png)


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

Se debe trabajar en modo gráfico, por eso hay que usar la función _setvideomode()_ del ejercicio 3.

La función \textit{pixel()} sería:

```c
void pixel(int x, int y, BYTE C){
    union REGS inregs, outregs;
    
    inregs.x.cx = x;       // Columna (coordenada X)
    inregs.x.dx = y;       // Fila (coordenada Y)
    inregs.h.al = C;       // Color del pixel
    inregs.h.ah = 0x0C;    // Función 0Ch: iluminar un pixel en modo gráfico
    
    int86(0x10, &inregs, &outregs); // Llamada a la interrupción BIOS para pantalla
}
```

Para probar que funciona correctamente se usa el siguiente main:
```c
int main(){
    // Cambiar a modo gráfico gráfico (320x200 con 4 colores)
    setvideomode(4); 

    // Pintar algunos píxeles (formando una línea diagonal)
    pixel(01, 40, 7); // Color 7: gris claro
    pixel(10, 50, 1); // Color 1: azul
    pixel(15, 60, 2); // Color 2: verde
    pixel(20, 70, 3); // Color 3: cyan
    pixel(25, 80, 7); // Color 7
    pixel(30, 90, 1); // Color 1
    pixel(35, 100, 2); // Color 2
    pixel(40, 110, 3); // Color 3

    pixel(45, 100, 7); // Color 7
    pixel(50, 90, 1); // Color 1
    pixel(55, 80, 2); // Color 2
    pixel(60, 70, 3); // Color 3
    pixel(65, 60, 7); // Color 7
    pixel(70, 50, 1); // Color 1
    pixel(75, 40, 2); // Color 2
    
    // Hacer una pausa para ver el resultado
    mi_pausa();
    
    // Restaurar el modo texto a color
    setvideomode(3); 
    
    return 0;
}
```

Los pixeles pintados forman una $V$, empezando por la coordenada $(1,40)$ con el color gris claro, con vértice color cyan en la coordenada $(40, 110)$, y teminando en la coordenada $(75, 40)$ con color verde.

Programa completo para probar el correcto funcionamiento: [pixel.c](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/pixel.c)

Ejecución: ![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/10pixel.png)

## Requisitos ampliados  
1. Implementar una función que permita dibujar un recuadro en la pantalla en modo texto. Recibirá como parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y el color de fondo.

Para ello hay que usar la interrupción de la BIOS para servicios de vídeo: $0x10$. 
- Para posicionar el puntero y empezar a pintar el recuadro se usa $AH=02h$, donde $DH$ indica la fila (coordenada Y) y $DL$ indica la columna (coordenada x).
- Para escribir el carácter se usa $AH=09h$ indicando cuantas veces se repite con $CX$, especificando el carácter con $AL$ y para dar color (fondo y texto) $BL$.

La función sería:

```c
void dibujar_recuadro(int sup_x, int sup_y, int inf_x, int inf_y, char color, char fondo){
    union REGS inregs, outregs;
    int i;

    // Guardar los colores 
    unsigned char atributo;
    atributo = (fondo << 4) | (color & 0x0F);
  
    // Dibujar las lineas horizontales
    for(i = sup_x; i <= inf_x; i++){
        // Borde superior
        inregs.h.ah = 0x02; // Posicionar cursor
        inregs.h.dh = sup_y; // Fila
        inregs.h.dl = i; // Columna
        inregs.h.bh = 0; 
        int86(0x10, &inregs, &outregs);
        
        inregs.h.ah = 0x09; // Escribir caracter con color
        inregs.h.al = 205; // Caracter guion ─
        inregs.h.bl = atributo; // Color
        inregs.x.cx = 1; int86(0x10, &inregs, &outregs); 

        // Borde inferior
        inregs.h.ah = 0x02; inregs.h.dh = inf_y; inregs.h.dl = i; 
        int86(0x10, &inregs, &outregs);
        
        inregs.h.ah = 0x09; inregs.h.al = 205; 
        int86(0x10, &inregs, &outregs);
    }
  
    // Dibujar las lineas verticales
    for(i = sup_y; i <= inf_y; i++){
        // Borde izquierdo
        inregs.h.ah = 0x02; inregs.h.dh = i; inregs.h.dl = sup_x; 
        int86(0x10, &inregs, &outregs);
        
        inregs.h.ah = 0x09;  // Escribir caracter con color
        inregs.h.al = 186;  // Caracter barra vertical │
        inregs.h.bl = atributo; // Color
        int86(0x10, &inregs, &outregs);

        // Borde derecho
        inregs.h.ah = 0x02; inregs.h.dh = i; inregs.h.dl = inf_x; 
        int86(0x10, &inregs, &outregs);
        
        inregs.h.ah = 0x09; inregs.h.al = 186; 
        int86(0x10, &inregs, &outregs);
    }

    // Dibujar las esquinas
    // Esquina superior izquierda
    inregs.h.ah = 0x02; inregs.h.dh = sup_y; inregs.h.dl = sup_x; // Posicionar cursor
    int86(0x10, &inregs, &outregs);
    inregs.h.ah = 0x09; inregs.h.al = 201; // Escribir caracter con color
    int86(0x10, &inregs, &outregs);

    // Esquina superior derecha
    inregs.h.ah = 0x02; inregs.h.dh = sup_y; inregs.h.dl = inf_x; 
    int86(0x10, &inregs, &outregs);
    inregs.h.ah = 0x09; inregs.h.al = 187; 
    int86(0x10, &inregs, &outregs);

    // Esquina inferior izquierda 
    inregs.h.ah = 0x02; inregs.h.dh = inf_y; inregs.h.dl = sup_x; 
    int86(0x10, &inregs, &outregs);
    inregs.h.ah = 0x09; inregs.h.al = 200; 
    int86(0x10, &inregs, &outregs);

    // Esquina inferior derecha
    inregs.h.ah = 0x02; inregs.h.dh = inf_y; inregs.h.dl = inf_x; 
    int86(0x10, &inregs, &outregs);
    inregs.h.ah = 0x09; inregs.h.al = 188; 
    int86(0x10, &inregs, &outregs);
}
```

Fichero: [ejer11.c](https://github.com/ruiz314/PDIH/blob/main/P1/ficheros/ejer11.c)

En el ejemplo se usan dos variables globales para fijar el color de fondo a negro, y el color de texto a azul claro. 

```c
    unsigned char cfondo=0; // Negro
    unsigned char ctexto=9; // Azul claro
    ...
    int main(){
        ...
        dibujar_recuadro(20, 5, 60, 15, 14, 2);
        ...
    }
```

Cuando se llama a la función se especifican otros colores: texto amarillo y fondo verde. El resultado es el siguiente:

 ![img](https://github.com/ruiz314/PDIH/blob/main/P1/img/11recuadro.png)

2. Implementar en lenguaje C un programa que establezca modo gráfico CGA (_modo=4_) para crear dibujos sencillos en pantalla.

3. Implementar un programa sencillo que realice un dibujo sencillo de tipo “ascii art”. En el ANEXO al final de este guión se proponen algunos diseños. 
