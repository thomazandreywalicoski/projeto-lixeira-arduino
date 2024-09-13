---

# **Sistema de Gerenciamento de Lixeira Inteligente**

## **Descrição**

Este projeto utiliza sensores ultrassônicos, LEDs, um servo motor e um buzzer para gerenciar e monitorar o nível de uma lixeira. O sistema é capaz de detectar a proximidade de um objeto para acionar a abertura da tampa da lixeira e também avalia o nível de lixo para acionar LEDs e um buzzer que indicam o status da lixeira.

## **Componentes Utilizados**

- **Sensores Ultrassônicos**:
  - Sensor de Proximidade (Pino TRIG e ECHO)
  - Sensor de Nível (Pino TRIG e ECHO)
- **LEDs**:
  - LED para lixeira vazia
  - LED para lixeira meio cheia
  - LED para lixeira cheia
- **Servo Motor**: Para controlar a abertura e fechamento da tampa da lixeira
- **Buzzer**: Para emitir um sinal sonoro quando a lixeira está cheia

## **Esquema de Ligação**

- **Sensor de Proximidade**:
  - Pino TRIG: Pino 6
  - Pino ECHO: Pino 7

- **Sensor de Nível**:
  - Pino TRIG: Pino 8
  - Pino ECHO: Pino 9

- **LEDs**:
  - LED Vazía: Pino 10
  - LED Meio Cheia: Pino 11
  - LED Cheia: Pino 12

- **Servo Motor**:
  - Pino de Controle: Pino 5

- **Buzzer**:
  - Pino: Pino 4

## **Funcionamento**

1. **Medição de Proximidade**: O sensor de proximidade mede a distância do objeto e aciona o servo motor para abrir a tampa da lixeira quando a distância é menor que 15 cm.
2. **Detecção do Nível de Lixo**: O sensor de nível mede a altura do lixo na lixeira. Dependendo da distância medida, o sistema acende o LED correspondente e ativa o buzzer:
   - **Menor que 6 cm**: LED Vermelho aceso, buzzer emite um som de 1500 Hz (lixeira cheia).
   - **Entre 6 cm e 20 cm**: LED Azul aceso (lixeira meio cheia).
   - **Maior que 20 cm**: LED Verde aceso (lixeira vazia).

## **Instalação**

1. Conecte todos os componentes conforme os pinos definidos acima.
2. Carregue o código no seu microcontrolador Arduino usando a IDE Arduino.
