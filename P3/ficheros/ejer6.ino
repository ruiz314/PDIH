// Librería para trabajar con servomotores
#include <Servo.h> 

// Declaración de pines
const int servoPin = 9; // Señal del servomotor
const int botonPin = 7; // Pulsador

int estadoBoton =0;
Servo miServo;

void setup()
{
  pinMode(botonPin, INPUT); //  Pin del botón como entrada
  miServo.attach(servoPin); // Vincular servo al pin físico
  miServo.write(0); //Posición a 0 grados
}

void loop()
{
  // Leer estado del botón
  estadoBoton = digitalRead(botonPin);
  
  // Control del motor
  if(estadoBoton == HIGH){ //Si el botón está pulsado
    miServo.write(180); // Girar el motor 90 grados
  }else{ // Si el botón no está pulsado
  	miServo.write(0); // No girar
  }
  
  // Pausa
  delay(15);
}
