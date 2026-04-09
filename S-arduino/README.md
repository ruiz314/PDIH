# Seminario. Introducción al uso de Arduino 
## Ejemplo Blink
En el ejemplo de Tinkercad viene por defecto el programa que nos da el profesor, pero en vez de indicar el número del pin se usa la constante `LED_BUILTIN`.
![img](https://github.com/ruiz314/PDIH/blob/main/S-arduino/img/S_blink1.png)

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
![img](https://github.com/ruiz314/PDIH/blob/main/S-arduino/img/S_blink2.png)

## Ejercicio 1
Implementar el programa de parpadeo de LED, ampliándolo para que encienda y apague alternativamente dos LED (uno rojo y otro verde), conectados a las salidas digitales 12 y 13 del Arduino, a un intervalo de 1.5 segundos. Crear el esquema con Fritzing y cargar el programa en Arduino para comprobar que funciona correctamente. 

## Ejercicio 2
Implementar en los simuladores el programa de parpadeo de LED, ampliándolo con las modificaciones necesarias para que se encienda el LED solo cuando se pulse un interruptor conectado a la entrada digital 7. 
