#include <stdio.h>
#include <dos.h>

unsigned char cfondo=0; // Negro
unsigned char ctexto=15; // Blanco

void mi_pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 8;         // Función 8: leer tecla sin mostrarla
    int86(0x21, &inregs, &outregs);
}

//Función para posicionar el cursor en coordenadas (x, y)
void xy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10, &inregs, &outregs);
	return;
}

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
}

int main() {   
    printf("\nPulsa una tecla para llamar a clrscr() ...");
    mi_pausa();

    // Cambiar el color de fondo a AZUL justo antes de borrar
    cfondo = 1; //Azul
    ctexto = 15; //Blanco

    clrscr();    

    printf("\nPulsa una tecla para salir del programa...");
    
    mi_pausa();

    // Restaurar el fondo a negro 
    cfondo = 0; //Negro
    clrscr();

    return 0;
}
