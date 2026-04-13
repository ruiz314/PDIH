# Práctica 3. Experimentación con Arduino
En esta práctica se propone crear y verificar el funcionamiento de diversos sistemas de control basados en Arduino.

## Requisitos mínimos
### Ejercicio 1
Implementar el programa de parpadeo de LED, ampliándolo para que encienda y apague alternativamente tres LEDs (uno rojo, otro amarillo y otro verde), conectados a las salidas digitales 11, 12 y 13 del Arduino, a un intervalo de 1.5 segundos. Simular primero el prototipo en Tinkercad y sacar captura de pantalla del prototipo (esquema) para incluirla en el documento de la práctica. 
A continuación, cargar el programa en el Arduino físico para comprobar que funciona correctamente (incluir foto en el documento de la práctica). 

Primero hay que asignar los pines digitales a los LED:
```c
const int ledPinR = 11; // LED Rojo
const int ledPinA = 12; // LED Amarillo
const int ledPinV = 13; // LED Verde
```

Una vez asignados los pines hay que configurarlos como salidas con la función `pinMode(ledPin, OUTPUT)`:

```c
void setup() {
 pinMode(ledPinR, OUTPUT); 
 pinMode(ledPinA, OUTPUT); 
 pinMode(ledPinV, OUTPUT);
}
```

Por último, se hace la lógica de encendido y apagado en la función `loop`:
```c
void loop() {
  // Encender
  digitalWrite(ledPinR, HIGH); // LED Rojo
  delay(1000);
  digitalWrite(ledPinA, HIGH); // LED Amarillo
  delay(1000);
  digitalWrite(ledPinV, HIGH); // LED Verde
  delay(1000);
  
  // Apagar
  digitalWrite(ledPinR, LOW); // LED Rojo
  delay(1000);
  digitalWrite(ledPinA, LOW); // LED Amarillo
  delay(1000);
  digitalWrite(ledPinV, LOW); // LED Verde
  delay(1000);
}
```

Este código hace que primero se encienda el led rojo, espera 1 segundo y enciende el amarillo, espera otro segundo y enciende el verde. Cuando están todos encendidos espera un segundo y apaga el rojo. De nuevo espera un segundo y apaga el amarillo, y por último espera un segundo y apaga el LED verde.

Las resistencias que se han usado tienen un valor de $1k$ Ohmios.

A continuación se muestra una imagen del circuito en Tinkercad:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_ejer1.png)

Fichero: [ejercicio1.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejercicio1.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/8cUpHRQn0iU/editel?sharecode=hjc5ENfjtw7kgeIf3-wHUPApSd_4_OOuukVCIAQ3KEU)

Al montar el circuito en la placa Arduino queda así:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_intermitentes.jpg)

Video de la simulación:
[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_intermitentes.jpg)](https://github.com/ruiz314/PDIH/blob/main/P3/img/1intermitentesVID.mp4)

Si queremos que solo se encienda un LED a la vez, entonces el orden de encendido y apagado debe ser distinto. Para eso solo hace falta cambiar la función `loop` anterior:

```c
void loop() {
  // Encender Rojo, resto apagado
  digitalWrite(ledPinR, HIGH); // LED Rojo
  digitalWrite(ledPinA, LOW); // LED Amarillo
  digitalWrite(ledPinV, LOW); // LED Verde
  delay(1500);
  
  // Encender Amarillo, resto apagado
  digitalWrite(ledPinA, HIGH); // LED Amarillo
  digitalWrite(ledPinR, LOW); // LED Rojo
  digitalWrite(ledPinV, LOW); // LED Verde
  delay(1500);
  
  
  // Encender Verde, resto apagado
  digitalWrite(ledPinV, HIGH); // LED Verde
  digitalWrite(ledPinR, LOW); // LED Rojo
  digitalWrite(ledPinA, LOW); // LED Amarillo
  delay(1500);
}
```

Esta función solo permite que haya un LED encendido, mientras los otros dos estarán apagados.

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_ejer1modif.png)

Fichero: [ejercicio1modificado.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer1_modif.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/gaBwdn6BxZt/editel?sharecode=IK2mjVQ69bJlynbLdLMnaqxHddvf1faAzySnm4B8esI)

