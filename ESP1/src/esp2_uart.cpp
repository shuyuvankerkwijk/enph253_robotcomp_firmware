#include "Arduino.h"
#include <HardwareSerial.h>
#include "pinout.h"

void esp2UartSetup() {
    Serial2.begin(9600, SERIAL_8N1, UART_ESP2_RX_PIN, UART_ESP2_TX_PIN);
}

void esp2UartSend(String message) {
    Serial2.println(message);
}

String esp2UartReceive() {
    if(Serial2.available()){
        String message= Serial2.readStringUntil('\n');
        return String(message);
    } else {
        return "";
    }
}