# Práctica 3. Experimentación con Arduino
En esta práctica se propone crear y verificar el funcionamiento de diversos sistemas de control basados en Arduino.

## Requisitos mínimos
### Ejercicio 1 - Parpadeo de LEDs
Implementar el programa de parpadeo de LED, ampliándolo para que encienda y apague alternativamente tres LEDs (uno rojo, otro amarillo y otro verde), conectados a las salidas digitales 11, 12 y 13 del Arduino, a un intervalo de 1.5 segundos. Simular primero el prototipo en Tinkercad y sacar captura de pantalla del prototipo (esquema) para incluirla en el documento de la práctica. 
A continuación, cargar el programa en el Arduino físico para comprobar que funciona correctamente (incluir foto en el documento de la práctica). 

Primero hay que asignar los pines digitales a los LED:
- pin 11 -> LED rojo
- pin 12 -> LED amarillo
- pin 13 -> LED verde
  
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

Por último, se hace la lógica de encendido y apagado en la función `loop`.

#### Versión 1 
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

A continuación se muestra una imagen de las **conexiones eléctricas** en Tinkercad:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_ejer1.png)

Como se puede observar, los **componentes eléctricos** utilizados son:
- Placa Arduino UNO.
- _Breadboard_ (placa de pruebas).
- Tres resistencias de 1k Ohmios cada una. Es por eso que los colores son café, negro y rojo.
- Tres LEDs (de distintos colores)
- _Jumper wires_ (cables) para la unión de los componentes entre sí.

Al montar el circuito en la placa Arduino queda así:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_intermitentes.jpg)

Para probar el programa uso el IDE de Arduino para cargar el código en la placa. Primero verifico que el código esté correcto:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_compilacion.png)

Una vez que se ha verificado el código, lo cargo en la tarjeta Arduino pulsando la flecha de la esquina superior izquierda:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_cargar.png)

Video de la simulación:
[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_intermitentes.jpg)](https://github.com/ruiz314/PDIH/blob/main/P3/img/1intermitentesVID.mp4)

Fichero: [ejercicio1.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejercicio1.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/8cUpHRQn0iU/editel?sharecode=hjc5ENfjtw7kgeIf3-wHUPApSd_4_OOuukVCIAQ3KEU)

#### Versión 2
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

En este caso el circuito físico no cambia, queda igual que para la primera versión. Para probar el código hay
que verificarlo desde el IDE y cargar el código en el Arduino como se ha hecho para la primera versión.

Video de la simulación:
[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/1_intermitentes.jpg)](https://github.com/ruiz314/PDIH/blob/main/P3/img/1intermitentesV2VID.mp4)

Fichero: [ejercicio1modificado.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer1_modif.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/gaBwdn6BxZt/editel?sharecode=IK2mjVQ69bJlynbLdLMnaqxHddvf1faAzySnm4B8esI)

### Ejercicio 2 - Parpadeo de LEDs con interruptor
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

Esquema de **conexiones eléctricas** en Tinkercad:
![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/2_ejer2.png)

Como se puede observar de la imagen de Tinkercad, los **componentes eléctricos** utilizados son:
- Placa Arduino UNO.
- _Breadboard_ (placa de pruebas).
- Pulsador (interruptor).
- Una resistencia de 10k Ohmios para el pulsador. Sus colores son: café, negro y naranja.
- Tres resistencias de 220 Ohmios cada una para los LEDs. Es por eso que los colores son rojo, rojo y café.
- Tres LEDs (de distintos colores)
- _Jumper wires_ (cables) para la unión de los componentes entre sí.

Al montar el circuito en la placa Arduino queda así:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/2_boton.jpg)

Video de la simulación:

[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/2_boton.jpg)](https://github.com/ruiz314/PDIH/blob/main/P3/img/2_botonVID.mp4)

Fichero: [ejercicio2.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer2.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/0rUjCbYO3RQ-p3ejer2/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fcollections%2Ff93vEWIxIhX%2Fall&sharecode=0m4p8z0yxeT1PuAEVyzAVbusQKUiD8RQ8YmMp3ujcz4)

## Requisitos ampliados
### Ejercicio 1 - Secuencia de cuatro LEDs
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

A continuación se muestra una imagen de las **conexiones eléctricas** para este ejercicio:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/3_ejer3luces.png)

