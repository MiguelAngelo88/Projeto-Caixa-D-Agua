

int alarmMuteKey = 2;
int com = 3;
int alarm_output = 13;

int sensorFlow = 8;

int sensor1 = 12;   // lev 25%
int sensor2 = 11;   // lev 50%
int sensor3 = 10;   // lev 75%
int sensor4 = 9;    // lev 100%(FULL)

unsigned char m,a = 0;

unsigned int level = 0;
unsigned int temp = 10;


void alarmFull()
{
  
if(digitalRead(alarmMuteKey) == LOW)
a = 1;

if(a == 0)
{  
unsigned int i, k;
  
for(k = 0; k < 2; k++)  
{  
for(i = 0; i < 200; i++)
{
digitalWrite(alarm_output,HIGH);
delayMicroseconds(250);
digitalWrite(alarm_output,LOW);
delayMicroseconds(250);
}

for(i = 0; i < 250; i++)
{
digitalWrite(alarm_output,HIGH);
delayMicroseconds(200);
digitalWrite(alarm_output,LOW);
delayMicroseconds(200);
}  
}
if(m == 0)
delay(300);
} 
}

void alarmEmpty()
{
  
if(digitalRead(alarmMuteKey) == LOW)
a = 1;

if(a == 0)
{ 
  
unsigned int i;

for(i = 0; i < 400; i++)
{
digitalWrite(alarm_output,HIGH);
delayMicroseconds(200);
digitalWrite(alarm_output,LOW);
delayMicroseconds(200);
} 
if(m == 0)
delay(300);
}
}



 void setup()
 {
 
  pinMode(SCL_PIN,OUTPUT);
  pinMode(SDA_PIN,OUTPUT);
  pinMode(RST_PIN,OUTPUT);
  pinMode(DC_PIN,OUTPUT);
  pinMode(sensor1,INPUT_PULLUP);   
  pinMode(sensor2,INPUT_PULLUP);   
  pinMode(sensor3,INPUT_PULLUP);   
  pinMode(sensor4,INPUT_PULLUP); 
  pinMode(sensorFlow,INPUT_PULLUP); 
  pinMode(alarmMuteKey,INPUT_PULLUP);      
  digitalWrite(SCL_PIN,HIGH);;;
  digitalWrite(RST_PIN,LOW);;;
  pinMode(alarm_output,OUTPUT); 
  digitalWrite(alarm_output,LOW);  
  pinMode(com,OUTPUT); 
  digitalWrite(com,LOW);  
        
  delay(100);
  digitalWrite(RST_PIN,HIGH);
  

    int k;
    for(k=0;k<26;k++)
    {
    write_cmd(pgm_read_byte(&init_display[k]));    
    } 
 }
 
 void loop()
{
digitalWrite(com,HIGH);    
delay(2);

if(digitalRead(sensor4) == LOW)
level = 4;
else if(digitalRead(sensor3) == LOW)
level = 3;
else if(digitalRead(sensor2) == LOW)
level = 2;
else if(digitalRead(sensor1) == LOW)
level = 1;
else
level = 0;

  if(digitalRead(sensorFlow) == LOW)
  m = 1;
  else
   if(m == 1)
   {
    m = 0; 
    digitalWrite(com,LOW);        
    displayLevel();   
   }    
  
  digitalWrite(com,LOW);   


  if(level != temp)
  {
    temp = level;

  displayLevel();
  }

  if(m == 1)
  {  
  if(level == 0)
  {
  dispFlow(5,3);
  delay(100);
  dispFlow(5,2);
  delay(100);
  dispFlow(5,1);
  delay(100);  
  }

  if(level == 1)
  {
  a=0;  
  dispFlow(4,3);
  delay(100);
  dispFlow(4,2);
  delay(100);
  dispFlow(4,1);
  delay(100); 
  
  }

  if(level == 2)
  {
  a=0;    
  dispFlow(3,3);
  delay(100);
  dispFlow(3,2);
  delay(100);
  dispFlow(3,1);
  delay(100); 
    
  }

   if(level == 3)
  {
  a=0;    
  dispFlow(2,3);
  delay(100);
  dispFlow(2,2);
  delay(100);
  dispFlow(2,1);
  delay(100); 
  }
  
  if(level == 4)
  {
  dispFlow(1,3);
  delay(100);
  dispFlow(1,2);
  delay(100);
  dispFlow(1,1);
  delay(100); 
  }
  }
  else
  delay(300);


    if(level == 0)
    alarmEmpty();

    if(level == 1)
    a=0;
    
    if(level == 2)
    a=0;

    if(level == 3)
    a=0;    
    
    if(level == 4)
    alarmFull();
    
}  