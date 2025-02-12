//Bibliotecas que foram necessárias para o funcionamento adequado do código
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

//Definição das constantes que foram utilizadas no código
#define SERVO_PIN 22  // GPIO do servomotor
#define LED_PIN 12 // GPIO do LED (Usada para fazer o teste do requisito 6 da atividade)
// Comportamento do LED: Ao usar o LED no lugar do servo motor foi visto que,
//                       o LED brilha mais na configuração da POS_180, brilho
//                       médio na POS_90 e por fim, ficou com o brilho mais
//                       fraco na POS_0. Já enquanto ele muda de 0° a 180°
//                       o seu brilho vai aumentando e diminuindo respectivamente.

// Cálculo da frequência do PWM:
// Frequência desejada: 50Hz -> Período = 1 / 50 = 20ms = 20000µs

#define PWM_DIVISER 55.0  // Divisor do clock para o PWM

// O clock base do RP2040 é 125MHz
// Frequência do contador PWM:
// f_cont = 125.000.000 / PWM_DIVISER
// f_cont = 125.000.000 / 55 = 2.272.727,27 Hz

// PWM_WRAP = f_cont * T
// PWM_WRAP = 2.272.727,27 * 0.02 = 45454,54 ~ 45000 (aproximado)
#define PWM_WRAP 45000  // Valor máximo do contador - WRAP

// Cálculo dos valores de nível PWM para cada ângulo:
// Valor PWM = (Tempo do pulso (µs) * PWM_WRAP) / T

// Para 0° (500µs):  (500 * 45000) / 20000 = 1125
#define POS_0 1125  // 500µs para 0 graus
// Para 90° (1500µs): (1500 * 45000) / 20000 = 3375
#define POS_90 3375  // 1500µs para 90 graus
// Para 180° (2500µs): (2500 * 45000) / 20000 = 5625
#define POS_180 5625 // 2500µs para 180 graus

/**
 * @brief Configura o módulo PWM para o servo.
 * @param slice_num Número do slice PWM.
 */
void pwm_setup(uint slice_num);

/**
 * @brief Define a posição do servo.
 * @param slice_num Número do slice PWM.
 * @param level Nível PWM correspondente ao ângulo desejado.
 */
void set_servo_position(uint slice_num, uint16_t level);

/**
 * @brief Realiza a varredura contínua do servo de 0° a 180° e vice-versa.
 * @param slice_num Número do slice PWM.
 */
void servo_sweep(uint slice_num);

int main() {
    stdio_init_all();
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o número do slice PWM para o pino do servo
    pwm_setup(slice_num);                             // Configura o PWM para o servo

    while (1) {
        printf("Posição 180 graus\n");
        set_servo_position(slice_num, POS_180); // Move o servo para 180°
        sleep_ms(5000);

        printf("Posição 90 graus\n");
        set_servo_position(slice_num, POS_90); // Move o servo para 90°
        sleep_ms(5000);

        printf("Posição 0 graus\n");
        set_servo_position(slice_num, POS_0); // Move o servo para 0°
        sleep_ms(5000);

        servo_sweep(slice_num); // Inicia a movimentação contínua do servo
    }
}

void pwm_setup(uint slice_num) {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Configura o pino do servo como saída PWM
    pwm_set_clkdiv(slice_num, PWM_DIVISER);     // Define o divisor do clock do PWM
    pwm_set_wrap(slice_num, PWM_WRAP);         // Define o valor máximo do contador PWM
    pwm_set_enabled(slice_num, true);     // Habilita o PWM
}

void set_servo_position(uint slice_num, uint16_t level) {
    pwm_set_gpio_level(SERVO_PIN, level); // Define o nível do PWM para posicionar o servo
}

void servo_sweep(uint slice_num) {
    printf("Movimentação contínua de 0° a 180° e vice-versa\n");
    for (uint16_t pos = POS_0; pos <= POS_180; pos += 5) { // Incrementa suavemente até 180°
        set_servo_position(slice_num, pos);
        sleep_ms(10); // Pequeno atraso para suavizar o movimento
    }
    for (uint16_t pos = POS_180; pos >= POS_0; pos -= 5) { // Decrementa suavemente até 0°
        set_servo_position(slice_num, pos);
        sleep_ms(10);
    }
}
