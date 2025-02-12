# Projeto: Controle de Servomotor por PWM

## Autor
**Levi Silva Freitas**

## Data
**11 de fevereiro de 2025**

## Link de entrega
Link: A gravar...

## Requisito n° 6
Se o LED GPIO 12 fosse controlado diretamente pelo sinal PWM utilizado para o servo, seu comportamento dependeria do duty cycle do PWM:

Posição 0° (500µs) → O LED ficaria com brilho fraco, pois estaria ligado apenas uma pequena fração do tempo.
Posição 90° (1500µs) → O LED ficaria com brilho médio, já que o PWM estaria ligado por um tempo maior.
Posição 180° (2500µs) → O LED ficaria mais brilhante, pois o sinal PWM teria um tempo ativo maior.
Movimentação contínua (0° a 180° e vice-versa) → O LED aumentaria e diminuiria o brilho suavemente, simulando um efeito de pulsação gradual.

Ou seja, no lugar do servo motor, o LED funcionaria como um indicador visual da variação do duty cycle, com intensidade proporcional ao tempo ativo do PWM.

## Descrição do Projeto
Este projeto implementa o controle de um **servomotor** utilizando o **PWM** do microcontrolador **Raspberry Pi Pico W**. O sistema é simulado no **Wokwi** e atende aos requisitos da atividade acadêmica.

O código permite:
- Controlar um **servo micro padrão** com **movimentação precisa**.
- Definir **ângulos fixos** de 0°, 90° e 180°.
- Realizar uma **varredura contínua suave** entre 0° e 180°.
- Testar a influência do **PWM no LED RGB (GPIO 12)** via **BitDogLab**.

## Componentes Utilizados
- **Raspberry Pi Pico W**
- **Servo Micro Padrão** – GPIO **22**
- **LED RGB** – GPIO **12** (para testes no BitDogLab)
- **Simulador Wokwi**

## Estrutura do Código

### 1. Configuração do PWM
Configuração do PWM para controle do servo:
```c
#define PWM_DIVISER 55.0
#define PWM_WRAP 45000
```

### 2. Definição das Posições do Servo
Mapeamento dos tempos de pulso para ângulos:
```c
#define POS_0 1125  // 0 graus
#define POS_90 3375 // 90 graus
#define POS_180 5625 // 180 graus
```

### 3. Função de Configuração do PWM
Inicializa e configura o módulo PWM:
```c
void pwm_setup(uint slice_num) {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    pwm_set_clkdiv(slice_num, PWM_DIVISER);
    pwm_set_wrap(slice_num, PWM_WRAP);
    pwm_set_gpio_level(SERVO_PIN, POS_90);
    pwm_set_enabled(slice_num, true);
}
```

### 4. Controle do Servo
Função para definir a posição do servo:
```c
void set_servo_position(uint slice_num, uint16_t level) {
    pwm_set_gpio_level(SERVO_PIN, level);
}
```

### 5. Movimento Contínuo
Movimenta suavemente entre 0° e 180°:
```c
void servo_sweep(uint slice_num) {
    for (uint16_t pos = POS_0; pos <= POS_180; pos += 5) {
        set_servo_position(slice_num, pos);
        sleep_ms(10);
    }
    for (uint16_t pos = POS_180; pos >= POS_0; pos -= 5) {
        set_servo_position(slice_num, pos);
        sleep_ms(10);
    }
}
```

### 6. Teste com LED RGB no BitDogLab
O LED RGB na GPIO 12 pode piscar ou variar de intensidade dependendo da interferência do PWM do servo.

## Como Executar
1. **Configurar o Ambiente**
   - Clone o meu repositório

2. **Compilar e Carregar o Código**

3. **Executar no Wokwi**
   - Abra o arquivo diagram.json
   - Carregue e execute o código

## Conclusão
Este projeto demonstra o **controle de servomotor via PWM**, proporcionando um aprendizado prático sobre sistemas embarcados.

## Contato
✉️ **Email:** [lsfreitas218@gmail.com]

