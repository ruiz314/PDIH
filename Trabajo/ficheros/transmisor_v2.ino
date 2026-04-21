/*
Permite escribir una frase en nuestro ordenador y hacer
que la placa Arduino lo convierta en los puntos y rayas
apropiados del código Morse. Las señales se ven con el 
LED y se escuchan con el zumbador.
*/

// Constantes y vectores
int ledPin = 12; // Constante para el pin del LED
int buzzPin = 11; // Constante para el pin del zumbador
int espera = 200; // Duración de un punto

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
  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600); // Inicia la comunicación
}

void loop()
{
  char caracter;

  // Comprobación de datos a leer
  if(Serial.available()){ // Si hay algo que leer del USB
  	caracter = Serial.read(); // Leer una letra

    // Según el caracter
    if(caracter >= 'a' && caracter <= 'z'){
    	mostrarSecuencia(letras[caracter - 'a']); // Minúscula
    }
    else if(caracter >= 'A' && caracter <= 'Z'){
    	mostrarSecuencia(letras[caracter - 'A']); // Mayúscula
    }
    else if(caracter >= '0' && caracter <= '9'){
    	mostrarSecuencia(numeros[caracter - '0']); // Número
    }
    else if(caracter == ' '){
    	delay(espera *4); // Espacio entre palabras
    }
  }
}

// Función auxiliar para emitir simboloes de un caracter
void mostrarSecuencia(char* secuencia)
{
  int i=0;

  // Recorre la cadena hasta encontrar el carácter nulo de fin de cadena (NULL)
  while(secuencia[i] != NULL)
  {
    encenderLED(secuencia[i]); // Emite punto o raya
    i++;
  }
  delay(espera *3); // Espacio entre letras
}

// Función auxiliar para encender el LED y buzzer
void encenderSignal(char puntoOBarra)
{
  digitalWrite(ledPin, HIGH); // Encender LED
  tone(buzzPin, 1000); // Activar zumbador
  
  if(puntoOBarra == '.')
  {
    delay(espera); // Pausa de un punto (1 unidad de tiempo)
  }
  else // es -
  {
    delay(espera *3); // Pausa de un guion (3 unidades de tiempo)
  }
  
  digitalWrite(ledPin, LOW); // Apagar LED
  noTone(buzzPin); // Desactivar zumbador
  
  delay(espera); // espacio entre destellos
}