Video de la simulación:
[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_intermitentes.jpg)](https://github.com/ruiz314/PDIH/blob/main/P3/img/1intermitentesV2VID.mp4)

### Ejercicio 2
Partir del programa de parpadeo de LEDs anterior y ampliarlo con las modificaciones necesarias para que se encienda el LED rojo solo cuando se pulse un interruptor conectado a la entrada digital 7, y en ese momento se apaguen los LEDs amarillo y verde. Simular primero el prototipo en Tinkercad y sacar captura de pantalla del prototipo (esquema) para incluirla en el documento de la práctica. A continuación, cargar el programa en el Arduino físico para comprobar que funciona correctamente (incluir foto en el documento 
de la práctica).

Primero se asignan el número del pin a los elementos usados en el circuito:
```c
const int ledPinR = 11; // LED Rojo
const int ledPinA = 12; // LED Amarillo
const int ledPinV = 13; // LED Verde
const int botonPin = 7; // Pulsador
int estadoBoton =0;
```
Además, uso una variable para saber si el botón está pulsado o no.

Segundo, se establecen los estados de los LED y el botón:
```c
void setup() {
 pinMode(ledPinR, OUTPUT);  
 pinMode(ledPinA, OUTPUT); 
 pinMode(ledPinV, OUTPUT);  
 pinMode(botonPin, INPUT);
}
```

En este caso todos los pines de los LEDs están configurados como salidas digitales, excepto el pin para el botón (debe escuchar las señales externas).


Por último se aplica la lógica necesaria para que el botón encienda la luz roja y apague el resto:
```c
void loop() {
  // Leer estado del boton
  estadoBoton = digitalRead(botonPin);
  
  // Comprobar si esta pulsado
  if(estadoBoton == HIGH){ // Boton pulsado
  	// Encender Rojo, resto apagado
  	digitalWrite(ledPinR, HIGH); // LED Rojo
  	digitalWrite(ledPinA, LOW); // LED Amarillo
  	digitalWrite(ledPinV, LOW); // LED Verde
  	delay(1500);
  }else{
  	// Encender Amarillo, resto apagado
  	digitalWrite(ledPinA, HIGH);
  	digitalWrite(ledPinR, LOW); 
    digitalWrite(ledPinV, LOW); 
  	delay(1500);
  
  	// Encender Verde, resto apagado
  	digitalWrite(ledPinV, HIGH);
  	digitalWrite(ledPinR, LOW); 
    digitalWrite(ledPinA, LOW); 
  	delay(1500);
  }
}
```

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/2_ejer2.png)

Fichero: [ejercicio2.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer2.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/0rUjCbYO3RQ-p3ejer2/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fcollections%2Ff93vEWIxIhX%2Fall&sharecode=0m4p8z0yxeT1PuAEVyzAVbusQKUiD8RQ8YmMp3ujcz4)


Al montar el circuito en la placa Arduino queda así:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/2_boton.jpg)

Video de la simulación:

[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/2_boton.jpg)](https://github.com/ruiz314/PDIH/blob/main/P3/img/2_botonVID.mp4)

## Requisitos ampliados
### Ejercicio 1
Secuencia de LEDs, encendiendo y apagando 4 LEDs secuencialmente, de forma similar a las lucecitas de "El coche fantástico".

Como en los dos primeros ejercicios, empiezo declarando las constantes para los pines de los LEDs y establezco los modos:

```c
const int ledPinB = 10; // LED Blanco
const int ledPinR = 11; // LED Rojo
const int ledPinA = 12; // LED Amarillo
const int ledPinV = 13; // LED Verde

void setup() {
 pinMode(ledPinB, OUTPUT); 
 pinMode(ledPinR, OUTPUT); 
 pinMode(ledPinA, OUTPUT); 
 pinMode(ledPinV, OUTPUT);
}
```

La lógica del encendido y apagado es la siguiente:
```c
void loop() {
  // Encender Rojo, resto apagado
  digitalWrite(ledPinR, HIGH); // LED Rojo
  digitalWrite(ledPinA, LOW); // LED Amarillo
  digitalWrite(ledPinV, LOW); // LED Verde
  digitalWrite(ledPinB, LOW); // LED Blanco
  delay(500);
  
  // Encender Amarillo, resto apagado
  digitalWrite(ledPinR, LOW); // LED Rojo
  digitalWrite(ledPinA, HIGH); // LED Amarillo
  digitalWrite(ledPinV, LOW); // LED Verde
  digitalWrite(ledPinB, LOW); // LED Blanco
  delay(500);
  
  // Encender Verde, resto apagado
  digitalWrite(ledPinV, HIGH); // LED Verde
  digitalWrite(ledPinR, LOW); // LED Rojo
  digitalWrite(ledPinA, LOW); // LED Amarillo
  digitalWrite(ledPinB, LOW); // LED Blanco
  delay(500);
  
  // Encender Blanco, resto apagado
  digitalWrite(ledPinB, HIGH); // LED Blanco
  digitalWrite(ledPinV, LOW); // LED Verde
  digitalWrite(ledPinR, LOW); // LED Rojo
  digitalWrite(ledPinA, LOW); // LED Amarillo
  delay(500);
}
```

El bucle está dividido en cuatro bloques, uno por cada LED. En cada bloque se envía una señal _HIGH_ a un solo LED, mientras que al resto se le envía una señal _LOW_ para que estén apagados. Al cambiar los estados de los pines de los LEDs se llama a la función `delay(500)` para detener el microcontrolador durante medio segundo y así crear el efecto de que la luz "salta" de un LED a otro.

Imágen del circuito:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/3_ejer3luces.png)

