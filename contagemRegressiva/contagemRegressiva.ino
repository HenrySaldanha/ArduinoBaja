#include "TM1637.h"
#include "TimerOne.h"  

int CLK = 9; //Set the CLK pin connection to the display
int DIO = 8; //Set the DIO pin connection to the display

int UP_H = 5;  // BOTAO INCREMENTAR HORA
int UP_M = 6;  // BOTAO INCREMENTAR MINUTO
int START = 7; // START

int temp = 0;

int numeroFinal = 0;  // tempo final
boolean start = false;
boolean pontos = false;
int reset = 0;

int verificacaoHora = 0;
int verificacaoMinuto = 0;
int verificacaoStart = 0;


TM1637Display display(CLK, DIO);  //configuracao do display

void setup()
{
  pinMode(UP_H, INPUT);
  pinMode(UP_M, INPUT);
  pinMode(START, INPUT);
  
  display.setBrightness(0x0b);  //brilho maximo

  Timer1.initialize(125000);  // a cada 125ms
  Timer1.attachInterrupt(tempoT);  

  Serial.begin(9600);

}

void tempoT(){
  
  if(start && numeroFinal>0){
      temp++;
      if(temp == 8*60){ // 125ms x 8 x 60 = 1s
        numeroFinal--;
        numeroFinal = justeHoras(numeroFinal,2);
        temp = 0;
        
        if(reset == 8) numeroFinal = 0;
      }
  }

  if(numeroFinal>0){
      if(digitalRead(START) == 1)
        reset++;
      else 
        reset = 0;

      if(reset == 8){
          numeroFinal = 0;
          reset = 0;
          start = false;
      }
  }

  pontos = !pontos;

  mostrarValorDisplay();
}
void loop()
{
  temporizador();
}

void temporizador(){
    
    if(digitalRead(UP_H) == 0 && verificacaoHora==1){
      verificacaoHora = 0;
    }
    if(digitalRead(UP_M) == 0 && verificacaoMinuto ==1){
      verificacaoMinuto = 0;
    }
    if(digitalRead(START) == 0 && verificacaoStart ==1){
      verificacaoMinuto = 0;
    }
  
    if(digitalRead(START) == 1 && verificacaoStart==0){
      start = !start;
      verificacaoStart = 1;
    }

    // INCREMENTA VALOR DE TEMPO
    if(digitalRead(UP_H) == 1 && verificacaoHora == 0){
      if(numeroFinal <9900){
          numeroFinal += 100;  
          numeroFinal = justeHoras(numeroFinal,1);
          verificacaoHora= 1;
      }
    }

    // DECREMENTAC VALOR DE TEMPO
    if(digitalRead(UP_M) == 1 && verificacaoMinuto == 0){
      if(numeroFinal <9999){
          numeroFinal++;  
          numeroFinal = justeHoras(numeroFinal,1);
          verificacaoMinuto = 1;
      }
    }


}

void mostrarValorDisplay(){

    if(pontos){
        display.showNumberDec(numeroFinal,true); //Display the Variable value;
    }else if(!pontos && start){
        uint8_t  segto = 0x80 | display.encodeDigit ((numeroFinal/ 100) % 10);
        display.setSegments (&segto, 1, 1);
    }
  
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
          else if(minutos == 1160)return 1200;
          else if(minutos == 1260)return 1300;
          else if(minutos == 1360)return 1400;
          else if(minutos == 1460)return 1500;
          else if(minutos == 1560)return 1600;
          else if(minutos == 1660)return 1700;
          else if(minutos == 1760)return 1800;
          else if(minutos == 1860)return 1900;
          else if(minutos == 1960)return 2000;
          
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
          else if(minutos == 1160)return 1200;
          else if(minutos == 1260)return 1300;
          else if(minutos == 1360)return 1400;
          else if(minutos == 1460)return 1500;
          else if(minutos == 1560)return 1600;
          else if(minutos == 1660)return 1700;
          else if(minutos == 1760)return 1800;
          else if(minutos == 1860)return 1900;
          else if(minutos == 1960)return 2000;
          
      }
      return minutos;
 }
