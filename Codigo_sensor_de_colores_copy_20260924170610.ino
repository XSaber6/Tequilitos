// ===================================================
// CONFIGURACIÓN DE PINES
// ===================================================

// Sensor de Color TCS3200
const int S0 = 2;
const int S1 = 3;
const int S2 = 5;
const int S3 = 6;
const int sensorOut = 4; // Pin OUT del sensor

// LEDs
const int ledAmarillo = 11;
const int ledRojo = 10;
const int ledVerde = 9;
const int ledAzul = 8;

// Variables para lecturas de frecuencia
int redFreq = 0;
int greenFreq = 0;
int blueFreq = 0;

// ===================================================
// SETUP (Configuración inicial)
// ===================================================
void setup() {
  // Configuración de pines del sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Configuración de pines para los LEDs
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);

  // Escala de frecuencia del sensor al 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Inicialización de la comunicación serie
  Serial.begin(9600);
}

// ===================================================
// LOOP (Bucle principal)
// ===================================================
void loop() {
  // Apaga todos los LEDs antes de cada nueva lectura
  apagarTodosLosLEDs();

  // 1. Lectura del componente ROJO
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFreq = pulseIn(sensorOut, LOW);
  delay(200);

  // 2. Lectura del componente VERDE
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFreq = pulseIn(sensorOut, LOW);
  delay(200);

  // 3. Lectura del componente AZUL
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFreq = pulseIn(sensorOut, LOW);
  delay(200);

  // Impresión en el Monitor Serie para seguimiento
  Serial.print("R: ");
  Serial.print(redFreq);
  Serial.print(" | G: ");
  Serial.print(greenFreq);
  Serial.print(" | B: ");
  Serial.println(blueFreq);

  // Lógica calibrada con tus lecturas reales
  int difVerdeRojo = greenFreq - redFreq;

  if (redFreq > 300 && greenFreq > 300) {
    // AZUL: R y G son muy altos (superan 300)
    digitalWrite(ledAzul, HIGH);
  } 
  else if (redFreq < 130) {
    // AMARILLO: R tiene el valor más bajo (menor a 130)
    digitalWrite(ledAmarillo, HIGH);
  } 
  else if (difVerdeRojo > 80) {
    // ROJO: La diferencia entre G y R es grande (mayor a 80)
    digitalWrite(ledRojo, HIGH);
  } 
  else if (redFreq >= 130 && redFreq <= 210) {
    // VERDE: R está entre 130 y 210 con diferencia pequeña respecto a G
    digitalWrite(ledVerde, HIGH);
  }

  delay(300); // Pausa de 300 ms entre lecturas
}

// ===================================================
// FUNCIÓN AUXILIAR
// ===================================================
void apagarTodosLosLEDs() {
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAzul, LOW);
}

