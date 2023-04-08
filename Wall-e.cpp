/*robô que desvia de obstáculos*/
//importa as bibliotecas 

#include <VarSpeedServo.h>

#include <NewPing.h>

//define o nome dos servos de movimento
VarSpeedServo head;
VarSpeedServo Larm;
VarSpeedServo Rarm;
//define os pinos pro sensor ultrassônico
#define TRIGGER  10 //azul
#define ECHO     11 //roxo
#define DISTMAX 200 //distância máxima
#define motorRF 8 //azul
#define motorRR 9 //verde
#define motorLF 12 //branco
#define motorLR 13 //roxo
//variavel de distância
int distancia = 40;
//variavel de tempo
int motorTime = 1000;
//variavel para o for de movimento 
int pos = 0;
//define o nome do sensor
NewPing sensor(TRIGGER, ECHO, DISTMAX);
void setup(){
  //define os pinos para os motores
  pinMode(motorRF, OUTPUT);
  pinMode(motorRR, OUTPUT);
  pinMode(motorLF, OUTPUT);
  pinMode(motorLR, OUTPUT);
  //define os pinos para os servos
  head.attach(3);
  Larm.attach(5);
  Rarm.attach(6);
  //abre o monitor serial em 115200
  Serial.begin(115200);
}
void loop(){
  //exibe a distância em cm no monitor serial
  delay(50);
  Serial.print("Ping: ");
  Serial.print(sensor.ping_cm());
  Serial.println("cm"); 
  //anda pra frente,dois braços balançando e olhar reto
  digitalWrite(motorRF,HIGH);
  digitalWrite(motorLF,HIGH);
  digitalWrite(motorRR,LOW);
  digitalWrite(motorLR,LOW);
  head.write(90);
  //trecho pra balançar os braços
  //vai de 0 até 80, em passos de 5
  for (pos = 0; pos <= 80; pos += 5 ) {
    //mexe de acordo com os passos
    Larm.write(pos);
    Rarm.write(pos);
    delay(15);                       
  }
  //vai de 120 até 0 em passos de -5
  for (pos = 120; pos >= 0; pos -= 5) { 
    Larm.write(pos); 
    Rarm.write(pos);
    delay(15);                       
  }
  //se a distância em frente for menor que 13cm
  if (sensor.ping_cm()<distancia and sensor.ping_cm()>0) {
    //para os motores
    digitalWrite(motorRF,LOW);
    digitalWrite(motorLF,LOW);
    digitalWrite(motorRR,LOW);
    digitalWrite(motorLR,LOW);
    delay(300);
    //olha pra esquerda
    head.write(180,50);
    delay(1000);
    //se a distância na esquerda for menor que 13cm
    if (sensor.ping_cm()<distancia and sensor.ping_cm()>0){
      //para
      digitalWrite(motorRF,LOW);
      digitalWrite(motorLF,LOW);
      digitalWrite(motorRR,LOW);
      digitalWrite(motorLR,LOW);
      //braços pra cima
      Larm.write(-70,100);
      Rarm.write(70,100);
      delay(300);
      //olha pra direita
      //vai de 180 até -180 em passos de -2
      for (pos = 180; pos >= -180; pos-= 2) { 
        delay(15);
        //mexe de acordo com os passos                       
        head.write(pos);
      }
      delay(motorTime);
      //se a distância na direita for menor que 13cm
      if (sensor.ping_cm()<distancia and sensor.ping_cm()>0){
      //braços pra cima
       Larm.write(-70,100);
       Rarm.write(70,100);
       delay(500);
       //dá meia volta 
       digitalWrite(motorRF,HIGH);
       digitalWrite(motorRR,LOW);
       digitalWrite(motorLR,HIGH);
       digitalWrite(motorLF,LOW); 
       delay(motorTime-200);
       //se a direita tiver livre
      } else if (sensor.ping_cm()>distancia and sensor.ping_cm()>0){
        //vira pra direita
        digitalWrite(motorRR,HIGH);
        digitalWrite(motorRF,LOW);
        digitalWrite(motorLF,HIGH);
        digitalWrite(motorLR,LOW);
        delay(motorTime-250);
      }
      //se a esquerda tiver livre
     }else if (sensor.ping_cm()>distancia and sensor.ping_cm()>0){
        //vira pra esquerda
        digitalWrite(motorRF,HIGH);
        digitalWrite(motorRR,LOW);
        digitalWrite(motorLR,HIGH);
        digitalWrite(motorLF,LOW);
        delay(motorTime-250);
    }
 } 
}