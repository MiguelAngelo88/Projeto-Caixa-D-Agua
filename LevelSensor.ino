/*
  componente dos sensores
*/

const byte PORT_LEVEL_SENSOR [] = {2,3,4,5};
#define SIZEOF_LEVEL_SENSOR sizeof(PORT_LEVEL_SENSOR)/sizeof(byte)
boolean STATUS_LEVEL_SENSOR [SIZEOF_LEVEL_SENSOR];

unsigned long currentTimeSensor [SIZEOF_LEVEL_SENSOR];
#define ATRASO 3000

//seta as portas dos sensores
void preparingLevelSensor(){
  for(byte x =0; x < SIZEOF_LEVEL_SENSOR;x++){
      pinMode(PORT_LEVEL_SENSOR[x], INPUT);
      currentTimeSensor[x] = 0;
  }
}

//retorna o status do sensor solicitado
int getLevelSensor(byte pos){
  if(TimeOver(currentTimeSensor[pos])){
      currentTimeSensor[pos] = 0;
      return STATUS_LEVEL_SENSOR[pos];
  }
  return _NULL;
}

//monitora o status dos sensores
void monitoringLevelSensor(){
  for(byte x = 0; x < SIZEOF_LEVEL_SENSOR; x++){
    if(digitalRead(PORT_LEVEL_SENSOR[x]) == NIVEL_ATINGIDO 
      && STATUS_LEVEL_SENSOR[x] == false){
        delay(50);
        if(digitalRead(PORT_LEVEL_SENSOR[x]) == NIVEL_ATINGIDO){
          STATUS_LEVEL_SENSOR[x] = true;
          currentTimeSensor[x] = millis() + ATRASO;
        }
    }else{
      if(digitalRead(PORT_LEVEL_SENSOR[x]) == NIVEL_NAO_ATINGIDO 
        && STATUS_LEVEL_SENSOR[x] == true){
          STATUS_LEVEL_SENSOR[x] = false;
          currentTimeSensor[x] = millis() + ATRASO;
      }
    }
  }
}
