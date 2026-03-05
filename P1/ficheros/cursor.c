#include <stdio.h>
#include <dos.h>

// Ejercicio P1: setcursortype()
// Fijar el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO.  


void mi_pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

/*int mi_getchar(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

void mi_putchar(char c){
	 union REGS inregs, outregs;

	 inregs.h.ah = 2;
	 inregs.h.dl = c;
	 int86(0x21, &inregs, &outregs);
}
*/
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
