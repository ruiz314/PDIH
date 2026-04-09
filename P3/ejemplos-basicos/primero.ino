void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, LOW);   // encender el LED (voltaje a HIGH)
  digitalWrite(12, HIGH);   // encender el LED (voltaje a HIGH)
  delay(500);              // esperar encendido durante 1 segundo (1000 milisegundos)
  digitalWrite(13, HIGH);    // apagar el LED (voltaje a LOW)
  digitalWrite(12, LOW);    // apagar el LED (voltaje a LOW)
  delay(1000);              // esperar apagado durante 100 milisegundos
}
