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
