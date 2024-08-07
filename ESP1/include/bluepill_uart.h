#ifndef BLUEPILL_UART_H
#define BLUEPILL_UART_H

#include <Arduino.h>

// functions
void bluepillUartSetup();
void bluepillUartSend(String message);
String bluepillUartReceive();

#endif // BLUEPILL_UART_H
