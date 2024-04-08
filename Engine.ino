/*
  componente motor
*/

#define PORT_ENGINE 10

void preparingEngine(){
  pinMode(PORT_ENGINE, OUTPUT);
}

//liga ou desliga o motor
void setStartEngine(boolean status){
  digitalWrite(PORT_ENGINE, status);
}

void monitoringEngine(){

  if(getLevelSensor(LEVEL_EMERGENCE) == NIVEL_NAO_ATINGIDO){
    setStartEngine(OFF);
    Serial.println("Sem Agua");
  }else{
        if(getLevelSensor(LEVEL_100) == NIVEL_ATINGIDO
          && getLevelSensor(LEVEL_50) ==  NIVEL_ATINGIDO
            && getLevelSensor(LEVEL_25) == NIVEL_ATINGIDO){
              setStartEngine(OFF);
              Serial.println("Motor Desligado");

        }else if(getLevelSensor(LEVEL_100) == NIVEL_NAO_ATINGIDO 
            && getLevelSensor(LEVEL_50) == NIVEL_NAO_ATINGIDO 
              && getLevelSensor(LEVEL_25) == NIVEL_NAO_ATINGIDO
                && getLevelSensor(LEVEL_EMERGENCE) == NIVEL_ATINGIDO){
                  setStartEngine(ON);
                  Serial.println("Motor Ligado");
          }  
    }
}
