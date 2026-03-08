#include <stdio.h>
#include <dos.h>

unsigned char colorActualTexto = 4; // Rojo
unsigned char colorActualFondo = 7; // Gris claro

void textcolor(int nuevo_color) { // Funcion para cambiar el color del texto
    colorActualTexto = nuevo_color;
}

void textbackground(int nuevo_color) { // Funcion para cambiar el color de fondo
    colorActualFondo = nuevo_color;
}

void cputchar(char c){ // Funcion para escribir el carácter
    union REGS inregs, outregs;
    inregs.h.ah = 0x09;	// Funcion 9: escribir caracter y atributo
    inregs.h.al = c;    // Caracter a imprimir
    inregs.h.bl = (colorActualFondo << 4) | colorActualTexto; // Fusion
    inregs.h.bh = 0x00; 
    inregs.x.cx = 1;   
    int86(0x10, &inregs, &outregs);
}

int main(){
    printf("\nc.fondo=rojo, c.texto=azul => ");
    colorActualTexto = 1; // Azul
    colorActualFondo = 4; // Rojo
    textbackground(colorActualFondo); 
    textcolor(colorActualTexto);
    cputchar('P'); 

    printf("\nc.fondo=gris claro, c.texto=cian => ");
    colorActualTexto = 3; // Cian
    colorActualFondo = 7; //Gris claro
    textbackground(colorActualFondo); textcolor(colorActualTexto);
    cputchar('D'); 
    
    printf("\nc.fondo=magenta, c.texto=verde claro => ");
    colorActualTexto = 10; //verde claro
    colorActualFondo = 5; //magenta
    textbackground(colorActualFondo); textcolor(colorActualTexto);
    cputchar('I'); 

    printf("\nc.fondo=verde, c.texto=negro => ");
    colorActualTexto = 0; //negro
    colorActualFondo = 2; //verde
    textbackground(colorActualFondo); textcolor(colorActualTexto);
    cputchar('H'); 

    return 0;
}
