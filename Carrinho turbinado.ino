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
int velocidadeParametro = 180;  // velocidade parametro dos motores
int velocidade1 = 0.75;
int velocidade2 = 0.5;
int velocidade3 = 0.35;
float distanciaCM = 0;
int var = 2;
bool Interruptor;
unsigned long currentTime = 0;
//unsigned long currentTime2 = 0;
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
  Serial.println(distanciaCM);
  Serial.println(var);

  int direcao = random(2);
  //Casos 1: para o carrinho desviar dos obstaculos
  if (distanciaCM > 200 && distanciaCM < 300 && var % 2 == 0) {
    //Todo: se identificar um obstaculo a frente de 2m a 3m ele ira buzina 2x
    //Variavis pares
    EstadoVariavel(3000);
    Buzzina(millis(), 3000, 300, 3200);
    Direcao(2, 255, 255);

    //Casos 2: para o carrinho desviar dos obstaculos
  } else if (distanciaCM > 200 && distanciaCM < 300 && var % 2 == 1) {
    //Todo: Se identificar um obstaculo a frente maior de 2m e menor de 3m ele ira buzinar e redizir a velocidade dos motores
    //Variaveis impares

    EstadoVariavel(3000);

    Buzzina(millis(), 3000, 300, 3200);

    // Frente((velocidadeParametro * velocidade1), (velocidadeParametro * velocidade1));
    Direcao(2, (velocidadeParametro * velocidade1), (velocidadeParametro * velocidade1));

    //Casos 3: para o carrinho desviar dos obstaculos
  } else if (distanciaCM > 150 && distanciaCM <= 200 && var % 2 == 0) {
    //Todo: Se identificar um obstaculo a frente  maior que 1,5m e menor que 2m ele ira buzinar e acelerar um dos motores para mudar a direção
    //Variavis pares

    EstadoVariavel(5000);

    Buzzina(millis(), 3000, 300, 3200);

    //Frente((velocidadeParametro * velocidade1), (velocidadeParametro * velocidade1));

    if (direcao == 0) {
      Direcao(0, (velocidadeParametro * velocidade2), (velocidadeParametro * velocidade1));
    } else if (direcao == 1) {
      Direcao(1, (velocidadeParametro * velocidade1), (velocidadeParametro * velocidade2));
    }

    //Casos 4: para o carrinho desviar dos obstaculos
  } else if (distanciaCM > 150 && distanciaCM <= 200 && var % 2 == 1) {
    //Todo: Se identificar um obstaculo a frente  maior que 1,5m e menor que 2m ele ira reduzir novamente a velocidade dos motores, buzinar e acelerar um dos motores para mudar a direção
    //Variaveis impares

    EstadoVariavel(5000);

    Buzzina(millis(), 3000, 300, 3200);

    //Frente((velocidadeParametro * velocidade1), (velocidadeParametro * velocidade1));

    if (direcao == 0) {
      Direcao(0, (velocidadeParametro * velocidade3), (velocidadeParametro * velocidade2));
    } else if (direcao == 1) {
      Direcao(1, (velocidadeParametro * velocidade2), (velocidadeParametro * velocidade3));
    }

    //Casos 5: para o carrinho desviar dos obstaculos
  } else if ((distanciaCM <= 150) && (Interruptor == true)) {
    //Todo: Se identificar um obstaculo a frente  maior que 1m e menor que 1,5m ele ira para o carrinho, vai buzinar,
    //dar ré com o pisca alerta e buzina acionados, escolher um lado para virar sinalizando o lado escolhido e siga em frente
    Comando(millis(), direcao);
    Interruptor = false; 

    /*/Casos 6: para o carrinho desviar dos obstaculos
  } else if (distanciaCM < 100) {
    //Todo: Se identificar um obstaculo a frente menor que 1m ele ira parar, dar ré, virar 180 graus e siguir em frente
  */} 
    else {
      Direcao(2, velocidadeParametro, velocidadeParametro);
      // Função do carrinho para seguir sempre frente
    }
    delay(100);
}
/*/Função de controle da velocidade do carrinho para cada motor da frente
void Frente(int velocidadeMotorDireito, int velocidadeMotorEsquerdo) {
  analogWrite(MotorEsquerdoFrente, velocidadeMotorEsquerdo);
  analogWrite(MotorDireitoFrente, velocidadeMotorDireito);
}
//Função de controle da velocidade do carrinho para cada motor de trás
void Tras(int velocidade) {
  analogWrite(MotorEsquerdoTras, velocidade);
  analogWrite(MotorDireitoTras, velocidade);
}
//Função de controle da velocidade do carrinho para cada motor da direita
void Direta(int velocidadeMD, int velocidadeME) {
  analogWrite(MotorDireitoTras, velocidadeMD);
  analogWrite(MotorEsquerdoFrente, velocidadeME);
}
//Função de controle da velocidade do carrinho para cada motor da esquerda
void Esquerda(int velocidadeMD, int velocidadeME) {
  analogWrite(MotorDireitoFrente, velocidadeMD);
  analogWrite(MotorEsquerdoTras, velocidadeME);
}*/
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
    } else {
      noTone(Buzina);
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
void Comando(unsigned long currentTime2, int direcao) {

  if ((((millis() - currentTime2) < 1000))) {
    Direcao(4, 0, 0);
    currentTime2 = millis(); 
  } else if ((millis() - currentTime2) > 1000) {
    if (direcao == 0) {
      Direcao(0, (velocidadeParametro * velocidade3), (velocidadeParametro * velocidade2));
      Interruptor = true;
    } else if (direcao == 1) {
      Direcao(1, (velocidadeParametro * velocidade2), (velocidadeParametro * velocidade3));
      Interruptor = true;
    }
  }
}