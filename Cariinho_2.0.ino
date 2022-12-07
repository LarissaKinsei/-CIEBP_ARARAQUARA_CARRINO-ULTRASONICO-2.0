/*
      AUTOR:   CIEBP Araraquara - Espaço 6 Robótica e Modelagem
      SKETCH:  Arduino - Carrinho com sensor de obstáculo ultrassonico, buzzer e setas
   DADOS: 09/11/2022
*/

// Definir pinos para componentes
#define MesquerdoF1 5//esquerda frente
#define MesquerdoT2 7//esquerda tras
#define MdireitoT3 8//direita tras
#define MdireitoF4 10//direita frente

// Definier pinos dos leds
#define Pdireitoacima 11//direita frente
#define Pdireitoabaixo 3//direita tras
#define Pesquerdoacima 6// esquerda frente
#define Pesquerdoabaixo 13// esquerda tras

// Definier pinos do buzzer - som
#define Buzzersom 4 //Pino do buzzer
int freq;// declarando variável global para armazernar a frequencia do tom


// Definir pinos do sensor Ultrasoonico
const int
ECHO = 12,
TRIG = 9,
velocidade = 83;

// Motor Velocidade
int
VelocidadeMD = velocidade + 18,
VelocidadeME = velocidade;

// Distancia do obstaculo
int //não assinado
obstaculo,
direcao;

int Valor_obstaculo(int TRIG, int ECHO) { //Função para leitura do sensor
  digitalWrite(TRIG, LOW); //Função que "emite o sinal" para leirura do obstaculo/ desligada
  delayMicroseconds(1);
  digitalWrite(TRIG, HIGH); //Função que "emite o sinal" para leirura do obstaculo/ ligado
  delayMicroseconds(5);
  digitalWrite(TRIG, LOW); //FALTA COMENTAR A FUNÇÃO DESTE COMANDO
  return 
  pulseIn (ECHO, HIGH) / 58; //Retorno da função sensor_morcego será um pulseIN ()
}

//Função que faz o carro andar pra frente
void Frente () {
  analogWrite (MesquerdoF1, VelocidadeMD);
  analogWrite(MdireitoF4, VelocidadeME - 3);
}

// Função que faz o carro andar pra tras
void Tras () {
  analogWrite (MesquerdoT2, VelocidadeMD);
  analogWrite(MdireitoT3, VelocidadeME);
}

// Função que faz o carro para quando esta andando pra frente
void StopFrente () {
  digitalWrite(MesquerdoF1, LOW);
  digitalWrite(MdireitoF4, LOW);
}

void StopTras  () {
  digitalWrite(MesquerdoT2, LOW);
  digitalWrite(MdireitoT3, LOW);
   digitalWrite(Buzzersom, HIGH);
    delay(500);
    digitalWrite(Buzzersom, LOW);
    delay(500);
    
    for (freq = 400; freq < 100; freq++) 
    tone(4, freq, 10);
}

// Função que faz o carro virar a direita
void direita() {
  analogWrite(MesquerdoF1, velocidade);
  delay(1000);
  analogWrite(MesquerdoF1, LOW);
   digitalWrite(Pdireitoacima, HIGH);
    digitalWrite(Pdireitoabaixo, HIGH);
    delay(500);
    digitalWrite(Pdireitoacima, LOW);
    digitalWrite(Pdireitoabaixo, LOW);
    delay(500);
}

// Função que faz o carro virar a esquera
void esquerda() {
  analogWrite(MdireitoF4, velocidade - 20);
  delay(1000);
  analogWrite(MdireitoF4, LOW);
  digitalWrite(Pesquerdoacima, HIGH);
    digitalWrite(Pesquerdoabaixo, HIGH);
    delay(500);
    digitalWrite(Pesquerdoacima, LOW);
    digitalWrite(Pesquerdoabaixo, LOW);
    delay(500);
}

// função que da Ré
void Re() {
  analogWrite(MesquerdoT2, VelocidadeMD);
  analogWrite(MdireitoT3, VelocidadeME);
   digitalWrite(Buzzersom, HIGH);
    delay(500);
    digitalWrite(Buzzersom, LOW);
    delay(500);
    
    for (freq = 400; freq < 100; freq++) 
    tone(4, freq, 10);
}

// Função que para a ré
void StopRe() {
  analogWrite(MesquerdoT2, 0);
  analogWrite(MdireitoT3, 0);
   digitalWrite(Buzzersom, HIGH);
    delay(500);
    digitalWrite(Buzzersom, LOW);
    delay(500);
    
    for (freq = 400; freq < 100; freq++)
    tone(4, freq, 10);
    
}

//Define pinos como entrada ou saida
void setup() {
  pinMode(Pdireitoacima , OUTPUT);
  pinMode(Pdireitoabaixo , OUTPUT);
  pinMode(Pesquerdoacima , OUTPUT);
  pinMode(Pesquerdoabaixo , OUTPUT);
  pinMode(Buzzersom , OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(MesquerdoF1, OUTPUT);
  pinMode(MesquerdoT2, OUTPUT);
  pinMode(MdireitoT3, OUTPUT);
  pinMode(MdireitoF4, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  Serial.println(obstaculo);
  delay(1000);
  obstaculo = Valor_obstaculo(TRIG, ECHO);

  if (obstaculo <= 50) {
    direcao = random(1, 3);
    Serial.println(direcao);
    delay(500);

    switch (direcao) {
      case 1:
        StopFrente();
        delay(2000);

        Re();
        delay(1000);
        StopRe();
        delay (2000);

        esquerda();
        delay (1000);
        break;
    

caso2:
        StopFrente();
        delay (2000);

        Re();
        delay (1000);
        StopRe();
        
          direita();
          delay (2000);
                    
         break;
        }
    } else {
         Frente();
  }
}
