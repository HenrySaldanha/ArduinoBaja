#include "TM1637.h"
#include "TimerOne.h"  

#define CLK 9 //Set the CLK pin connection to the display
#define DIO 8 //Set the DIO pin connection to the display

#define UP 10  // BOTAO INCREMENTAR
#define DOWN 11  // BOTAO DECREMENTAR
#define START 12 // START

int numeroFinal = 0;  // tempo final
boolean start = false;

TM1637Display display(CLK, DIO);  //configuracao do display

void setup()
{
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(START, INPUT);
  
  display.setBrightness(0x0b);  //brilho maximo

    Timer1.initialize(1 * 1000000);  // a cada 1 segundos
    Timer1.attachInterrupt(tempoT);  
}

void tempoT(){
  if(start && numeroFinal>0){
      numeroFinal--;
      numeroFinal = justeHoras(numeroFinal,2);
  }
}


void loop()
{
  temporizador();
}

void temporizador(){
    if(digitalRead(START) == 1){
      start = !start;
      while(digitalRead(START) == 1);
    }

    // INCREMENTA VALOR DE TEMPO
    if(digitalRead(UP) == 1){
      if(numeroFinal <9999){
          numeroFinal++;  
          numeroFinal = justeHoras(numeroFinal,1);
          while(digitalRead(UP) == 1);
      }
    }

    // DECREMENTAC VALOR DE TEMPO
    if(digitalRead(DOWN) == 1){
      if(numeroFinal >0){
          numeroFinal--;  
          numeroFinal = justeHoras(numeroFinal,2);
          while(digitalRead(DOWN) == 1);
      }
    }
    display.showNumberDec(numeroFinal); //Display the Variable value;
}

 int justeHoras(int minutos,int upDown){
      if(upDown == 1){
          if(minutos == 60)return 100;
          else if(minutos == 160)return 200;
          else if(minutos == 260)return 300;
          else if(minutos == 360)return 400;
          else if(minutos == 460)return 500;
          else if(minutos == 560)return 600;
          else if(minutos == 660)return 700;
          else if(minutos == 760)return 800;
          else if(minutos == 860)return 900;
          else if(minutos == 960)return 1000;
          else if(minutos == 1060)return 1100;
      }
      if(upDown == 2){
          if(minutos == 99)return 59;
          else if(minutos == 199)return 159;
          else if(minutos == 299)return 259;
          else if(minutos == 399)return 359;
          else if(minutos == 499)return 500;
          else if(minutos == 599)return 600;
          else if(minutos == 660)return 700;
          else if(minutos == 760)return 800;
          else if(minutos == 860)return 900;
          else if(minutos == 960)return 1000;
          else if(minutos == 1060)return 1100;
      }
      return minutos;
 }





