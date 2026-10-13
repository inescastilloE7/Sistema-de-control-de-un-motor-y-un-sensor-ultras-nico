// ===== SENSOR ULTRASONICO Y BUZZER =====
const int trigPin = 11;
const int echoPin = 4;
const int buzzerPin = 13; // (Usa un buzzer pasivo para que pueda variar el tono)

// ===== DRIVER LADO IZQUIERDO =====
const int IN1 = 6;
const int IN2 = 7;
const int ENA = 9;

// ===== DRIVER LADO DERECHO =====
const int IN3 = 8;
const int IN4 = 12;
const int ENB = 10;

// Velocidad de los motores
const int velocidad = 200;

void setup() {
  // Sensor y Buzzer
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  detener();
  delay(1000); 
}

void loop() {
  // 1. Medir la distancia actual del sensor
  long distancia = medirDistancia();

  // 2. Todos los motores irán hacia atrás todo el tiempo
  atras();

  // 3. Evaluar la proximidad del objeto mientras retrocede
  if (distancia > 0 && distancia <= 90) {
    // Si hay un objeto a 90 cm o menos, el buzzer suena con intensidad variable
    int frecuencia = map(distancia, 1, 90, 2000, 400);
    tone(buzzerPin, frecuencia);
  } 
  else {
    // Si está a más de 90 cm o no hay obstáculos cercanos, el buzzer se apaga
    noTone(buzzerPin);
  }
}

long medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000); // Timeout de 30ms
  long distanciaCm = duracion * 0.034 / 2;
  return distanciaCm;
}

void atras() {
  // Lado izquierdo
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Lado derecho (invertido respecto al izquierdo para empujar hacia el mismo lado)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
}

void detener() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}