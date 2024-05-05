#define LEVEL_100      0
#define LEVEL_50       1
#define LEVEL_25       2

#define ON             HIGH
#define OFF            !ON
#define LEVEL_ACHIEVED  0
#define LEVEL_NOT_ACHIEVED !LEVEL_ACHIEVED
#define _NULL          -1

#define DELAY_TIME         3000

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando");

  prepareSensors();
  prepareLeds();
  prepareAlarm(); 
}

void loop() {
  monitoringSensors();
  monitoringAlarm();
  refreshLeds();
 
}
// Controle dos LEDs
const byte PORTA_LED[] = {6, 7, 8};
#define NUM_LEDS sizeof(PORTA_LED) / sizeof(byte)

void prepareLeds() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    pinMode(PORTA_LED[i], OUTPUT);
  }
}

void setLed(byte pos, boolean status) {
  digitalWrite(PORTA_LED[pos], status);
}

void refreshLeds() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    if (getStatusSensor(i) != _NULL) {
      setLed(i, getStatusSensor(i));
    }
  }
}

// Componente dos sensores
const byte LEVEL_SENSORS_PIN[] = {2, 3, 4};
#define NUM_SENSORS sizeof(LEVEL_SENSORS_PIN) / sizeof(byte)
boolean STATUS_LEVEL_SENSOR[NUM_SENSORS];
unsigned long sensorCurrentTime[NUM_SENSORS];

void prepareSensors() {
  for (byte i = 0; i < NUM_SENSORS; i++) {
    pinMode(LEVEL_SENSORS_PIN[i], INPUT_PULLUP);
    sensorCurrentTime[i] = 0;
  }
}

int getStatusSensor(byte pos) {
  if (ExpiredTime(sensorCurrentTime[pos])) {
    sensorCurrentTime[pos] = 0;
    return STATUS_LEVEL_SENSOR[pos];
  }
  return _NULL;
}

void monitoringSensors() {
  for (byte i = 0; i < NUM_SENSORS; i++) {
    byte SensorRead = digitalRead(LEVEL_SENSORS_PIN[i]);
    if ((SensorRead == LEVEL_ACHIEVED && !STATUS_LEVEL_SENSOR[i]) ||
        (SensorRead == LEVEL_NOT_ACHIEVED && STATUS_LEVEL_SENSOR[i])) {
      if (StabilizeSensor(LEVEL_SENSORS_PIN[i])) {
        STATUS_LEVEL_SENSOR[i] = !STATUS_LEVEL_SENSOR[i];
        sensorCurrentTime[i] = millis() + DELAY_TIME;
      }
    }
  }
}

// Espera o sensor se estabilizar antes de continuar
boolean StabilizeSensor(byte SensorPin) {
  byte CurrentRead = digitalRead(SensorPin);
  unsigned long StartTime = millis();
  while (digitalRead(SensorPin) != CurrentRead) {
    if (millis() - StartTime > 50) {
      return false; // Timeout
    }
  }
  return true;
}

// Componente de tempo
boolean ExpiredTime(unsigned long timeOut) {
  return millis() > timeOut;
}

//Componente de Alarme

#define MuteButton  10
#define alarmPin  9

boolean alarmSilenced = false;

void prepareAlarm(){
  pinMode(alarmPin, OUTPUT);
  pinMode(MuteButton, INPUT_PULLUP);
}

void monitoringAlarm(){
  int status_100 = getStatusSensor(LEVEL_100);
  int status_50 = getStatusSensor(LEVEL_50);
  int status_25 = getStatusSensor(LEVEL_25);

  if ((status_100 == LEVEL_ACHIEVED && status_50 == LEVEL_ACHIEVED && status_25 == LEVEL_ACHIEVED) ||
      (status_100 == LEVEL_NOT_ACHIEVED && status_50 == LEVEL_NOT_ACHIEVED && status_25 == LEVEL_NOT_ACHIEVED)) {
    playAlarm();
  } else {
    alarmSilenced = false;
  }

  if (alarmSilenced == false) {
    int ButtonState = digitalRead(MuteButton);
    if (ButtonState == LOW) {
      alarmSilenced = true;
    }
  }
}

void playAlarm() {
  if (alarmSilenced == false) {
     
    for (unsigned int i = 0; i < 400; i++) {
      digitalWrite(alarmPin, HIGH);
      delayMicroseconds(200);
      digitalWrite(alarmPin, LOW);
      delayMicroseconds(200);
    }
  }
}
