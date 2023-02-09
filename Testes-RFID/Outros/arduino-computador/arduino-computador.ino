#include <SoftwareSerial.h>

uint8_t rx_pin = 7;
uint8_t tx_pin = 6;

SoftwareSerial computador(rx_pin, tx_pin, false);

void setup() {
    Serial.begin(9600);
    computador.begin(9600);
}

#define MAX_BYTES 100

void loop() {
    if (computador.available()) {
        delay(100);

        int recebido[MAX_BYTES];

        size_t sz = 0;
        while (computador.available()) {
            recebido[sz] = computador.read();
            sz++;
        }

        for (size_t i = 0; i < sz; i++) {
            Serial.print((char)recebido[i]);
            computador.write(recebido[i]+1);
        }
        Serial.println();
    }
}
