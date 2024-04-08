#define LEVEL_100          0
#define LEVEL_50           1
#define LEVEL_25           2
#define LEVEL_EMERGENCE    3

#define ON  HIGH
#define OFF !ON
#define NIVEL_ATINGIDO 1
#define NIVEL_NAO_ATINGIDO !NIVEL_ATINGIDO
#define _NULL -1

void setup() {
  Serial.begin(9600);
  Serial.println("iniciando");

  preparingEngine();
  preparingLevelSensor();
  preparingLed();
}

void loop() {
  monitoringLevelSensor();
  monitoringEngine();
  monitoringLed();
}
