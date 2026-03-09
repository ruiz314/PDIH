#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char

void mi_pausa(){
   union REGS inregs, outregs;
   inregs.h.ah = 8;
   int86(0x21, &inregs, &outregs);
}


void setvideomode(unsigned char modo){
	union REGS inregs, outregs; 
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs); 
	return;
}

void pixel(int x, int y, BYTE C){
    union REGS inregs, outregs;
    
    inregs.x.cx = x;       // Columna (coordenada X)
    inregs.x.dx = y;       // Fila (coordenada Y)
    inregs.h.al = C;       // Color del pixel
    inregs.h.ah = 0x0C;    // Función 0Ch: iluminar un pixel en modo gráfico
    
    int86(0x10, &inregs, &outregs); // Llamada a la interrupción BIOS para pantalla
}

int main(){
    // Cambiar a modo gráfico gráfico (320x200 con 4 colores)
    setvideomode(4); 

    // Pintar algunos píxeles (formando una v)
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
    //pixel(80, 70, 3); // Color 3
    
    // Hacer una pausa para ver el resultado
    mi_pausa();
    
    // Restaurar el modo texto a color
    setvideomode(3); 
    
    return 0;
}
