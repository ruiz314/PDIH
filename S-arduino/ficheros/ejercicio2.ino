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
}
