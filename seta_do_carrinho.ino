
// Definier pinos dos leds
#define Pdireitoacima 11//direita frente
#define Pdireitoabaixo 3//direita tras
#define Pesquerdoacima 6// esquerda frente
#define Pesquerdoabaixo 13// esquerda tras


void setup() {
  pinMode(Pdireitoacima , OUTPUT);
  pinMode(Pdireitoabaixo , OUTPUT);
  pinMode(Pesquerdoacima , OUTPUT);
  pinMode(Pesquerdoabaixo , OUTPUT);
}

void loop() {

    digitalWrite(Pdireitoacima, HIGH);
    digitalWrite(Pdireitoabaixo, HIGH);
    delay(500);
    digitalWrite(Pdireitoacima, LOW);
    digitalWrite(Pdireitoabaixo, LOW);
    delay(500);
    digitalWrite(Pesquerdoacima, HIGH);
    digitalWrite(Pesquerdoabaixo, HIGH);
    delay(500);
    digitalWrite(Pesquerdoacima, LOW);
    digitalWrite(Pesquerdoabaixo, LOW);
    delay(500);
    
}
