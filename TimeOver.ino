/*
  componente Tempo
*/

boolean TimeOver(unsigned long time){
  return (millis() > time)? true : false;
}
