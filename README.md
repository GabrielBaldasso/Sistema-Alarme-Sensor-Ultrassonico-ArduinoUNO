# Sistema de Alarme com Sensor Ultrassônico e Arduino (AVR)

Este projeto implementa um sistema de alarme utilizando um microcontrolador AVR e o sensor ultrassônico HC-SR04 para detecção de proximidade. O sistema aciona um LED como alerta visual quando um objeto é detectado a uma curta distância e, se um botão não for pressionado a tempo, um buzzer é ativado como alerta sonoro.

## Funcionalidades
- **Medição de Distância**: Utiliza o sensor HC-SR04 para calcular a distância de objetos próximos.
- **Alerta Visual (LED)**: Quando a distância medida for inferior ao limite, o LED é ativado.
- **Alerta Sonoro (Buzzer)**: Se o botão não for pressionado dentro de um tempo pré-definido, o buzzer será acionado.
- **Controle por Botão**: Um botão permite ativar ou desativar o sistema manualmente.
- **Temporização e Interrupções**: Utiliza o Timer1 para controlar o acionamento do buzzer após um determinado tempo.

## Componentes Utilizados
- **Microcontrolador AVR (ATmega328P ou similar)**
- **Sensor Ultrassônico HC-SR04**
- **LED**
- **Buzzer**
- **Botão de Reset**
- **Resistores e conexões diversas**

## Lógica de Funcionamento
1. O sensor ultrassônico mede a distância continuamente.
2. Se um objeto for detectado a uma distância inferior ao limite, o LED acende.
3. Um temporizador é iniciado para contar um período de resposta.
4. Se o botão for pressionado dentro do tempo, o sistema é resetado.
5. Se o botão não for pressionado, o buzzer é ativado como alerta adicional.
6. O botão também permite ativar/desativar o sistema manualmente.
