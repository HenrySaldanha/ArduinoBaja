#include <Wire.h>

// DECLARACAO DOS PINOS
char sensor_indutivo = 39;

/* a,b,c,d,e,f,g*/
char display1[] = {44, 46, 51, 49 , 53, 40, 42};
char display2[] = {50, 52 ,41, 45, 47, 48, 43};

//---------------------------
void setup() {
  /* declaracao dos pinos que serao usados, (entrada ou saida de dados)*/
  //monitor serial do PC
  Serial.begin(9600);
  // sensor indutivo
  pinMode(sensor_indutivo, INPUT);
  
  // display duplo, total 14 pinos  
  for (int i = 0; i < 7; i++) {
    pinMode(display2[i], OUTPUT);
    pinMode(display1[i], OUTPUT);
  }

  
  //for(int i=0;i<100;i++){
    //displayDuplo(i);
   // delay(80);
  //}
  displayDuplo(0);
}

void loop() { 
  velocimetro();  
}

void velocimetro(){
  // diferenca de tempo entre os furos em milisegundos
   unsigned long tempo = diferencaTempoSensorIndutivo();
   int vel = ((1/((tempo/1000.0)*1))*1.89)*3.6;
   if(vel <50){
     displayDuplo(vel);
  }
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


unsigned long diferencaTempoSensorIndutivo () {
  unsigned long tempoAnt, tempoAtual;
  /*
  pega a diferenca de tempo entre os furos
  */
  
  while (digitalRead(sensor_indutivo) == 0) {
  }
  // primeiro passagem pelo furo
  tempoAnt = millis();

  while (digitalRead(sensor_indutivo) == 1) {
  }

  while (digitalRead(sensor_indutivo) == 0) {
  }
  // segunda passagem pelo furo
  tempoAtual = millis();
  return (tempoAtual - tempoAnt);
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



