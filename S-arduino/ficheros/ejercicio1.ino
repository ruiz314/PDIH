// Ejercicio 1. 
// Implementar el programa de parpadeo de LED, ampliándolo para que encienda y apague alternativamente dos LED (uno rojo y otro verde), conectados a las salidas digitales 12 y 13 del Arduino, a un intervalo de 1.5 segundos. Crear el esquema con Fritzing y cargar el programa en Arduino para comprobar que funciona correctamente.

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
