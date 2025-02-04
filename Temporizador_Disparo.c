#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

// Definindo os pinos dos LEDs e o botão
# define LED_PIN_BLUE 11 
# define LED_PIN_RED 12
# define LED_PIN_GREEN 13
# define BUTTON_A 5

// Variável para controlar a ativação do LED
volatile bool led_sequence_active = false;

// Função de callback para desligar os LEDs em sequência
bool turn_off_callback(alarm_id_t id, void *user_data) {
    static int state = 0;
    
    switch (state) {
        case 0:
            gpio_put(LED_PIN_BLUE, 0);
            state++;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            break;
        case 1:
            gpio_put(LED_PIN_RED, 0);
            state++;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            break;
        case 2:
            gpio_put(LED_PIN_GREEN, 0);
            state = 0;
            led_sequence_active = false;  // Permitir nova ativação pelo botão
            break;
    }
    return false;
}

// Função de callback para o botão
void button_callback(uint gpio, uint32_t events) {
    // Verifica se a sequência de LEDs está ativa 
    if (!led_sequence_active) { 
        led_sequence_active = true; // Impede que a sequência seja ativada novamente
        // Aciona os LEDs
        gpio_put(LED_PIN_BLUE, 1); 
        gpio_put(LED_PIN_RED, 1);
        gpio_put(LED_PIN_GREEN, 1);
        add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Temporizador
    }
}

int main()
{
    stdio_init_all(); // Inicializa a comunicação serial

    // Inicializa os pinos dos LEDs e do botão
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);


    while (true) {
        // Adiciona um callback para o botão
        gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_RISE, true, &button_callback);
        sleep_ms(1000);
    }
}