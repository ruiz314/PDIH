#include <stdio.h>
#include <dos.h>

unsigned char cfondo=0; // Negro
unsigned char ctexto=9; // Azul claro

void mi_pausa(){
	union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs); // Interrupción del MS-DOS para servicios del sistema (teclado, salida de texto, terminar programa).
}

void gotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10,&inregs,&outregs);
	return;
}

// Funcion para cambiar el color del texto
void textcolor(int nuevo_color) { ctexto = nuevo_color;}

// Funcion para cambiar el color de fondo
void textbackground(int nuevo_color) { cfondo = nuevo_color;}

// Funcion para escribir el carácter
void cputchar(char c){ 
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;	// Función 9: escribir caracter y atributo
    inregs.h.al = c;    // Caracter a imprimir
    inregs.h.bl = (cfondo << 4) | ctexto; // Fusión
    inregs.h.bh = 0x00; 
    inregs.x.cx = 1;   
    int86(0x10, &inregs, &outregs);
}

void clrscr() {
    union REGS inregs, outregs;
    
    inregs.h.ah = 0x06;      // Función 6: Desplazamiento hacia arriba (Scroll)
    inregs.h.al = 0x00;      // AL = 0 indica borrar toda la zona seleccionada
    
    // El color con el que se rellenará la pantalla vacía
    inregs.h.bh = (cfondo << 4) | ctexto; 
    
    inregs.h.ch = 0;         // Fila de la esquina superior izquierda
    inregs.h.cl = 0;         // Columna de la esquina superior izquierda
    inregs.h.dh = 24;        // Fila de la esquina inferior derecha (25 filas en total)
    inregs.h.dl = 79;        // Columna de la esquina inferior derecha (80 columnas en total)
    
    int86(0x10, &inregs, &outregs); // Interrupción de vídeo
    
    // Posicionar cursor en la esquina superior izquierda después de limpiar
    gotoxy(0,0);
}

/**
 * @brief Función que permita dibujar un recuadro en la pantalla en modo texto. 
 * Recibirá como parámetros las coordenadas superior izquierda e inferior derecha del recuadro, el color de primer plano y el color de fondo.
*/
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
        int86(0x10, &inregs, &outregs);  // Interrupción de la BIOS para servicios de vídeo
        
        inregs.h.ah = 0x09; // Escribir caracter con color
        inregs.h.al = 205; // Caracter ─
        inregs.h.bl = atributo; // Color
        inregs.x.cx = 1; int86(0x10, &inregs, &outregs); 

        // Borde inferior
        inregs.h.ah = 0x02; inregs.h.dh = inf_y; inregs.h.dl = i; int86(0x10, &inregs, &outregs);
        
        inregs.h.ah = 0x09; inregs.h.al = 205; int86(0x10, &inregs, &outregs);
    }
  
    // Dibujar las lineas verticales
    for(i = sup_y; i <= inf_y; i++){
        // Borde izquierdo
        inregs.h.ah = 0x02; inregs.h.dh = i; inregs.h.dl = sup_x; int86(0x10, &inregs, &outregs);
        
        inregs.h.ah = 0x09;  // Escribir caracter con color
        inregs.h.al = 186;  // Caracter │
        inregs.h.bl = atributo; // Color
        int86(0x10, &inregs, &outregs);

        // Borde derecho
        inregs.h.ah = 0x02; inregs.h.dh = i; inregs.h.dl = inf_x; int86(0x10, &inregs, &outregs);
        
        inregs.h.ah = 0x09; inregs.h.al = 186; int86(0x10, &inregs, &outregs);
    }

    // Dibujar las esquinas
    // Esquina superior izquierda
    inregs.h.ah = 0x02; inregs.h.dh = sup_y; inregs.h.dl = sup_x; int86(0x10, &inregs, &outregs);
    inregs.h.ah = 0x09; inregs.h.al = 201; int86(0x10, &inregs, &outregs);

    // Esquina superior derecha
    inregs.h.ah = 0x02; inregs.h.dh = sup_y; inregs.h.dl = inf_x; int86(0x10, &inregs, &outregs);
    inregs.h.ah = 0x09; inregs.h.al = 187; int86(0x10, &inregs, &outregs);

    // Esquina inferior izquierda 
    inregs.h.ah = 0x02; inregs.h.dh = inf_y; inregs.h.dl = sup_x; int86(0x10, &inregs, &outregs);
    inregs.h.ah = 0x09; inregs.h.al = 200; int86(0x10, &inregs, &outregs);

    // Esquina inferior derecha
    inregs.h.ah = 0x02; inregs.h.dh = inf_y; inregs.h.dl = inf_x; int86(0x10, &inregs, &outregs);
    inregs.h.ah = 0x09; inregs.h.al = 188; int86(0x10, &inregs, &outregs);
}

int main(){
    clrscr();// Limpiar la pantalla

    // Dibujar recuadro en el centro de la pantalla: desde la columna 20, fila 5 hasta la columna 60, fila 15. Texto AMARILLO (14) y Fondo VERDE (2).
    dibujar_recuadro(20, 5, 60, 15, 14, 2); // (sup_x, sup_y, inf_x, inf_y, color, fondo)

    // Escribimos un título dentro del recuadro
    gotoxy(25, 10); 
    printf("Recuadro dibujado con exito"); 

    // Pausa para ver el resultado
    gotoxy(1, 20);
    
    printf("Pulsa una tecla para salir...");  
    mi_pausa();
    return 0;
}
