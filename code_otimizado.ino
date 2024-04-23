#define LEVEL_100      0
#define LEVEL_50       1
#define LEVEL_25       2

#define ON             HIGH
#define OFF            !ON
#define NIVEL_ATINGIDO 0
#define NIVEL_NAO_ATINGIDO !NIVEL_ATINGIDO
#define _NULL          -1

#define ATRASO         3000

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando");

  prepararSensores();
  prepararLeds();
  prepareAlarm(); 
}

void loop() {
  monitorarSensores();
  monitoringAlarm();
  atualizarLeds();
 
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

//Componente de Alarme

#define alarmMuteKey  10
#define alarm_output  9

boolean a = false;

void prepareAlarm(){
  pinMode(alarm_output, OUTPUT);
  pinMode(alarmMuteKey, INPUT_PULLUP);
}

void monitoringAlarm(){
  
  if(getStatusSensor(LEVEL_100) == NIVEL_ATINGIDO &&
     getStatusSensor(LEVEL_50) ==  NIVEL_ATINGIDO &&
     getStatusSensor(LEVEL_25) == NIVEL_ATINGIDO){
    alarmEmpty();
  }
  
  if(getStatusSensor(LEVEL_100) == NIVEL_NAO_ATINGIDO && 
          getStatusSensor(LEVEL_50) == NIVEL_NAO_ATINGIDO && 
          getStatusSensor(LEVEL_25) == NIVEL_NAO_ATINGIDO){
    alarmEmpty();
  }else {
  	a=false;	
  }

  // Verifica se o botão de desativação do alarme foi pressionado
  int buttonRead = digitalRead(alarmMuteKey);
  if(buttonRead == LOW){
    a = true; // Define a variável 'a' como 1, indicando que o alarme foi silenciado
  }
  Serial.print("estado do botao: ");
  Serial.println(a);
}


void alarmFull(){
  Serial.println("full");

  if(a == false){  
    unsigned int i, k;
    
  for(k = 0; k < 2; k++) {  
    for(i = 0; i < 200; i++){
      digitalWrite(alarm_output,HIGH);
      delayMicroseconds(250);
      digitalWrite(alarm_output,LOW);
      delayMicroseconds(250);
  }
    for(i = 0; i < 250; i++) {
        digitalWrite(alarm_output,HIGH);
        delayMicroseconds(200);
        digitalWrite(alarm_output,LOW);
        delayMicroseconds(200);
      }  
    }
  } 
}

void alarmEmpty(){
  Serial.println("empty");

  if(a == false){ 
    unsigned int i;
    for(i = 0; i < 400; i++){
      digitalWrite(alarm_output,HIGH);
      delayMicroseconds(200);
      digitalWrite(alarm_output,LOW);
      delayMicroseconds(200);
    } 
  }Serial.println("termino");
}
  
