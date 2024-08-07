#include <esp1_uart.h>
#include <HardwareSerial.h>
#include "pinout.h"

void esp1UartSetup() {
    Serial1.begin(9600, SERIAL_8N1, UART_ESP1_RX_PIN, UART_ESP1_TX_PIN);
}

void esp1UartSend(String message) {
    Serial1.println(message);
}

String esp1UartReceive() {
    if(Serial1.available()){
        char message[50];
        int length = Serial1.readBytesUntil('\n', message, sizeof(message) - 1);
        message[length] = '\0';
        return String(message);
    } else {
        return "";
    }
}

// Can use 'SerialEvent' and check if there is a new message (interrupt)
// void serialEvent() {}

// ws.textAll("BP received: " + String((char*)message));
