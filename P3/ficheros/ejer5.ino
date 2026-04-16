const int luzPin = A0;  // Sensor de luz
const int ledPin = 9;   // LED

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(luzPin, INPUT); 
  
  // Inicializar el monitor serie
  Serial.begin(9600);
}

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
