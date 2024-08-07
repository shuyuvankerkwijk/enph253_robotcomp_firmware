#ifndef ESP1_UART_H
#define ESP1_UART_H

#include <Arduino.h>

// functions
void esp1UartSetup();
void esp1UartSend(String message);
String esp1UartReceive();

#endif // ESP1_UART_H
