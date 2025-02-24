# Side Sense

**Side Sense** é um sistema embarcado interativo desenvolvido para auxiliar no discernimento entre o lado esquerdo e o lado direito. Ele utiliza um display OLED, botões físicos e um jogo dinâmico para treinar a percepção direcional do usuário.

## Funcionalidades

**Modo Consulta**:  
- O usuário pressiona um botão e o sistema exibe no display OLED se a direção está correta.  

**Modo Jogo**:  
- O sistema exibe aleatoriamente a palavra "ESQUERDA" ou "DIREITA", e o usuário precisa pressionar o botão correspondente.  
- A pontuação é contabilizada e exibida ao final da rodada.

## Componentes utilizados

**Interface OLED**:  
- O display SSD1306 mostra instruções, mensagens e a pontuação final do usuário.  

**Botões Físicos**:  
- Dois botões são utilizados para interação: um para a esquerda e outro para a direita.  

---

## Tecnologias Utilizadas

🔹 **Linguagem**: C  
🔹 **Placa**: Raspberry Pi Pico  
🔹 **Bibliotecas**:  
  - `pico/stdlib.h` → Biblioteca padrão para GPIO e UART  
  - `ssd1306.h` → Controle do display OLED  
  - `stdlib.h`, `stdio.h` → Funções padrões da linguagem C  

---

## Conexões do Hardware

O projeto utiliza os seguintes pinos na Raspberry Pi Pico:

| Componente     | Pino na Pico |
|---------------|-------------|
| Botão Esquerdo | GPIO 5      |
| Botão Direito  | GPIO 6      |
| UART TX       | GPIO 0      |
| UART RX       | GPIO 1      |
| I2C SDA       | GPIO 14     |
| I2C SCL       | GPIO 15     |

---

## Como Executar o Projeto

1. Clone este repositório:
   ```bash
   git clone https://github.com/seuusuario/SideSense.git
2. Configure o ambiente de desenvolvimento para Raspberry Pi Pico.
3. Compile e faça o upload do código para a placa.
4. Conecte os botões e o display conforme os pinos definidos no código.
5. Reinicie a placa e interaja com o sistema.

---

## Organização do Código
main.c → Código principal do projeto.
ssd1306.h e ssd1306.c → Biblioteca para controle do display OLED.
CMakeLists.txt → Arquivo de configuração para compilação no Raspberry Pi Pico.
