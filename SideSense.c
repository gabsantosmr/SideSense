#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "ssd1306.h"




#define BTN_E_PIN 5
#define BTN_D_PIN 6
#define UART_ID uart0
#define UART_TX 0
#define UART_RX 1
#define BAUD_RATE 115200
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

void consulta() {
    ssd1306_fill(&ssd, false);
    ssd1306_draw_string(&ssd, "O BOTAO CORRESPONDE A DIRECAO:", 0, 10);
    ssd1306_send_data(&ssd);

    while (true) {
        char input_string[20];

        if(!gpio_get(BTN_E_PIN)) {
            ssd1306_fill(&ssd, false);
            ssd1306_draw_string(&ssd, "O BOTAO CORRESPONDE A DIRECAO:", 0, 10);
            snprintf(input_string, sizeof(input_string), "ESQUERDA");
            ssd1306_draw_string(&ssd, input_string, 10, 50);
            ssd1306_send_data(&ssd);
        }
        if(!gpio_get(BTN_D_PIN)) {
            ssd1306_fill(&ssd, false);
            ssd1306_draw_string(&ssd, "O BOTAO CORRESPONDE A DIRECAO:", 0, 10);
            snprintf(input_string, sizeof(input_string), "DIREITA");
            ssd1306_draw_string(&ssd, input_string, 10, 50);
            ssd1306_send_data(&ssd);
        }

        sleep_ms(100);
    }
}

void game() {
    while (true) {
        int contador = 0;
        uint32_t tempo_inicio = to_ms_since_boot(get_absolute_time());

        ssd1306_fill(&ssd, false);
        ssd1306_draw_string(&ssd, "PREPARE-SE", 10, 20);
        ssd1306_send_data(&ssd);
        sleep_ms(3000);

        while (to_ms_since_boot(get_absolute_time()) - tempo_inicio < 30000) {
            int direcao = rand() % 2;

            ssd1306_fill(&ssd, false);
            if (direcao == 0) {
                ssd1306_draw_string(&ssd, "ESQUERDA", 10, 20);
                sleep_ms(100);
            } else {
                ssd1306_draw_string(&ssd, "DIREITA", 10, 20);
                sleep_ms(100);
            }
            ssd1306_send_data(&ssd);

            while (true) {
                if (direcao == 0 && !gpio_get(BTN_E_PIN)) {
                    contador++;
                    ssd1306_fill(&ssd, false);
                    ssd1306_send_data(&ssd);
                    sleep_ms(100);
                    break;
                }
                if (direcao == 1 && !gpio_get(BTN_D_PIN)) {
                    contador++;
                    ssd1306_fill(&ssd, false);
                    ssd1306_send_data(&ssd);
                    sleep_ms(100);
                    break;
                } 
                if (direcao == 1 && !gpio_get(BTN_E_PIN)) {
                    char pontuacao[20];
                    ssd1306_fill(&ssd, false);
                    ssd1306_draw_string(&ssd, "VOCE ERROU", 0, 10);
                    ssd1306_draw_string(&ssd, "VOCE CONSEGUIU", 0, 20);
                    snprintf(pontuacao, sizeof(pontuacao), "%d PONTOS", contador);
                    ssd1306_draw_string(&ssd, pontuacao, 0, 50);
                    ssd1306_send_data(&ssd);
                }
                if (direcao == 0 && !gpio_get(BTN_D_PIN)) {
                    char pontuacao[20];
                    ssd1306_fill(&ssd, false);
                    ssd1306_draw_string(&ssd, "VOCE ERROU", 0, 10);
                    ssd1306_draw_string(&ssd, "VOCE CONSEGUIU", 0, 20);
                    snprintf(pontuacao, sizeof(pontuacao), "%d PONTOS", contador);
                    ssd1306_draw_string(&ssd, pontuacao, 0, 50);
                    ssd1306_send_data(&ssd);
                }
            }
        }

        char pontuacao[20];
        ssd1306_fill(&ssd, false);
        ssd1306_draw_string(&ssd, "PARABENS", 0, 10);
        ssd1306_draw_string(&ssd, "VOCE CONSEGUIU", 0, 20);
        snprintf(pontuacao, sizeof(pontuacao), "%d PONTOS", contador);
        ssd1306_draw_string(&ssd, pontuacao, 0, 50);
        ssd1306_send_data(&ssd);
        sleep_ms(10000);
    }
}

int main() {
    stdio_init_all();

    gpio_init(BTN_E_PIN);
    gpio_set_dir(BTN_E_PIN, GPIO_IN);
    gpio_pull_up(BTN_E_PIN);

    gpio_init(BTN_D_PIN);
    gpio_set_dir(BTN_D_PIN, GPIO_IN);
    gpio_pull_up(BTN_D_PIN);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX, GPIO_FUNC_UART);
    gpio_set_function(UART_RX, GPIO_FUNC_UART);

    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); 
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); 
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);

    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    while (true) {
        int escolha = 1;
        uint32_t tempo_inicio = to_ms_since_boot(get_absolute_time());

        while (to_ms_since_boot(get_absolute_time()) - tempo_inicio < 5000) {
            if (gpio_get(BTN_E_PIN) == 0) {
                escolha++;
                sleep_ms(200);
            } else if (gpio_get(BTN_D_PIN) == 0) {
                escolha++;
                sleep_ms(200);
            }

            ssd1306_fill(&ssd, false);
            ssd1306_draw_string(&ssd, "INDIQUE A FUNCIONALIDADE", 0, 10);

            if (escolha == 1 || escolha % 2 == 1) {
                ssd1306_draw_string(&ssd, "CONSULTA   jogo", 0, 50);
            } else {
                ssd1306_draw_string(&ssd, "consulta   JOGO", 0, 50);
            }

            ssd1306_send_data(&ssd);
            sleep_ms(100);
        }

        if (escolha == 1 || escolha % 2 == 1) {
            consulta();
        } else {
            game();
        }
    }
}