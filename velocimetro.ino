 #include "TimerOne.h"  
 
char sensor_indutivo = 7;
unsigned int picos = 0;

void setup() {
   Serial.begin(9600);
   pinMode(sensor_indutivo, INPUT);
   
  Timer1.initialize(500000);  // a cada 0.5 segundos
  Timer1.attachInterrupt(velocimetro);  
}

void velocimetro(){

  unsigned int tempo = 0.5;
  unsigned int numeroCiclos = picos;
  picos = 0;

  unsigned int frequencia = numeroCiclos/tempo;

  
   
  Serial.println(picos);
  
}

void loop() { 
  if(analogRead(sensor_indutivo) != 0) picos++;
}