Video de la simulación:

[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/3_ejer3luces.png)](https://github.com/ruiz314/PDIH/blob/main/P3/img/3_ejer3.mp4)

Fichero: [ejercicio3.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer3.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/7IiRztn3ZZV/editel?sharecode=9raEkBkbUV031nzYe7hsnvjDtU9ZpSUxcQ8BiVlgLQ0)

### Ejercicio 2
Detector de la distancia a un objeto (usar el buzzer para hacer sonar un pitido en función de la distancia detectada por el sensor de ultrasonidos). 

Para medir las distancias se usa un ultrasonido $HC - SR04$ con las siguientes señales:
- VCC conectado a la alimentación de 5 voltios de la placa Arduino
- GND conectado a la Tierra de la placa
- TRIG (Señal de disparo) al pin $12$ de Arduino
- ECHO (Señal de eco) al pin $11$ de Arduino

Además, para emitir el pitido se usa un _buzzer_ que conecto al pin $10$.
```c
const int trigPin = 12;
const int echoPin = 11;
const int buzzPin = 10;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600); // Para monitor serie
}
```

La función `Serial.begin(speed)` pertenecen a la biblioteca estándar de comunicación. Inicializa el puerto serie a $9600$ baudios para monitorizar.

En la función `loop` se genera el pulso, se calcula la distancia y se controla el zumbador. Se usa la función `pulseIn(pin, value)` que mide el tiempo (en microsegundos) que un pin permanece en un estado específico (en este caso, HIGH). Sirve para cronometrar cuánto tiempo tarda el eco del sonido en regresar al Arduino.

```c
  // Disparo ultrasonico
  digitalWrite(trigPin, LOW);
  delay(2); // Wait for 2 milliseconds
  digitalWrite(trigPin, HIGH);
  delay(2);
  digitalWrite(trigPin, LOW);
  
  // Leer duracion
  duracion = pulseIn(echoPin, HIGH);
  
  //Calcular distancia
  distancia = duracion * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.println(distancia);
```

La fórmula matemática $distancia = duracion * 0.034 / 2$ se basa en la constante física de la velocidad del sonido en el aire, que es de aproximadamente $0.034$ centímetros por microsegundo, dividiéndose entre dos porque el cronómetro mide el tiempo que el sonido tarda en viajar hasta el objeto y regresar.

Las funciones `Serial.print()` y `Serial.println()` permiten enviar cadenas de texto e imprimir variables numéricas en el Monitor Serie.

Por último, con la función `tone(pin, frequency, duration)` se emiten sonidos a través del zumbador. El tercer parámetro (duration) es opcional pero así no es necesario usar `delay()`.
```c
//Control de buzzer segun la distancia
  if (distancia <= 60){
  	tone(buzzPin, 1400, 600); 
  }else if(distancia >60 && distancia <= 150){
  	tone(buzzPin, 900, 400);
  }else{ // Silencio si no hay objeto cerca
  	noTone(buzzPin);
  }
  delay(100);
```

La función `noTone(pin)` detiene inmediatamente la generación de sonido en un pin. Se utiliza para asegurar un silencio total cuando el objeto está lejos.

Imágen del circuito:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/4_ejer4buzz.png)

Video de la simulación:

[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/4_ejer4buzz.png)](https://github.com/ruiz314/PDIH/blob/main/P3/img/4_ejer4.mp4)

Fichero: [ejercicio4.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer4.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/9mgfdPeUUIt-p3ejer4/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fcollections%2Ff93vEWIxIhX%2Fall&sharecode=GHlIEY_WpEDHnj7l7oeITgtpOTbkQp_1Wjgztlc24RY)

### Ejercicio 3
Detector de la cantidad de luz que haya en ese momento (usar un LED que se ilumine más o menos en función de la cantidad de luz detectada con el fotosensor). 

### Ejercicio 4 
Implementar un proyecto en el que se active un motor (DC Motor o Servo motor) cuando se pulse un pulsador. 
