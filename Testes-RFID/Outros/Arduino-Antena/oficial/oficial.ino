#include <SoftwareSerial.h>

uint8_t rx_pin = 6;
uint8_t tx_pin = 7;

SoftwareSerial antena(rx_pin, tx_pin);

void setup() {
    Serial.begin(9600);
    antena.begin(9600);
}

constexpr size_t header_size = 6;

constexpr size_t soi_i = 0;
constexpr size_t address_i = 1;
constexpr size_t cid1_i = 3;
constexpr size_t cid2_i = 4;
constexpr size_t length_i = 5;

bool serial_error = false;

void loop() {
    if (!antena.available()) {
        return;
    }

    delay(100);

    // read header
    uint8_t header[header_size];

    for (size_t i = 0; i < header_size; i++) {
        header[i] = readAntena();
    }

    // read info
    String info;
    info.reserve(header[length_i]);

    for (size_t i = 0; i < header[length_i]; i++) {
        info += (char)readAntena();
    }

    // read checksum
    uint8_t checksum = readAntena();

    // check serial error
    if (serial_error) {
        serial_error = false;
        Serial.print("Erro no serial...");

        while (antena.read() != -1) {}
        Serial.println("Bytes descartados");

        return;
    }

    // check checksum
    uint8_t sum = 0;
    for (size_t i = 0; i < header_size; i++) {
        sum += header[i];
    }
    for (size_t i = 0; i < info.length(); i++) {
        sum += info[i];
    }

    sum = ~sum + 1;

    if (sum != checksum) {
        Serial.println("Erro no checksum");
        return;
    }

    // check soi
    if (header[soi_i] != 0xcc && header[soi_i] != 0x7c) {
        Serial.println("SOI invalido");
        return;
    }

    // print info
    const char* card1 = "\x01\xe2\x00\x00\x1c\x51\x04\x02\x11\x07\x10\xc0\x25";
    const char* card2 = "\x01\xe2\x00\x00\x1c\x51\x03\x02\x50\x09\x30\xe2\xb5";
    const char* card3 = "\x01\xe2\x00\x00\x1c\x51\x03\x02\x50\x17\x90\xe1\x61";
    const char* card4 = "\x01\x00\x00\x9c\xbb\x51\x03\x02\x50\x16\x80\xe1\x89";

    const char* card = info.c_str();

    if (cardCompare(card, card1)) {
        Serial.print("Cartao 1: ");
    } else if (cardCompare(card, card2)) {
        Serial.print("Cartao 2: ");
    } else if (cardCompare(card, card3)) {
        Serial.print("Cartao 3: ");
    } else if (cardCompare(card, card4)) {
        Serial.print("Cartao 4: ");
    } else {
        Serial.print("Cartao desconhecido: ");
    }

    for (size_t i = 0; i < info.length(); i++) {
        Serial.print((uint8_t)info[i], HEX); Serial.print(" ");
    }
    Serial.println("");
}

uint8_t readAntena() {
    int data = antena.read();
    if (data == -1) {
        serial_error = true;
    }
    return data;
}

bool cardCompare(const char* a, const char* b) {
    return memcmp(a, b, 0x0d) == 0;
}
