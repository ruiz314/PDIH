# Práctica 3. Experimentación con Arduino
En esta práctica se propone crear y verificar el funcionamiento de diversos sistemas de control basados en Arduino.

## Requisitos mínimos
### Ejercicio 1
Implementar el programa de parpadeo de LED, ampliándolo para que encienda y apague alternativamente tres LEDs (uno rojo, otro amarillo y otro verde), conectados a las salidas digitales 11, 12 y 13 del Arduino, a un intervalo de 1.5 segundos. Simular primero el prototipo en Tinkercad y sacar captura de pantalla del prototipo (esquema) para incluirla en el documento de la práctica. 
A continuación, cargar el programa en el Arduino físico para comprobar que funciona correctamente (incluir foto en el documento de la práctica). 

La implementación en Tinkercad:
```c
const int ledPinR = 11; // LED Rojo
const int ledPinA = 12; // LED Amarillo
const int ledPinV = 13; // LED Verde

void setup() {
 pinMode(ledPinR, OUTPUT); 
 pinMode(ledPinA, OUTPUT); 
 pinMode(ledPinV, OUTPUT);

}

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

Este código hace que primero se encienda el led rojo, espera 1 segundo y enciende el amarillo, espera otro segundo y enciende el verde. Cuando están todos encendidos espera un segundo y apaga el rojo. De nuevo espera un segundo y apaga el amatillo, y por último espera un segundo y apaga el LED verde.

Las resistencias que se han usado tiene un valor de $1k$ Ohmios.

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_ejer1.png)

Fichero: [ejercicio1.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejercicio1.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/8cUpHRQn0iU/editel?sharecode=hjc5ENfjtw7kgeIf3-wHUPApSd_4_OOuukVCIAQ3KEU)


Si queremos que solo se encienda un LED a la vez, entonces el orden de encendido y apagado debe ser distinto:

```c
const int ledPinR = 11; // LED Rojo
const int ledPinA = 12; // LED Amarillo
const int ledPinV = 13; // LED Verde

void setup() {
 pinMode(ledPinR, OUTPUT); 
 pinMode(ledPinA, OUTPUT); 
 pinMode(ledPinV, OUTPUT);

}

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
![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_ejer1modif.png)

Fichero: [ejercicio1.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer1_modif.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/gaBwdn6BxZt/editel?sharecode=IK2mjVQ69bJlynbLdLMnaqxHddvf1faAzySnm4B8esI)

### Ejercicio 2
Partir del programa de parpadeo de LEDs anterior y ampliarlo con las modificaciones necesarias para que se encienda el LED rojo solo cuando se pulse un interruptor conectado a la entrada digital 7, y en ese momento se apaguen los LEDs amarillo y verde. Simular primero el prototipo en Tinkercad y 
sacar captura de pantalla del prototipo (esquema) para incluirla en el documento de la práctica. A continuación, cargar el programa en el Arduino físico para comprobar que funciona correctamente (incluir foto en el documento 
de la práctica).

## Requisitos ampliados
### Ejercicio 1
Secuencia de LEDs, encendiendo y apagando 4 LEDs secuencialmente, de forma similar a las lucecitas de "El coche fantástico".

### Ejercicio 2
Detector de la distancia a un objeto (usar el buzzer para hacer sonar un pitido en función de la distancia detectada por el sensor de ultrasonidos). 

### Ejercicio 3
Detector de la cantidad de luz que haya en ese momento (usar un LED que se ilumine más o menos en función de la cantidad de luz detectada con el fotosensor). 

### Ejercicio 4 
Implementar un proyecto en el que se active un motor (DC Motor o Servo motor) cuando se pulse un pulsador. 
