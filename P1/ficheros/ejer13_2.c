#include <stdio.h>
#include <dos.h>

// Para restaurar los valores originales tras usar la función limpiar
unsigned char cfondo=0; // Negro
unsigned char ctexto=15; // Blanco

// Espera la pulsación de una tecla
void mi_pausa(){
	union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs); // Interrupción del MS-DOS para servicios del sistema (teclado, salida de texto, terminar programa).
}

//Función para posicionar el cursor en coordenadas (x, y)
void xy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10,&inregs,&outregs);
	return;
}

// Función para limpiar pantalla
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
int main() {
    // Limpiar la pantalla
    clrscr();

    // Posicionar el cursor en el centro (columna 35, fila 10)
    // y dibujar línea a línea del primer conejo.
    
    // Orejas
    gotoxy(35, 10);
    printf("   (\\(\\ \n");

    // Cara
    gotoxy(35, 11);
    printf("   (-.-)\n");

    // Patas
    gotoxy(35, 12);
    printf(" o_(\")(\")\n");

    //Posicionar el cursor en (columna 45, fila 10)
    // y dibujar el segundo conejo, que es igual pero invertido (mirando hacia abajo)
    gotoxy(47, 10);
    printf("  /)/) \n");
    gotoxy(47, 11);
    printf(" (-.-) \n");
    gotoxy(47, 12);
    printf("(\")(\")_o\n");

    // Mensaje final
    gotoxy(25, 15);
    printf("Conejo dibujado con exito");
    
    // Pausa para ver el resultado
    gotoxy(25, 17);
    printf("Pulsa una tecla para salir...");
    mi_pausa();

    return 0;
}
