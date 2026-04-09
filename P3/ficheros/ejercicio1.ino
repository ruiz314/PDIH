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