Como se puede observar de la imagen de Tinkercad, los **componentes eléctricos** utilizados son:
- Placa Arduino UNO.
- _Breadboard_ (placa de pruebas).
- Cuatro resistencias de 1k Ohmios cada una. Sus colores son: café, negro y rojo.
- Cuatro LEDs (de distintos colores)
- Jumper wires (cables) para la unión de los componentes entre sí.

Video de la simulación:

[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/3_ejer3luces.png)](https://github.com/ruiz314/PDIH/blob/main/P3/img/3_ejer3.mp4)

El diseño del circuito físico queda así:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/3_ejer3circuito.jpg)

Video:

[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/3_ejer3_secuencia.jpg)](https://github.com/ruiz314/PDIH/blob/main/P3/img/3_ejer3_secuenciaLED.mp4)

Fichero: [ejercicio3.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer3.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/7IiRztn3ZZV/editel?sharecode=9raEkBkbUV031nzYe7hsnvjDtU9ZpSUxcQ8BiVlgLQ0)

### Ejercicio 2 - Detector de distancia
Detector de la distancia a un objeto (usar el buzzer para hacer sonar un pitido en función de la distancia detectada por el sensor de ultrasonidos). 

Para medir las distancias se usa un ultrasonido $HC - SR04$ con las siguientes señales:
- VCC conectado a la alimentación de 5 voltios de la placa Arduino
- GND conectado a la Tierra de la placa
- TRIG (Señal de disparo) al pin $11$ de Arduino
- ECHO (Señal de eco) al pin $12$ de Arduino

Además, para emitir el pitido se usa un _buzzer_ que conecto al pin $10$ de Arduino, y el otro pin a tierra.
```c
const int echoPin = 12;
const int trigPin = 11;
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

Imágen de las **conexiones eléctricas** del circuito:

![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/4_ejer4.png)

En la imagen se observa qye los **componentes eléctricos** utilizados son:
- Placa Arduino UNO.
- _Breadboard_ (placa de pruebas).
- _Ultrasonic Distance Sensor_ (4-pin) (Sensor de ultra sonido con 4 pines).
- _Piezo_ (zumbador) para emitir sonido.
- _Jumper wires_ (cables) para la unión de los componentes entre sí.

Imagen del circuito físico:
![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/4_ejer4buzz.jpg)

Video del circuito físico:

[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/4_ejer4buzz.jpg)](https://github.com/ruiz314/PDIH/blob/main/P3/img/4_ejer4.mp4)

Fichero: [ejercicio4.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer4.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/9mgfdPeUUIt-p3ejer4/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fcollections%2Ff93vEWIxIhX%2Fall&sharecode=GHlIEY_WpEDHnj7l7oeITgtpOTbkQp_1Wjgztlc24RY)

### Ejercicio 3
Detector de la cantidad de luz que haya en ese momento (usar un LED que se ilumine más o menos en función de la cantidad de luz detectada con el fotosensor). 

Para detectar distintos niveles de luz se necesita un **fotosensor** que vaya conectado a un pin analógico: $A0$ en este caso. Además, la otra patilla irá conectada a tierra y a una resistencia de $10 kΩ$. El LED debe estar conectado en un pin que tenga el símbolo `~`, es decir, que soporte PWM (Modulación por Ancho de Pulsos) para poder regular el nivel de brillo.
```c
const int luzPin = A0;  // Sensor de luz
const int ledPin = 9;   // LED

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(luzPin, INPUT); 
  
  // Inicializar el monitor serie
  Serial.begin(9600);
}
```

Una vez inicializadas las variables que indican los pines, programamos la lógica del problema:
```c
void loop() {
  // Lectura del sensor
  int nivelLuz = analogRead(luzPin);

  // Conversión de escalas
  int brilloLED = map(nivelLuz, 0, 1023, 0, 255);

  // Ajuste de brillo de brillo
  analogWrite(ledPin, brilloLED);

  // Mostrar en monitor serie
  Serial.print("Luz detectada: ");
  Serial.print(nivelLuz);
  Serial.print(" | Nivel de brillo (PWM): ");
  Serial.println(brilloLED);

  // Pequeña pausa para estabilizar las lecturas
  delay(1000);
}
```
- _analogRead(luzPin)_: lee el voltaje que deja pasar el fotosensor y lo transforma en un valor comprendido entre 0 (oscuridad total) y 1023 (luz máxima).
- _map(valor, fromLow, fromHigh, toLow, toHigh)_: traduce proporcionalmente el rango del sensor al rango del LED. El sensor da un valor hasta 1023, pero el LED solo admite niveles de brillo hasta 255.
- _analogWrite(ledPin, valor)_: enciende y apaga el pin de forma que parezca que el LED tiene varias intensidades de brillo.

Imágen de las **conexiones eléctricas** del circuito:
![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/5_ejer5circuito.png)

En la imagen se observa qye los **componentes eléctricos** utilizados son:
- Placa Arduino UNO.
- _Breadboard_ (placa de pruebas).
- LED (verde)
- Fotosensor
- Una resistencia de 220Ω para el LED y otra de 10kΩ para el fotosensor.
- _Jumper wires_ (cables) para la unión de los componentes entre sí.
  
Imagen del circuito físico:
![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/5_ejer5fotosensor.jpg)

Video del circuito físico:

[![Watch the video](https://github.com/ruiz314/PDIH/blob/main/P3/img/5_ejer5fotosensor.jpg)](https://github.com/ruiz314/PDIH/blob/main/P3/img/5_ejer5.mp4)

Fichero: [ejercicio5.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer5.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/8Y2OIWiWnKP-p3ejer5/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fcollections%2Ff93vEWIxIhX%2Fall&sharecode=yDFOFjNgw1Dakdx7i2RQen3KdP0OUzZfTqOxnnYpmYQ)

### Ejercicio 4 
Implementar un proyecto en el que se active un motor (DC Motor o Servo motor) cuando se pulse un pulsador. 

Para conectar el pulsador lo haremos igual que en el _ejercicio 2_ de los requisitos mínimos: un terminal del botón va a $5V$, y el otro terminal se conecta simultáneamente al pin digital $7$ y a tierra (GND) mediante una resistencia de $10k$ Ohmios.

El servomotor tiene tres cables: El cable rojo (alimentación) se conecta a los 5V del Arduino, el cable negro (tierra) se conecta a GND, y el tercer cable (naranja) es el de control de señal que va conectado al pin digital 9.

```c
// Libreria para trabajar con servomotores
#include <Servo.h> 

