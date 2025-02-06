#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Definições dos pinos
#define TRIG    PD5  
#define ECHO    PD4  
#define LED     PB1  
#define BUTTON  PD2  
#define BUZZER  PD6  

// Variáveis globais (1: ligado, 0: desligado)
volatile uint8_t sensor_ativo = 1;
volatile uint8_t botao_pressionado = 0; // Estado do botão (0: não pressionado, 1: pressionado)
volatile uint8_t led_ligado = 0;  
volatile uint8_t buzzer_ligado = 0;  
volatile uint8_t temporizador_iniciado = 0;  // Flag para verificar se o temporizador começou

uint16_t medir_distancia() {
    uint16_t contador;
    
    if (sensor_ativo) {
        PORTD &= ~(1 << TRIG);  
        _delay_us(2);
        PORTD |= (1 << TRIG);  
        _delay_us(10);  
        PORTD &= ~(1 << TRIG);  

        while (!(PIND & (1 << ECHO)));  
        contador = 0;
      
        while (PIND & (1 << ECHO)) {  
            _delay_us(1);
            contador++;
          
            if (contador > 4000) return 400;
        }
      
        return (contador / 2) / 2;  // Retorna a distância em centímetros
    }
    return 2;
}

void iniciar_temporizador1() {
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);  // Modo CTC, prescaler de 1024
    OCR1A = 312500;  // Formula (16MHz / 1024 / 1Hz * 10)
    TIMSK1 |= (1 << OCIE1A);  // Habilita interrupção do Timer1
}

void verificar_clique_botao() {
    if (!(PIND & (1 << BUTTON)) && !botao_pressionado) {
        _delay_ms(50);
        if (!(PIND & (1 << BUTTON))) {
            botao_pressionado = 1;
            sensor_ativo = !sensor_ativo;  
            if (!sensor_ativo) {
                PORTB &= ~(1 << LED);  
                PORTD &= ~(1 << BUZZER);  
                led_ligado = 0;
                buzzer_ligado = 0;
                temporizador_iniciado = 0;  // Reseta o temporizador
            }
        }
    } else if (PIND & (1 << BUTTON)) {  
        botao_pressionado = 0;  
    }
}

ISR(TIMER1_COMPA_vect) {
    if (led_ligado && !buzzer_ligado) {
        PORTD |= (1 << BUZZER);
        buzzer_ligado = 1;
    }
}

int main(void) {

    DDRD |= (1 << TRIG) | (1 << BUZZER);  // TRIG e BUZZER como saída
    DDRD &= ~((1 << ECHO) | (1 << BUTTON)); // ECHO e BUTTON como entrada
    DDRB |= (1 << LED);  
    PORTD |= (1 << BUTTON);

    iniciar_temporizador1();

    sei();  //serve para habilita interrupções globais

    while (1) {
        uint16_t distancia = medir_distancia();

        if (distancia < 2 && sensor_ativo && !led_ligado) {
            PORTB |= (1 << LED);  
            led_ligado = 1;
            if (!temporizador_iniciado) {
                TCNT1 = 0;
                temporizador_iniciado = 1;
            }
        }
        verificar_clique_botao();
    }
}