// Definier pinos do buzzer - som
#define Buzzersom 4 //Pino do buzzer
int freq;// declarando variável global para armazernar a frequencia do tom

void setup() {
  pinMode(Buzzersom , OUTPUT);

}

void loop() {
    digitalWrite(Buzzersom, HIGH);
    delay(500);
    digitalWrite(Buzzersom, LOW);
    delay(500);
    
    for (freq = 400; freq < 100; freq++) {
    tone(4, freq, 10);
  
  }
}
