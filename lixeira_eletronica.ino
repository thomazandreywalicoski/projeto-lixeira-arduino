#include <Servo.h>

// Definição dos pinos para os sensores e LEDs
#define PINO_TRIG_PROXIMIDADE 6    // Pino de disparo do sensor de proximidade
#define PINO_ECHO_PROXIMIDADE 7    // Pino de recepção do sensor de proximidade
#define PINO_TRIG_NIVEL 8          // Pino de disparo do sensor de nível
#define PINO_ECHO_NIVEL 9          // Pino de recepção do sensor de nível
#define PINO_LED_VAZIA 10          // Pino para o LED que indica lixeira vazia
#define PINO_LED_MEIA 11           // Pino para o LED que indica lixeira meio cheia
#define PINO_LED_CHEIA 12          // Pino para o LED que indica lixeira cheia
#define PINO_SERVOMOTOR 5          // Pino para o controle do servo motor
#define PINO_BUZZER 4              // Pino para controlar o Buzzer

Servo servomotor; // Cria um objeto Servo para controlar o servo motor

void setup() {
  // Inicializa o servo motor no pino especificado
  servomotor.attach(PINO_SERVOMOTOR);
  
  // Define os pinos dos sensores como entrada ou saída
  pinMode(PINO_TRIG_PROXIMIDADE, OUTPUT);
  pinMode(PINO_ECHO_PROXIMIDADE, INPUT);
  pinMode(PINO_TRIG_NIVEL, OUTPUT);
  pinMode(PINO_ECHO_NIVEL, INPUT);
  
  // Define os pinos dos LEDs e do buzzer como saída
  pinMode(PINO_LED_VAZIA, OUTPUT);
  pinMode(PINO_LED_MEIA, OUTPUT);
  pinMode(PINO_LED_CHEIA, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);
}

float medirDistancia(int pinoTrig, int pinoEcho) {
  long duracao;
  float distancia;
  
  // Gera um pulso de 10 microssegundos no pino TRIG
  digitalWrite(pinoTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinoTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrig, LOW);
  
  // Mede o tempo que o sinal leva para retornar ao pino ECHO
  duracao = pulseIn(pinoEcho, HIGH);
  
  // Se duração for zero, indica que houve um erro
  if (duracao == 0) {
    return -1; // Valor inválido
  }
  
  // Calcula a distância com base na duração do pulso
  distancia = (duracao / 2.0) / 29.1;
  
  return distancia; // Retorna a distância medida
}

void loop() {
  // Mede a distância da proximidade
  float distanciaProximidade = medirDistancia(PINO_TRIG_PROXIMIDADE, PINO_ECHO_PROXIMIDADE);
  
  // Mede a distância do nível de lixo
  float distanciaNivel = medirDistancia(PINO_TRIG_NIVEL, PINO_ECHO_NIVEL);

  // Controle do Servo Motor baseado na proximidade
  if (distanciaProximidade > 0 && distanciaProximidade < 15) { // Se a distância da proximidade for menor que 20 cm
    servomotor.write(0);  // Define o ângulo 0 graus (extremo no sentido anti-horário)
    delay(2500); // Aguarda 2,5 segundos antes da próxima medição
  } else {
    servomotor.write(180); // Define o ângulo 180 graus (posição intermediária)
  }
  
  // Controle dos LEDs e Buzzer para indicar o nível de lixo
  if (distanciaNivel > 0 && distanciaNivel < 6) { // Se a distância do nível for menor que 6 cm (lixeira cheia)
    digitalWrite(PINO_LED_CHEIA, LOW);  
    digitalWrite(PINO_LED_MEIA, LOW);       // Acende a cor VERMELHA no led
    digitalWrite(PINO_LED_VAZIA, HIGH);   
    tone(PINO_BUZZER, 1500);  // Emite um tom de 1500 Hz
    servomotor.write(0);
    delay(4000); // Aguarda 4 segundos antes da próxima medição
  } else if (distanciaNivel >= 6 && distanciaNivel < 20) { // Se a distância do nível for menor que 20 cm (lixeira meio cheia)
    digitalWrite(PINO_LED_CHEIA, LOW);  
    digitalWrite(PINO_LED_MEIA, HIGH);       // Acende a cor AZUL no led
    digitalWrite(PINO_LED_VAZIA, LOW);   
    noTone(PINO_BUZZER);    // Desliga o buzzer
    delay(1000); // Aguarda 1 segundo antes da próxima medição
  } else {
    digitalWrite(PINO_LED_CHEIA, HIGH);   
    digitalWrite(PINO_LED_MEIA, LOW);       // Acende a cor VERDE no led
    digitalWrite(PINO_LED_VAZIA, HIGH);  
    noTone(PINO_BUZZER);    // Desliga o buzzer
    delay(1000); // Aguarda 1 segundo antes da próxima medição
  }
}
