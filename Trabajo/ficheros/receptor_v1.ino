const int espera = 200; // La misma unidad que en el transmisor (duración de un punto)
const int botonPin = 7;
int estadoBoton=0;
unsigned long tiempoInicio;
unsigned long duracionPulsacion;
String secuenciaMorse = "";

// Array con las letras del alfabeto Morse (De la 'A' a la 'Z')
char* letras[] = {
  ".-",   "-...", "-.-.", "-..",  ".",   // A, B, C, D, E
  "..-.", "--.",  "....", "..",   ".---",// F, G, H, I, J
  "-.-",  ".-..", "--",   "-.",   "---", // K, L, M, N, O
  ".--.", "--.-", ".-.",  "...",  "-",   // P, Q, R, S, T
  "..-",  "...-", ".--",  "-..-", "-.--",// U, V, W, X, Y
  "--.."  // Z
};

// Array con los números del alfabeto Morse (Del '0' al '9')
char* numeros[] = {
  "-----", ".----",  // 0, 1
  "..---", "...--",  // 2, 3
  "....-", ".....",  // 4, 5
  "-....", "--...",  // 6, 7
  "---..", "----."   // 8, 9
};

void setup()
{
  pinMode(botonPin, INPUT); // Configuración como entrada
  Serial.begin(9600);
  Serial.println("Receptor Morse Listo...");
}

void loop()
{
  // Leer estado del botón
  estadoBoton = digitalRead(botonPin);
  
  // Comprobar si está pulsado
  if(estadoBoton == HIGH){ // Botón pulsado
  	tiempoInicio = millis();
    
    // Mientras esté pulsado no se hace nada
    while(digitalRead(botonPin) == HIGH);
    
    // Al soltarlo se calcula el tiempmo transcurrido
    duracionPulsacion = millis() - tiempoInicio;
    
    // Determinar si es punto o raya
    if(duracionPulsacion > 50){
      if(duracionPulsacion < (espera * 1.5)){
      	secuenciaMorse += ".";
		Serial.print(".");
      }else{
      	secuenciaMorse += "-";
		Serial.print("-");
      }
    }
    delay(50);
  }
  
  // Comprobar si ha pasado tiempo para ser fin de letra
  // Leer estado del botón
  estadoBoton = digitalRead(botonPin);
  if(secuenciaMorse.length() > 0 &&(millis() - tiempoInicio > espera *3)){
    traducirMorse();
  }
} // Fin loop

// Función auxiliar para comparar la secuenciaMorse con la tabla de equivalencias y traducir
void traducirMorse(){
  bool encontrado = false;
  
  //Serial.print("\n Traduciendo ...");
  
  // Buscar en el array de letras
  for (int i = 0; i< 26; i++){
    if (secuenciaMorse == letras[i]) {
      // Calcula el carácter basándose en el índice
      char letraTraducida = 'A' + i;
      Serial.print(letraTraducida);
      encontrado = true;
      break;
  	}
  }
  
  // Buscar en el array de números (0-9)
  if (!encontrado) {
    for (int i = 0; i < 10; i++) {
      if (secuenciaMorse == numeros[i]) {
        char numeroTraducido = '0' + i; // Calcula el número basándose en el índice 
        Serial.print(numeroTraducido);
        encontrado = true;
        break;
      }
    }
  }
  
  // Si la secuencia no existe en el alfabeto Morse
  if(!encontrado){
  	Serial.print("Error");
  }
  // Limpiar para la siguiente letra
  secuenciaMorse = "";
  Serial.print("\n");
} 
