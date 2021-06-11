/*
   Display number on seven segment display with Arduino
   Written by Ahmad Shamshiri for Robojax.com
  Date modified: Jun 11, 2018 at 17:20 at Ajax, Ontario, Canada
  watch video instruction for this code:https://youtu.be/-g6Q9lSHDzg

  Code is provided for free AS IS without warranty.
  You can share this acode as long as you keep the above note intact.
*/

#include "Ultrasonic.h" //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX

const int echoPin = 5; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 4; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)

Ultrasonic ultrasonic(trigPin, echoPin); //INICIALIZANDO OS PINOS DO ARDUINO

int distancia; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING

const int A1A = 6;//define pin 2 for A1A
const int A1B = 7;//define pin 3 for A1B

const int B1A = 9;//define pin 8 for B1A
const int B1B = 10;//define pin 9 for B1B

int Led1 = 11;
int Led2 = 12;

char opcao;

long randNum;

void setup() {
  pinMode(B1A, OUTPUT); // define pin as output
  pinMode(B1B, OUTPUT);

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  delay(3000);


  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)

  randomSeed(analogRead(0));
}

void loop() {

  if (mySerial.available() > 0) {
    opcao = mySerial.read();
    switch (opcao) {
      case 'S':
        Serial.println("parar");
        parar();
        break;
      case 'F':
        Serial.println("frente");
        frente();
        break; 
      case 'R':
        Serial.println("direita");
        direita();
        break;
      case 'L':
        Serial.println("esquerda");
        esquerda();
        break;
      case 'B':
        Serial.println("para traz");
        traz();
        break;
      case 'X':
        do {
          Serial.println("auto");
          hcsr04();
          if (distancia < 50) {
            Serial.println("obstaculo");
            parar();
            delay(500);
            traz();
            delay(500);
            randNum = random(2);
            if (randNum == 1)
              esquerda();
            else
              direita();
            delay(200);
          } else {
            Serial.println("frente");
            frente();
          }
          if (mySerial.available() > 0) {
            opcao = mySerial.read();
          }
        } while (opcao == 'X');
        break;
    }
  }
}



void traz() {
  digitalWrite(A1A, HIGH);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(B1B, HIGH);
}

void esquerda() {
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, HIGH);
  digitalWrite(B1A, LOW);
  digitalWrite(B1B, HIGH);
  digitalWrite(Led1, HIGH);
}

void direita() {
  digitalWrite(A1A, HIGH);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, HIGH);
  digitalWrite(B1B, LOW);
  digitalWrite(Led2, HIGH);
}

void frente() {
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, HIGH);
  digitalWrite(B1A, HIGH);
  digitalWrite(B1B, LOW);
  digitalWrite(Led1, HIGH);
  digitalWrite(Led2, HIGH);
}

void parar() {
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(B1B, LOW);
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
}






void hcsr04() {
  digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
  delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
  digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
  delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
  digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
  //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
  //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
  //NA VARIAVEL "distancia"
  distancia = (ultrasonic.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
  result = String(distancia); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS
}
