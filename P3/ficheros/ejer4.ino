const int echoPin = 12;
const int trigPin = 11;
const int buzzPin = 10;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600); // Para monitor serie
}

void loop()
{
  long duracion;
  int distancia;
  
  // Disparo ultrasónico
  digitalWrite(trigPin, LOW);
  delay(2); // Wait for 2 milliseconds
  digitalWrite(trigPin, HIGH);
  delay(2); // Wait for 2 milliseconds
  digitalWrite(trigPin, LOW);
  
  // Leer duración
  duracion = pulseIn(echoPin, HIGH);
  
  //Calcular distancia
  distancia = duracion * 0.034 / 2;
  
  Serial.print("Distancia: ");
  Serial.println(distancia);
  
  //Control de buzzer según la distancia
  if (distancia <= 60){
  	tone(buzzPin, 1400, 600);
  }else if(distancia >60 && distancia <= 150){
  	tone(buzzPin, 900, 400);
  }else{ // Silencio si no hay objeto cerca
  	noTone(buzzPin);
  }
  delay(100);
}
