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
