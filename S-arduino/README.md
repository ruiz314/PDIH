# Seminario. Introducción al uso de Arduino 
## Ejemplo Blink
El	“Hola	Mundo”	de	Arduino:	hacer	parpadear	un	LED.

En el ejemplo de Tinkercad viene por defecto el programa que nos da el profesor, pero en vez de indicar el número del pin se usa la constante `LED_BUILTIN`.

```c
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
```

![img1](https://github.com/ruiz314/PDIH/blob/main/S-arduino/img/S_blink1.png)

Ahora probando el código dado por el profesor:

```c
// Función de configuración
void setup() {
 pinMode(13, OUTPUT); // Indica el modo en el que usamos el pin número 13. En este caso es para salida
}

// Bucle infinito
void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
```

![img2](https://github.com/ruiz314/PDIH/blob/main/S-arduino/img/S_blink2.png)

## Ejercicio 1
Implementar el programa de parpadeo de LED, ampliándolo para que encienda y apague alternativamente dos LED (uno rojo y otro verde), conectados a las salidas digitales 12 y 13 del Arduino, a un intervalo de 1.5 segundos. Crear el esquema con Fritzing y cargar el programa en Arduino para comprobar que funciona correctamente. 

```c
void setup() {
 pinMode(13, OUTPUT); // LED Rojo
 pinMode(12, OUTPUT); // LED Verde

}

void loop() {
  // LED Rojo
  digitalWrite(13, HIGH);
  delay(1500);
  digitalWrite(13, LOW);
  delay(1500);
  
  // LED Verde
  digitalWrite(12, HIGH);
  delay(1500);
  digitalWrite(12, LOW);
  delay(1500);
}
```

La resistencia tiene un valor de $1K$ Ohmios.

![img3](https://github.com/ruiz314/PDIH/blob/main/S-arduino/img/S_blink3.png)

Se enciende primero el LED rojo y se apaga a los 1500ms. A continuación se enciende el LED verde, y a los 1500 ms se apaga.

Fichero fuente: [ejercicio1.ino](https://github.com/ruiz314/PDIH/blob/main/S-arduino/ficheros/ejercicio1.ino)

[Enlace a proyecto en Tinkercad](https://www.tinkercad.com/things/hgxeAdCIdFW-blink3/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fcollections%2Ff93vEWIxIhX%2Fall&sharecode=SMlAqG8CpycQzrsdykNOQvvY96TQ8KJW3OgVsEJz77w)

## Ejercicio 2
Implementar en los simuladores el programa de parpadeo de LED, ampliándolo con las modificaciones necesarias para que se encienda el LED solo cuando se pulse un interruptor conectado a la entrada digital 7. 

 ```c
const int botonPin = 7;
const int ledPin = 13;
int estadoBoton =0;

void setup() {
 pinMode(ledPin, OUTPUT);
 pinMode(botonPin, INPUT);

}

void loop() {
  // Leer estado del botón
  estadoBoton = digitalRead(botonPin);
  
  // Comprobar si está pulsado
  if(estadoBoton == HIGH){ // Botón pulsado
  	// Encender luz
    digitalWrite(ledPin, HIGH);
  }else{
  	// Apagar luz
  	digitalWrite(ledPin, LOW);
  }
  delay(10);
}
```

Como materiales se han necesitado:
- Un LED
- La resistencia para el LED que tiene un valor de $220$ Ohmios.
- Un pulsador
- La resistencia para el pulsador que tiene un valor de $10K$ Ohmios.

![img4](https://github.com/ruiz314/PDIH/blob/main/S-arduino/img/S_blinkBotton.png)

Fichero fuente: [ejercicio2.ino](https://github.com/ruiz314/PDIH/blob/main/S-arduino/ficheros/ejercicio2.ino)

[Enlace a proyecto en Tinkercad](https://www.tinkercad.com/things/1IVDQKk12L9-bottontoblink/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fcircuits&sharecode=xKXGPKaCEOjsYK8XpiCgtLzw55L3yv9NjRQPejdMqr0)
