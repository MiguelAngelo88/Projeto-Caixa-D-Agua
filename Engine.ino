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

  if(!getLevelSensor(LEVEL_EMERGENCE)){
    setStartEngine(OFF);
    Serial.println("Sem Agua");
  }else{
        if(getLevelSensor(LEVEL_100) 
          && getLevelSensor(LEVEL_50) 
            && getLevelSensor(LEVEL_25)){
            setStartEngine(OFF);
            Serial.println("Motor Desligado");
        }else{
          if(!getLevelSensor(LEVEL_100) 
            && !getLevelSensor(LEVEL_50) 
              && !getLevelSensor(LEVEL_25)){
            setStartEngine(ON);
            Serial.println("Motor Ligado");
          }
        }
    }
}