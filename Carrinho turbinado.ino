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
int direcao = 0;
int velocidadeParametro = 150;  // velocidade parametro dos motores
int velocidade1 = 0.75;
int velocidade2 = 0.5;
int velocidade3 = 0.35;
int gatilho;
float distanciaCM = 0;
int var = 2;
bool interruptor = true;
int c = 0;
unsigned long currentTime = 0;
unsigned long currentTime2 = 0;
unsigned long currentTime3 = 0;
unsigned long currentTime4 = 0;
unsigned long currentTime5 = 0;
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
  distanciaCM = ultrasonic.getDistanceCM();  //Biblioteca utilizada do arduino
  DirecaoAtrasada();

  //Casos 1: para o carrinho desviar dos obstaculos
  if (distanciaCM > 200 && distanciaCM < 300 && var % 2 == 0) {
    //Todo: se identificar um obstaculo a frente de 2m a 3m ele ira buzina 2x
    //Variavis pares

    //EstadoVariavel(2000);
    //Direcao(2, 160, 160);

    //Casos 2: para o carrinho desviar dos obstaculos
  } else if (distanciaCM > 200 && distanciaCM < 300 && var % 2 == 1) {
    //Todo: Se identificar um obstaculo a frente maior de 2m e menor de 3m ele ira buzinar e redizir a velocidade dos motores
    //Variaveis impares

    //int v1 = velocidadeParametro * velocidade2;
    // int v2 = velocidadeParametro * velocidade2;
    // EstadoVariavel(3000);
    //Direcao(2, 110, 110);

    //Casos 3: para o carrinho desviar dos obstaculos
  } else if (distanciaCM > 150 && distanciaCM <= 200) {
    //Todo: Se identificar um obstaculo a frente  maior que 1,5m e menor que 2m ele ira reduzir novamente a velocidade dos motores, buzinar e acelerar um dos motores para mudar a direção
    //Variaveis impares
    EstadoVariavel(500);
    Serial.println("caso 3");

    //Casos 4: para o carrinho desviar dos obstaculos
  } else if ((distanciaCM <= 150)) {
    //Todo: Se identificar um obstaculo a frente menor que 1,5m ele ira para o carrinho, vai buzinar,
    //dar ré com o pisca alerta e buzina acionados, escolher um lado para virar sinalizando o lado escolhido e siga em frente
    EstadoVariavel(500);

    SentidoAtrasado(direcao);

    //Casos 6: para o carrinho desviar dos obstaculos
  } else {
    Direcao(2, 140, 140);
  }
}

void SentidoAtrasado(int direcao) {
  if (millis() - c > 5000) {
    c = millis();
    if (direcao == 0) {
      Direita(0, 90);
    } else if (direcao == 1) {
      Esquerda(90, 0);
    }
  }
}
//Função de escolha de direção com atraso
void DirecaoAtrasada() {
  if ((millis() - currentTime5 > 1500)) {
    currentTime5 = millis();
    direcao = random(2);
  }
}
//Função de controle da seta alerta do carrinho para piscar os 4 leds
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
//Função de controle da seta re do carrinho para piscar 2 leds de tras
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
//Função de controle da seta direita do carrinho para piscar os 2 leds do lado direito
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
//Função de controle da seta esquerda do carrinho para piscar os 2 leds do lado esquerdo
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
//Função de controle do buzzer para emitir o som de buzina para cada caso acima
void Buzzina(unsigned long tempoInicialBuzina, int tempoBuzina, int velocidadeBuzina, int somBuzina) {
  do {
    unsigned long B = ((millis() / velocidadeBuzina) % 2 == 0);
    if (B) {
      tone(Buzina, somBuzina);
      digitalWrite(Buzina, HIGH);
    } else {
      noTone(Buzina);
      digitalWrite(Buzina, LOW);
    }
    noTone(Buzina);
  } while ((millis() - tempoInicialBuzina) < tempoBuzina);
}
void EstadoVariavel(int intervaloTempo) {
  if (millis() - currentTime > intervaloTempo) {
    currentTime = millis();
    var++;
  }
}
void Direcao(int dir, int velocidadeMotorEsquerdo, int velocidadeMotorDireito) {
  switch (dir) {
    case 0:
      analogWrite(MotorDireitoFrente, velocidadeMotorDireito);
      analogWrite(MotorEsquerdoTras, velocidadeMotorEsquerdo);
      break;

    case 1:
      analogWrite(MotorDireitoTras, velocidadeMotorDireito);
      analogWrite(MotorEsquerdoFrente, velocidadeMotorEsquerdo);
      break;

    case 2:
      analogWrite(MotorEsquerdoFrente, velocidadeMotorEsquerdo);
      analogWrite(MotorDireitoFrente, velocidadeMotorDireito);
      break;

    case 3:
      analogWrite(MotorEsquerdoTras, velocidadeMotorEsquerdo);
      analogWrite(MotorDireitoTras, velocidadeMotorDireito);
      break;

    case 4:
      analogWrite(MotorDireitoFrente, 0);
      analogWrite(MotorDireitoTras, 0);
      analogWrite(MotorEsquerdoFrente, 0);
      analogWrite(MotorEsquerdoTras, 0);
      break;
  }
}
void Esquerda(int velocidadeMotorEsquerdo, int velocidadeMotorDireito) {
  analogWrite(MotorDireitoFrente, velocidadeMotorDireito);
  analogWrite(MotorEsquerdoTras, velocidadeMotorEsquerdo);
}
void Direita(int velocidadeMotorEsquerdo, int velocidadeMotorDireito) {
  analogWrite(MotorDireitoTras, velocidadeMotorDireito);
  analogWrite(MotorEsquerdoFrente, velocidadeMotorEsquerdo);
}