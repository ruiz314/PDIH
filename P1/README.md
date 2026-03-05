# Práctica 1. Entrada/Salida utilizando interrupciones con lenguaje C

## Requisitos mínimos
Realizar las siguientes 10 funciones, que deben diseñarse e implementarse de forma que se puedan reutilizar fácilmente en otros programas. El programa debe utilizar de todas esas funciones para comprobar su correcto funcionamiento. 

1. `gotoxy()`: coloca el cursor en una posición determinada
2. `setcursortype()`: fijar el aspecto del cursor, debe admitir tres valores: _INVISIBLE_, _NORMAL_ y _GRUESO_.
3. `setvideomode()`: fija el modo de video deseado
4. `getvideomode()`: obtiene el modo de video actual
5. `textcolor()`: modifica el color de primer plano con que se mostrarán los caracteres
6. `textbackground()`: modifica el color de fondo con que se mostrarán los caracteres
7. `clrscr()`: borra toda la pantalla
8. `cputchar()`: escribe un carácter en pantalla con el color indicado actualmente
9. `getche()`: obtiene un carácter de teclado y lo muestra en pantalla
10. `pixel()`: dibujar un pixel en modo gráfico (la función recibirá la coordinada _x,y_ y el color del punto). 



## Requisitos ampliados  
1. Implementar una función que permita dibujar un recuadro en la pantalla en modo texto. Recibirá como parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y el color de fondo.
2. Implementar en lenguaje C un programa que establezca modo gráfico CGA (_modo=4_) para crear dibujos sencillos en pantalla.
3. Implementar un programa sencillo que realice un dibujo sencillo de tipo “ascii art”. En el ANEXO al final de este guión se proponen algunos diseños. 
