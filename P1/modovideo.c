#include <stdio.h>
#include <dos.h>

// P1
// setvideomode(): fija el modo de video deseado  
// getvideomode(): obtiene el modo de video actual 

#define TEXTO 0x03
#define GRAFICO 0x04 // O 0x13 para 320x200 256 colores

void mi_pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

void setvideomode(unsigned char modo){
	union REGS inregs, outregs; 
	inregs.h.ah = 0x00; // Para cambiar el modo de pantalla
	inregs.h.al = modo; // Indicar a qué modo específico cambiar
	int86(0x10,&inregs,&outregs); 
	return;
}

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
   //setvideomode(TEXTO);
   //mi_pausa();

   // Volver al modo original, sea cual sea
   setvideomode(modo_original);

	return 0;
}
