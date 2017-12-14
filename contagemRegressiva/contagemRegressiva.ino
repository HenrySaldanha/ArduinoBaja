#include "TM1637.h"
#include "TimerOne.h"  

/* a,b,c,d,e,f,g*/
char display1[] = {47, 49 ,48, 50, 52, 53, 51};
char display2[] = {33, 35, 40, 44, 46, 31, 42};


int CLK = 9; //Set the CLK pin connection to the display
int DIO = 8; //Set the DIO pin connection to the display

int UP_H = 7;  // BOTAO INCREMENTAR HORA
int UP_M = 6;  // BOTAO INCREMENTAR MINUTO
int START = 5; // START

int temp = 0;

int numeroFinal = 0;  // tempo final
boolean start = false;
boolean pontos = false;
int reset = 0;

int verificacaoHora = 0;
int verificacaoMinuto = 0;
int verificacaoStart = 0;


int verificacaoVelocimetro = 0;
int velocidade =0;
int picos = 0;

int s =0;


TM1637Display display(CLK, DIO);  //configuracao do display

void setup()
{
  pinMode(UP_H, INPUT);
  pinMode(UP_M, INPUT);
  pinMode(START, INPUT);

  for (int i = 0; i < 7; i++) {
    pinMode(display2[i], OUTPUT);
    pinMode(display1[i], OUTPUT);
  }
  
  display.setBrightness(0x0b);  //brilho maximo

  Timer1.initialize(125000);  // a cada 125ms
  Timer1.attachInterrupt(tempoT);  

  Serial.begin(9600);

  displayDuplo(0);
}

void displayDuplo(int n) {
  char vetorDisplay1[7];
  char vetorDisplay2[7];

  // display 35 
  // valor do primeiro display = 35/10 = 3
  numeroDisplay(vetorDisplay1, (n/10));
  //valor do segundo display = 35 - (3*10) = 5
  numeroDisplay(vetorDisplay2, (n-((n/10)*10)));

  // 7 e a quantidade de leds que vao acender em cada display
  for (int i = 0; i < 7; i++) {
    // comando que envia 0 ou 1 para a porta digital
    digitalWrite(display1[i], vetorDisplay1[i]);
    digitalWrite(display2[i], vetorDisplay2[i]);
  }

  

}

void tempoT(){

  if(numeroFinal == 0) start = false;

  if(numeroFinal>0){

      // se ficar pressionado por 1 segund
      if(digitalRead(START) == HIGH)
        reset++;
      else 
        reset = 0;

      if(reset == 8){
          numeroFinal = 0;
          reset = 0;
          start = false;
      }
  

  
  if(start && numeroFinal>0){
      temp++;
      if(temp == 8*60){ // 125ms x 8 x 60 = 1s
        numeroFinal--;
        numeroFinal = justeHoras(numeroFinal,2);
        temp = 0;
      }
  }

  
  }

  pontos = !pontos;

  mostrarValorDisplay();

  velocimetro();
  
}

void velocimetro(){

  s++;
  if(s == 8){
    float freq = (picos/1); 
    //velocidade = (1.89*freq*3.6)/12.0;
    velocidade = (1.89*(freq/12.0)*3.6);
    Serial.println(picos);
    
    picos = 0;
    s = 0;
    if(velocidade <50.0)
      displayDuplo(((int)velocidade));
      
  }
  
}



void loop()
{
  if(!start)
    temporizador();
  
  for(int i=0;i<20;i++)
    lerVelocidade();
}

void lerVelocidade(){

  if(analogRead(0) <50 && verificacaoVelocimetro == 1 ){
  verificacaoVelocimetro = 0;
    
  }
  if(analogRead(0)> 400 && verificacaoVelocimetro == 0){
    picos++;
    verificacaoVelocimetro = 1;
  }

}



void temporizador(){

    // variaveis de controle
    if(digitalRead(UP_H) == 0 && verificacaoHora == 1){
      verificacaoHora = 0;
    }
    if(digitalRead(UP_M) == 0 && verificacaoMinuto == 1){
      verificacaoMinuto = 0;
    }
    if(digitalRead(START) == 0 && verificacaoStart == 1){
      verificacaoStart = 0;
    }



    // se o botao estiver solto, ele entrara nas funcoes abaixo
 
    if(digitalRead(START) == HIGH && verificacaoStart == 0){
      start = !start;
      verificacaoStart = 1;
    }

    // INCREMENTA VALOR DE TEMPO
    if(digitalRead(UP_H) == HIGH && verificacaoHora == 0){
      if(numeroFinal <9900){
          numeroFinal += 100;  
          numeroFinal = justeHoras(numeroFinal,1);
          verificacaoHora= 1;
      }
    }

    // DECREMENTAC VALOR DE TEMPO
    if(digitalRead(UP_M) == HIGH && verificacaoMinuto == 0){
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

 void numeroDisplay(char *vetor, int k) {
  /*
    Cada numero mostrado no display e um vetor de leds
    alguns ligados(1) outros apagados(0)
  */
  
  switch (k) {
    case 0:
      vetor[0] = 1;
      vetor[1] = 1;
      vetor[2] = 1;
      vetor[3] = 1;
      vetor[4] = 1;
      vetor[5] = 1;
      vetor[6] = 0;   
      break;

    case 1:
      vetor[0] = 0;
      vetor[1] = 1;
      vetor[2] = 1;
      vetor[3] = 0;
      vetor[4] = 0;
      vetor[5] = 0;
      vetor[6] = 0;
      break;

    case 2:
      vetor[0] = 1;
      vetor[1] = 1;
      vetor[2] = 0;
      vetor[3] = 1;
      vetor[4] = 1;
      vetor[5] = 0;
      vetor[6] = 1;
      break;

    case 3:
      vetor[0] = 1;
      vetor[1] = 1;
      vetor[2] = 1;
      vetor[3] = 1;
      vetor[4] = 0;
      vetor[5] = 0;
      vetor[6] = 1;
      break;

    case 4:
      vetor[0] = 0;
      vetor[1] = 1;
      vetor[2] = 1;
      vetor[3] = 0;
      vetor[4] = 0;
      vetor[5] = 1;
      vetor[6] = 1;
      break;

    case 5:
      vetor[0] = 1;
      vetor[1] = 0;
      vetor[2] = 1;
      vetor[3] = 1;
      vetor[4] = 0;
      vetor[5] = 1;
      vetor[6] = 1;
      break;

    case 6:
      vetor[0] = 1;
      vetor[1] = 0;
      vetor[2] = 1;
      vetor[3] = 1;
      vetor[4] = 1;
      vetor[5] = 1;
      vetor[6] = 1;
      break;

    case 7:
      vetor[0] = 1;
      vetor[1] = 1;
      vetor[2] = 1;
      vetor[3] = 0;
      vetor[4] = 0;
      vetor[5] = 0;
      vetor[6] = 0;
      break;

    case 8:
      vetor[0] = 1;
      vetor[1] = 1;
      vetor[2] = 1;
      vetor[3] = 1;
      vetor[4] = 1;
      vetor[5] = 1;
      vetor[6] = 1;
      break;

    case 9:
      vetor[0] = 1;
      vetor[1] = 1;
      vetor[2] = 1;
      vetor[3] = 0;
      vetor[4] = 0;
      vetor[5] = 1;
      vetor[6] = 1;
      break;
  }
}
