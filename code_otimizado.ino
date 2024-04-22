#define LEVEL_100      0
#define LEVEL_50       1
#define LEVEL_25       2

#define ON             HIGH
#define OFF            !ON
#define NIVEL_ATINGIDO 0
#define NIVEL_NAO_ATINGIDO !NIVEL_ATINGIDO
#define _NULL          -1

#define ATRASO         3000

#define PORTA_BUZZER   9

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando");

  prepararSensores();
  prepararLeds();
  prepararBuzzer(); 
}

void loop() {
  monitorarSensores();
  atualizarLeds();
  atualizaBuzzer();
}

// Controle dos LEDs
const byte PORTA_LED[] = {6, 7, 8};
#define NUM_LEDS sizeof(PORTA_LED) / sizeof(byte)

void prepararLeds() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    pinMode(PORTA_LED[i], OUTPUT);
  }
}

void setLed(byte pos, boolean status) {
  digitalWrite(PORTA_LED[pos], status);
}

void atualizarLeds() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    if (getStatusSensor(i) != _NULL) {
      setLed(i, getStatusSensor(i));
    }
  }
}

// Componente dos sensores
const byte PORTA_SENSOR_NIVEL[] = {2, 3, 4};
#define NUM_SENSORES sizeof(PORTA_SENSOR_NIVEL) / sizeof(byte)
boolean STATUS_SENSOR_NIVEL[NUM_SENSORES];
unsigned long tempoAtualSensor[NUM_SENSORES];

void prepararSensores() {
  for (byte i = 0; i < NUM_SENSORES; i++) {
    pinMode(PORTA_SENSOR_NIVEL[i], INPUT_PULLUP);
    tempoAtualSensor[i] = 0;
  }
}

int getStatusSensor(byte pos) {
  if (TempoExpirado(tempoAtualSensor[pos])) {
    tempoAtualSensor[pos] = 0;
    return STATUS_SENSOR_NIVEL[pos];
  }
  return _NULL;
}

void monitorarSensores() {
  for (byte i = 0; i < NUM_SENSORES; i++) {
    byte leituraSensor = digitalRead(PORTA_SENSOR_NIVEL[i]);
    if ((leituraSensor == NIVEL_ATINGIDO && !STATUS_SENSOR_NIVEL[i]) ||
        (leituraSensor == NIVEL_NAO_ATINGIDO && STATUS_SENSOR_NIVEL[i])) {
      if (esperarSensorEstabilizar(PORTA_SENSOR_NIVEL[i])) {
        STATUS_SENSOR_NIVEL[i] = !STATUS_SENSOR_NIVEL[i];
        tempoAtualSensor[i] = millis() + ATRASO;
      }
    }
  }
}

// Espera o sensor se estabilizar antes de continuar
boolean esperarSensorEstabilizar(byte portaSensor) {
  byte leituraAtual = digitalRead(portaSensor);
  unsigned long tempoInicioEspera = millis();
  while (digitalRead(portaSensor) != leituraAtual) {
    if (millis() - tempoInicioEspera > 50) {
      return false; // Timeout
    }
  }
  return true;
}

// Componente de Tempo
boolean TempoExpirado(unsigned long tempo) {
  return millis() > tempo;
}

void prepararBuzzer() {
  pinMode(PORTA_BUZZER, OUTPUT);
}

void atualizaBuzzer() {
  // Verifica se todos os sensores estão em NIVEL_NAO_ATINGIDO
  boolean todosNaoAtingidos = true;
  for (byte i = 0; i < NUM_SENSORES; i++) {
    if (getStatusSensor[i] != NIVEL_NAO_ATINGIDO) {
      todosNaoAtingidos = false;
      break;
    }
  }

  // Se todos estiverem em NIVEL_NAO_ATINGIDO, toca o buzzer
  if (todosNaoAtingidos) {
    tone(PORTA_BUZZER, 500, 1000); // Toca o buzzer por 1 segundo
    delay(1000); // Espera 1 segundo
    noTone(PORTA_BUZZER); // Desliga o buzzer
  }
}
