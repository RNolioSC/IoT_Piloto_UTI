#include <SoftwareSerial.h>

uint8_t rx_pin = 7;
uint8_t tx_pin = 6;

SoftwareSerial antena(rx_pin, tx_pin, false);

void setup() {
    Serial.begin(9600);
    antena.begin(9600);

    while (!Serial) {}
    while (!antena) {}
}

void printBytes(uint8_t* bs, size_t sz) {
    for (size_t i = 0; i < sz; i++) {
        Serial.print("/"); Serial.print(bs[i], HEX);
    }
    Serial.println();
}

#define MAX_BYTES 100

void loop() {
    Serial.println("Digite enter para enviar");

    while (true) {
        if (Serial.available() && Serial.read() == '\n') {
            break;
        }
    }

    // Enviar
    {
        uint8_t envio[] = {0x7c, 0xff, 0xff, 0x10, 0x32, 0x00, 0x43};

        size_t sz = 7;

        for (size_t i = 0; i < sz; i++) {
            antena.write(envio[i]);
        }

        Serial.print("Enviado: ");
        printBytes(envio, sz);
    }

    delay(100);

    // Receber
    if (antena.available() == 0) {
        Serial.println("Nao recebi nada");
    } else {
        uint8_t recebido[MAX_BYTES]; 

        size_t sz = 0;
        while (antena.available()) {
            recebido[sz] = antena.read();
            sz++;
        }

        Serial.print("Recebido: ");
        printBytes(recebido, sz);
    }

    Serial.println("");
}