#include <bluepill_uart.h>
#include <HardwareSerial.h>
#include "pinout.h"

void bluepillUartSetup() {
    Serial1.begin(9600, SERIAL_8N1, UART_BLUEPILL_RX_PIN, UART_BLUEPILL_TX_PIN);
}

void bluepillUartSend(String message) {
    Serial1.println(message);
}

String bluepillUartReceive() {
    if(Serial1.available()){
        String message= Serial1.readStringUntil('\n');
        return String(message);
    } else {
        return "";
    }
}
