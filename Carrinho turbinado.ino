/*
      AUTOR:   CIEBP Araraquara - Espaço 6 Robótica e Modelagem
      SKETCH:  Arduino - Carrinho com sensor de obstáculo ultrassonico, buzzer e setas
   DADOS: 12/12/2022
*/
//Bibliotecas utilizadas
#include <EasyUltrasonic.h>  // controle de sensor ultrasonico
EasyUltrasonic ultrasonic;
// Definir pinos para componentes
#define MotorEsquerdoFrente 3  //esquerda frente
#define MotorEsquerdoTras 5    //esquerda tras
#define MotorDireitoTras 6     //direita tras
#define MotorDireitoFrente 9   //direita frente
//Definier pinos dos leds
#define SetaDireitaFrente 4   //direita frente
#define SetaDireitaTras 7     //direita tras
#define SetaEsquerdaFrente 8  // esquerda frente
#define SetaEsquerdaTras 10   // esquerda tras
// Definier pinos do buzzer - som
#define Buzina 11  //Pino do buzzer */
//Definier pinos Ultrassonicos
#define ECHO 12  // pino ultrassonico recebe o sinal
#define TRIG 13  // pino ultrassonico envia o sinal
// Variaveis
int velocidadeParametro = 83;  // velocidade parametro dos motores
float distanciaCM = 0;         // Distancia em centimetros
unsigned long tempoAtual = 0;  // Tempo atual da função millis()
// Inicialização do codigo
void setup() {
  // Pinos motores
  pinMode(MotorEsquerdoFrente, OUTPUT);
  pinMode(MotorEsquerdoTras, OUTPUT);
  pinMode(MotorDireitoTras, OUTPUT);
  pinMode(MotorDireitoFrente, OUTPUT);
  // Pinos setas
  pinMode(SetaDireitaFrente, OUTPUT);
  pinMode(SetaDireitaTras, OUTPUT);
  pinMode(SetaEsquerdaFrente, OUTPUT);
  pinMode(SetaEsquerdaTras, OUTPUT);
  // Pino Buzzer
  pinMode(Buzina, OUTPUT);
  // Pinos Sensor Ultrasonico
  ultrasonic.attach(TRIG, ECHO);
  //Monitor Serial
  Serial.begin(115200);
}
void loop() {
  // Tempo interno do arduino, inicio do loop
  tempoAtual = millis();
  //Calculo de distancia Ultrassonica
  distanciaCM = ultrasonic.getDistanceCM();

  // Frente (100);
  // Tras (100);

  Serial.println(distanciaCM);
  delay(50);
}
void Frente(int velocidade) {
  analogWrite(MotorEsquerdoFrente, velocidade);
  analogWrite(MotorDireitoFrente, velocidade);
}
void Tras(int velocidade) {
  analogWrite(MotorEsquerdoTras, velocidade);
  analogWrite(MotorDireitoTras, velocidade);
}
void Direta (int velocidadeMD, int velocidadeME) {
  analogWrite (MotorDireitoTras, velocidadeMD);
  analogWrite (MotorEsquerdoFrente, velocidadeME); 
}
void Esquerda (int velocidadeMD, int velocidadeME) {
  analogWrite (MotorDireitoFrente, velocidadeMD);
  analogWrite (MotorEsquerdoTras, velocidadeME); 
}

