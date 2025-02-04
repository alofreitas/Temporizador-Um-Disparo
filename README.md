# README - Controle de LEDs com Botão na Raspberry Pi Pico W

## Descrição
Este programa implementa um controle sequencial de LEDs utilizando a placa Raspberry Pi Pico. Os LEDs são acionados quando um botão é pressionado, e depois se apagam em uma sequência controlada por temporizadores.

## Requisitos
- Placa **Raspberry Pi Pico**
- LEDs de cores **azul, vermelha e verde**
- **Resistores** apropriados (330Ω recomendados)
- **Botão de pressão**
- **Cabos jumper** e protoboard
- **Ambiente de desenvolvimento para Raspberry Pi Pico**, como:
  - **SDK do Raspberry Pi Pico** instalado
  - **Compilador GCC ARM**
  - **CMake**
  - **Ferramenta de upload (picotool ou UF2 Bootloader)**

## Esquema de Ligação
Os LEDs e o botão devem ser conectados aos seguintes pinos da Raspberry Pi Pico:

| Componente   | Pino GPIO |
|-------------|----------|
| LED Azul    | 11       |
| LED Vermelho| 12       |
| LED Verde   | 13       |
| Botão      | 5        |

Cada LED deve estar conectado em série com um resistor de **330Ω** para limitar a corrente.

## Compilação e Upload
1. Clone ou baixe este repositório para sua máquina:
   ```sh
   git clone https://github.com/alofreitas/Temporizador-Um-Disparo.git
   cd Temporizador-Um-Disparo
   ```
2. Compile o código usando **CMake**:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Conecte a Raspberry Pi Pico ao computador no **modo bootloader** (pressionando o botão **BOOTSEL** ao conectar o cabo USB).
4. Copie o arquivo `.uf2` gerado para a unidade montada pelo Pico.

## Execução
Após o upload, o código será executado automaticamente. O funcionamento do sistema é o seguinte:
- Quando o botão é pressionado, os LEDs **azul, vermelho e verde** são acesos simultaneamente.
- Os LEDs se apagam em sequência, com um intervalo de **3 segundos** entre cada desligamento:
  1. O LED azul se apaga.
  2. O LED vermelho se apaga.
  3. O LED verde se apaga e a sequência pode ser reiniciada.

## Monitoramento Serial
Para visualizar as mensagens enviadas pelo programa, utilize um monitor serial como **Minicom, PuTTY ou screen**:
```sh
screen /dev/ttyUSB0 115200
```
Substitua `/dev/ttyUSB0` pelo dispositivo correspondente ao seu Raspberry Pi Pico.

## Autor
Ana Luiza Oliveira de Freitas
