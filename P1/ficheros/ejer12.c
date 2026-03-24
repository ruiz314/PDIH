#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char

//unsigned char cfondo=0; // Negro
//unsigned char ctexto=9; // Azul claro

// Espera la pulsación de una tecla
void mi_pausa(){
	union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs); // Interrupción del MS-DOS para servicios del sistema (teclado, salida de texto, terminar programa).
}

// Fija el modo de video deseado.
void setvideomode(unsigned char modo){
	union REGS inregs, outregs; 
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs); 
	return;
}

// Dibujar un pixel en modo gráfico (la función recibirá la coordinada x,y y el color del punto).
void pixel(int x, int y, BYTE C){
    union REGS inregs, outregs;
    
    inregs.x.cx = x;       // Columna (coordenada X)
    inregs.x.dx = y;       // Fila (coordenada Y)
    inregs.h.al = C;       // Color del pixel
    inregs.h.ah = 0x0C;    // Función 0Ch: iluminar un pixel en modo gráfico
    
    int86(0x10, &inregs, &outregs); // Llamada a la interrupción BIOS para pantalla
}


int main(){
    int i;

    // Pasar a modo gráfico CGA
    setvideomode(4); // 320x200, 4 colores

    // Hacer dibujo: CASA
    // Techo y suelo, color azul claro = 1
    // desde la columna X=100 hasta X=200,
    for(i = 100; i <= 200; i++) {
        pixel(i, 100, 1); // Techo del cuadrado (Y se mantiene en 100)
        pixel(i, 180, 1); // Suelo de la casa (Y se mantiene en 180)
    }

    // Paredes, color azul claro = 1
    // desde la fila Y=100 hasta Y=180
    for(i = 100; i <= 180; i++) {
        pixel(100, i, 1); // Pared izquierda (X se mantiene en 100)
        pixel(200, i, 1); // Pared derecha (X se mantiene en 200)
    }

    // Tejado (triángulo), color rosa = 2
    // El centro de la casa está en X=(100+200)/2 = 150
    for(i = 0; i <= 50; i++){
        pixel(100 + i, 100 -i, 2); // Lado izquierdo: desde la esquina (100,100) hacia el pico (150,50)
        pixel(150 +i, 50 +i, 2); // Lado derecho: desde el pico (150,50) hasta la esquina (200,100)
    }

    // Puerta, color blanco = 3
    for(i = 150; i <= 180; i++){
        pixel(140, i, 3); // Lado izquierdo de la puerta (X se mantiene en 140)
        pixel(160, i, 3); // Lado derecho de la puerta (X se mantiene en 160)
    }
    for(i = 140; i <= 160; i++){
        pixel(i, 150, 3); // Parte superior de la puerta (Y se mantiene en 150)
    }


    printf("Pulsa una tecla para salir...");  
    mi_pausa();

    // Restaurar modo texto
    setvideomode(3); // Modo texto 80x25
    
    return 0;
}