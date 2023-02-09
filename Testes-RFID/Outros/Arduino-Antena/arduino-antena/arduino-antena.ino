#include <SoftwareSerial.h>

uint8_t rx_pin = 6;
uint8_t tx_pin = 7;

SoftwareSerial antena(rx_pin, tx_pin);

void setup() {
    Serial.begin(9600);

    delay(100);

    antena.begin(9600);

    delay(100);
    Serial.println("Iniciou");
    delay(100);
}

void loop() {
    if (antena.available() != 0) {
        delay(100);
        Serial.println("entrou");
        delay(100);

        int valor = antena.read();

        delay(100);

        Serial.println(valor, HEX);
    }
    delay(100);
}
