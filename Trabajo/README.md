# Código Morse usando Arduino
Memoria del proyecto: [doc/memoria.pdf](https://github.com/ruiz314/PDIH/blob/main/Trabajo/doc/memoria_proyecto.pdf)

Carpeta con videos: [enlace a Drive](https://drive.google.com/drive/folders/1-nxhgiJg5rF9BGvR2GCVBDPSpM-96K7R?usp=sharing)

Presentación: [enlace a Canva](https://canva.link/apihdbxe9odjvdp)

## Introducción

En la asignatura de _Periféricos y Dispositivos de Interfaz Humana_ se ha demostrado que la comunicación entre el usuario y el sistema informático es muy importante. Es por eso que he escogido como trabajo de la asignatura la traducción del código Morse con la placa Arduino ya que fue una de las primeras formas de comunicar información con señales binarias de distinta duración.


### ¿Qué es el código Morse?
El código Morse es un sistema de representación de letras y números mediante una secuencia de señales intermitentes. Al igual que en la escritura se usa un espacio para separar palabras, en el código morse se usan pausas (silencio) para separar caracteres.

Se establecen unas reglas:
- La duración de una raya es tres veces la de un punto.
- El tiempo que transcurre entre cada raya o punto es igual a la duración de un punto.
- El espacio entre dos letras tiene la misma longitud que la raya.
- El espacio entre dos palabras tiene la misma duración que cuatro puntos.

La codificación empleada para la traducción es la siguiente:

| Caracter | Código | Caracter | Código | Caracter | Código | Caracter | Código |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **A** | $.-$ | **J** | $.---$ | **S** | $...$ | **1** | $.----$ |
| **B** | $-...$ | **K** | $-.-$ | **T** | $-$ | **2** | $..---$ |
| **C** | $-.-.$ | **L** | $.-..$ | **U** | $..-$ | **3** | $...--$ |
| **D** | $-..$ | **M** | $--$ | **V** | $...-$ | **4** | $....-$ |
| **E** | $.$ | **N** | $-.$ | **W** | $.--$ | **5** | $.....$ |
| **F** | $..-.$ | **O** | $---$ | **X** | $-..-$ | **6** | $-....$ |
| **G** | $--.$ | **P** | $.--.$ | **Y** | $-.--$ | **7** | $--...$ |
| **H** | $....$ | **Q** | $--.-$ | **Z** | $--..$ | **8** | $---..$ |
| **I** | $..$ | **R** | $.-.$ | **0** | $-----$ | **9** | $----.$ |

### Objetivo del proyecto
Este proyecto se centra en cómo un microcontrolador puede actuar como un traductor, convirtiendo texto digital en señales físicas y viceversa.
- **Codificador** - **Modo Transmisor**. Programar el Arduino para que, dada una cadena de texto (enviada desde el ordenador por el puerto serie), el Arduino la traduzca y la emita haciendo parpadear un LED y sonando un zumbador (buzzer) con los tiempos exactos del código Morse (punto corto, raya larga).
- **Decodificador** - **Modo Receptor**. Conectar un pulsador (botón) al Arduino. El usuario hará pulsaciones cortas y largas. El programa deberá medir el tiempo que el botón está pulsado para distinguir entre "puntos" y "rayas", agruparlos, y mostrar por el monitor serie (y/o en una pequeña pantalla) la letra o palabra que se está tecleando.

## Diseño Hardware
### Listado de componentes
Para hacer un **transmisor** de código Morse los **componentes eléctricos** necesarios son:
- Placa Arduino UNO
- Placa de pruebas (_protoboard_)
- Resistencia de $270$ Ohmios
- LED en el pin 12
- Buzzer (altavoz piezoeléctrico)
- Cables para conectar los componentes
- Cable USB para conectar placa Arduino con el ordenador

Los **componentes eléctricos** utilizados para el **receptor** de código Morse son:
- Placa Arduino UNO
- Placa de pruebas (_protoboard_)
- Cables para conectar los componentes
- Cable USB para conectar placa Arduino con el ordenador
- Display a elegir
  - Display de 7 segmentos
  - Matriz LED 8x8
  - Pantalla LCD
  - Pulsador
  - Resistencia 10k Ohmios

### Esquema de conexión
#### Circuito del módulo **Transmisor**:

**Versión 1** - Señal luminosa.
![img](https://github.com/ruiz314/PDIH/blob/main/Trabajo/doc/images/transmisor_v1.png)

Se puede observar que el **LED** está conectado al **pin 12** del Arduino. 

**Versión 2** - Señal luminosa y acústica.
![img](https://github.com/ruiz314/PDIH/blob/main/Trabajo/doc/images/transmisor_v2.png)

El terminal positivo del **buzzer** está conectado al **pin 11** del Arduino.

#### Circuito del módulo **Receptor**:

**Versión 1** - Sin display.
![img](https://github.com/ruiz314/PDIH/blob/main/Trabajo/doc/images/receptor_v1.png)

El pulsador está conectado al **pin 7** del Arduino.

**Versión 2** - Display de 7 segmentos

![img](https://github.com/ruiz314/PDIH/blob/main/Trabajo/doc/images/receptor7_ej1.png)

Esta versión solo la he simulado en Tinkercad, no disponía del display físico.

**Versión 3** - Matriz LED 8x8

![img](https://github.com/ruiz314/PDIH/blob/main/Trabajo/doc/images/4_receptor_circuito_v3.jpg)

Este componente no está en Tinkercad por lo que no he podido simularlo antes de montar el circuito físico.

## Desarrollo Software

### Módulo Transmisor (Texto a Morse)
Permite escribir una frase en nuestro ordenador y hacer que la placa Arduino lo convierta en los puntos y rayas apropiados del código Morse encendiendo y apagando un LED.

Versión 1: [transmisor_v1.ino](https://github.com/ruiz314/PDIH/blob/main/Trabajo/ficheros/transmisor_v1.ino)

Versión 2: [transmisor_v2.ino](https://github.com/ruiz314/PDIH/blob/main/Trabajo/ficheros/transmisor_v2.ino)


### Módulo Receptor (Morse a Texto)
La placa Arduino mide la duración de la señal digital enviada con el interruptor para interpretarla según las reglas del código Morse.

Versión 1: [receptor_v1.ino](https://github.com/ruiz314/PDIH/blob/main/Trabajo/ficheros/receptor_v1.ino)

Versión 3: [receptor_v3.ino](https://github.com/ruiz314/PDIH/blob/main/Trabajo/ficheros/receptor_v3.ino)
