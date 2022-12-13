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
#define SetaEsquerdaTras 2    // esquerda tras
// Definier pinos do buzzer - som
#define Buzina 10  //Pino do buzzer */
//Definier pinos Ultrassonicos
#define ECHO 12  // pino ultrassonico recebe o sinal
#define TRIG 13  // pino ultrassonico envia o sinal
// Variaveis
int velocidadeParametro = 83;  // velocidade parametro dos motores
float distanciaCM = 0;
int var1 = 1;
int var2 = 1;
// Distancia em centimetros
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
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}
void loop() {
  //Calculo de distancia Ultrassonica
  distanciaCM = ultrasonic.getDistanceCM();
  Serial.println(distanciaCM);
  
  int direcao = random(3);

  if (distanciaCM > 200 && distanciaCM < 300 && var1 == 1) {
    var1 == 2;
    Tras(0);
    //Buzzina(millis(), 2200, 400, 1200);
    Frente(220, 220);

  } else if (distanciaCM > 200 && distanciaCM < 300 && var1 == 2) {
    var1 == 1;
    Tras(0);
    Frente(150, 150);
    //Buzzina(millis(), 2200, 400, 1200);


  } else if (distanciaCM > 150 && distanciaCM <= 200 && var2 == 1) {
    var2 == 2;
    Tras(0);
    Frente(100, 125);
    //Buzzina(millis(), 2200, 400, 1200);

  } else if (distanciaCM > 150 && distanciaCM <= 200 && var2 == 2) {
    var2 == 1;
    Tras(0);
    Frente(80, 80);

  } else if (distanciaCM > 100 && distanciaCM <= 150) {
    Tras(0);
    Frente(70, 70);

  } else if (distanciaCM < 100) {
    Frente(0, 0);
    Tras(255);

  } else {
    Tras(0);
    Frente(255, 255);

  }
  delay(300);
}
void Frente(int velocidadeMotorDireito, int velocidadeMotorEsquerdo) {
  analogWrite(MotorEsquerdoFrente, velocidadeMotorEsquerdo);
  analogWrite(MotorDireitoFrente, velocidadeMotorDireito);
}
void Tras(int velocidade) {
  analogWrite(MotorEsquerdoTras, velocidade);
  analogWrite(MotorDireitoTras, velocidade);
}
void Direta(int velocidadeMD, int velocidadeME) {
  analogWrite(MotorDireitoTras, velocidadeMD);
  analogWrite(MotorEsquerdoFrente, velocidadeME);
}
void Esquerda(int velocidadeMD, int velocidadeME) {
  analogWrite(MotorDireitoFrente, velocidadeMD);
  analogWrite(MotorEsquerdoTras, velocidadeME);
}
void SetaAlerta(unsigned long tempoInicialSeta, int tempoSeta, int velocidadeSeta) {
  do {
    unsigned long S = ((millis() / velocidadeSeta) % 2 == 0);
    if (S) {
      digitalWrite(SetaEsquerdaFrente, HIGH);
      digitalWrite(SetaDireitaTras, HIGH);
      digitalWrite(SetaEsquerdaTras, HIGH);
      digitalWrite(SetaDireitaFrente, HIGH);
    } else {
      digitalWrite(SetaEsquerdaFrente, LOW);
      digitalWrite(SetaEsquerdaTras, LOW);
      digitalWrite(SetaDireitaTras, LOW);
      digitalWrite(SetaDireitaFrente, LOW);
    }
    digitalWrite(SetaEsquerdaFrente, LOW);
    digitalWrite(SetaEsquerdaTras, LOW);
    digitalWrite(SetaDireitaTras, LOW);
    digitalWrite(SetaDireitaFrente, LOW);
  } while ((millis() - tempoInicialSeta) < tempoSeta);
}
void SetaRe(unsigned long tempoInicialSeta, int tempoSeta, int velocidadeSeta) {
  do {
    unsigned long S = ((millis() / velocidadeSeta) % 2 == 0);
    if (S) {
      digitalWrite(SetaDireitaTras, HIGH);
      digitalWrite(SetaEsquerdaTras, HIGH);
    } else {
      digitalWrite(SetaEsquerdaTras, LOW);
      digitalWrite(SetaDireitaTras, LOW);
    }
    digitalWrite(SetaEsquerdaFrente, LOW);
    digitalWrite(SetaEsquerdaTras, LOW);
    digitalWrite(SetaDireitaTras, LOW);
    digitalWrite(SetaDireitaFrente, LOW);
  } while ((millis() - tempoInicialSeta) < tempoSeta);
}
void SetaDireita(unsigned long tempoInicialSeta, int tempoSeta, int velocidadeSeta) {
  do {
    unsigned long S = ((millis() / velocidadeSeta) % 2 == 0);
    if (S) {
      digitalWrite(SetaDireitaTras, HIGH);
      digitalWrite(SetaDireitaFrente, HIGH);
    } else {
      digitalWrite(SetaDireitaTras, LOW);
      digitalWrite(SetaDireitaFrente, LOW);
    }
    digitalWrite(SetaEsquerdaFrente, LOW);
    digitalWrite(SetaEsquerdaTras, LOW);
    digitalWrite(SetaDireitaTras, LOW);
    digitalWrite(SetaDireitaFrente, LOW);
  } while ((millis() - tempoInicialSeta) < tempoSeta);
}
void SetaEsquerda(unsigned long tempoInicialSeta, int tempoSeta, int velocidadeSeta) {
  do {
    unsigned long S = ((millis() / velocidadeSeta) % 2 == 0);
    if (S) {
      digitalWrite(SetaEsquerdaFrente, HIGH);
      digitalWrite(SetaEsquerdaTras, HIGH);
    } else {
      digitalWrite(SetaEsquerdaFrente, LOW);
      digitalWrite(SetaEsquerdaTras, LOW);
    }
    digitalWrite(SetaEsquerdaFrente, LOW);
    digitalWrite(SetaEsquerdaTras, LOW);
    digitalWrite(SetaDireitaTras, LOW);
    digitalWrite(SetaDireitaFrente, LOW);
  } while ((millis() - tempoInicialSeta) < tempoSeta);
}
void Buzzina(unsigned long tempoInicialBuzina, int tempoBuzina, int velocidadeBuzina, int somBuzina) {
  do {
    unsigned long B = ((millis() / velocidadeBuzina) % 2 == 0);
    if (B) {
      tone(Buzina, somBuzina);
    } else {
      noTone(Buzina);
    }
    noTone(Buzina);
  } while ((millis() - tempoInicialBuzina) < tempoBuzina);
}