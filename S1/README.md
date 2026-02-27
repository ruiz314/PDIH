# Seminario 1. Programación de dispositivos a bajo nivel 
Ejercicios planteados en el seminario:

## 1. Instalar el software DOSBox y ejecutar aplicaciones de MS-DOS (p.ej. juegos clásicos). 

![img](https://github.com/ruiz314/PDIH/blob/main/S1/S1_ejer1.png)

## 2. Configurar el inicio de DOSBox para que monte en la unidad C: el directorio donde se encuentra el entorno de programación Borland C (que incluye las herramientas para compilar no sólo lenguaje C, sino también ensamblador). Añadir a la variable “PATH” de inicio el directorio “bin” donde se encuentra el ejecutable BC.EXE 
La ruta en mi ordenador del fichero a modificar es: `C:\Users\inesr\AppData\Local\DOSBox\dosbox-0.74-3.conf`

Al final del fichero hay que modificar y añadir:
```bash
[autoexec]
# Lines in this section will be run at startup.
# You can put your MOUNT lines here.

mount C C:\DOSBOX
keyb sp
path c:\bc\bin
```

Enlace al fichero completo: [dosbox-0.74-3.conf](https://github.com/ruiz314/PDIH/blob/main/S1/dosbox-0.74-3.conf)

## 3. Crear el ejemplo “Hola mundo” en ensamblador, compilarlo y comprobar su funcionamiento. A continuación incluir un bucle para mostrar el mensaje 7 veces. 
Ejemplo "Hola mundo":

```
pila segment stack 'stack'
	dw 100h dup (?)
pila ends
datos segment 'data'
	msg db 'hola mundo$'
datos ends
codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax

		mov dx,OFFSET msg
		mov ah,9
		int 21h

		mov ax,4C00h
		int 21h
	main ENDP
codigo ends

END main

```
![img](https://github.com/ruiz314/PDIH/blob/main/S1/S1_ejer3_hola_mundo.png)

Uso el fichero C.BAT que viene en el guion:

![img](https://github.com/ruiz314/PDIH/blob/main/S1/S1_ejer3_c_bat.png)

Al ejecutar se muestra el mensaje:

![img](https://github.com/ruiz314/PDIH/blob/main/S1/S1_ejer3_ejecucion1.png)

Ejemplo con el bucle:
```
pila segment stack 'stack'
	dw 100h dup (?)
pila ends
datos segment 'data'
	msg db 'hola mundo$'
datos ends
codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax

		mov cx,0 ;contador de bucle

		bucle:
			mov dx,OFFSET msg
			mov ah,9
			int 21h

			int cx
			cmp c,5
			jne bucle
		
	main ENDP
codigo ends

END main
```