// Declaracion de pines
const int servoPin = 9; // Senal del servomotor
const int botonPin = 7; // Pulsador

int estadoBoton =0;
Servo miServo;

void setup()
{
  pinMode(botonPin, INPUT); //  Pin del boton como entrada
  miServo.attach(servoPin); // Vincular servo al pin fisico
  miServo.write(0); //Posicion a 0 grados
}
```

La función `attach(pin)` se usa para inicializar la instancia de nuestro motor físico. Indica el pin físico al que enviar la corriente para mover el motor.

Por último se implementa la lógica de giro tras pulsar el interruptor. Primero se lee el estado del botón, y en función de si está pulsado o no se mueve el motor o no se mueve.
```c
void loop()
{
  // Leer estado del botón
  estadoBoton = digitalRead(botonPin);
  
  // Control del motor
  if(estadoBoton == HIGH){ //Si el botón esta pulsado
    miServo.write(180); // Girar el motor 90 grados
  }else{ // Si el botón no esta pulsado
  	miServo.write(0); // No girar
  }
  
  // Pausa
  delay(15);
}
```

La función `write(grados)` gira el motor exactamente hasta ese ángulo indicado en _grados_.

Imágen de las **conexiones eléctricas** del circuito en Tinkercad:
![img](https://github.com/ruiz314/PDIH/blob/main/P3/img/5_ejer6.png)

En la imagen se observa qye los **componentes eléctricos** utilizados son:
- Placa Arduino UNO.
- _Breadboard_ (placa de pruebas).
- Pulsador (interruptor)
- Servomotor
- Una resistencia de 10kΩ para el pulsador. Sus colores son: café, negro y naranja.
- _Jumper wires_ (cables) para la unión de los componentes entre sí.
  
Fichero: [ejercicio6.ino](https://github.com/ruiz314/PDIH/blob/main/P3/ficheros/ejer6.ino)

[Link a proyecto en Tinkercad](https://www.tinkercad.com/things/6opNGlCy2VE-p3ejer6/editel?returnTo=%2Fdashboard%2Fdesigns%2Fall&sharecode=yZj4DiLdb2XZNTpwrQ5lG4Q49mgYi61C-GD97jd8Ncs)
