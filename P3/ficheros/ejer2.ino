const int ledPinR = 11; // LED Rojo
const int ledPinA = 12; // LED Amarillo
const int ledPinV = 13; // LED Verde
const int botonPin = 7; // Pulsador
int estadoBoton =0;

void setup() {
 pinMode(ledPinR, OUTPUT);  
 pinMode(ledPinA, OUTPUT); 
 pinMode(ledPinV, OUTPUT);  
 pinMode(botonPin, INPUT);
}

void loop() {
  // Leer estado del botón
  estadoBoton = digitalRead(botonPin);
  
  // Comprobar si está pulsado
  if(estadoBoton == HIGH){ // Botón pulsado
  	// Encender Rojo, resto apagado
  	digitalWrite(ledPinR, HIGH); // LED Rojo
  	digitalWrite(ledPinA, LOW); // LED Amarillo
  	digitalWrite(ledPinV, LOW); // LED Verde
  	delay(1500);
  }else{
  	// Encender Amarillo, resto apagado
  	digitalWrite(ledPinA, HIGH); // LED Amarillo
  	digitalWrite(ledPinR, LOW); 
    digitalWrite(ledPinV, LOW); 
  	delay(1500);
  
  	// Encender Verde, resto apagado
  	digitalWrite(ledPinV, HIGH); // LED Verde
  	digitalWrite(ledPinR, LOW); 
    digitalWrite(ledPinA, LOW); 
  	delay(1500);
  }
}
