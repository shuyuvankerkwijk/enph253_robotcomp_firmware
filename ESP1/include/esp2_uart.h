#ifndef ESP2_UART_H
#define ESP2_UART_H

#include <Arduino.h>

// functions
void esp2UartSetup();
void esp2UartSend(String message);
String esp2UartReceive();

#endif // ESP2_UART_H