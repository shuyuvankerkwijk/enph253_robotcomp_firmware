#ifndef ESP_COMM_H
#define ESP_COMM_H

#include <Arduino.h>

// pins

// variables

// functions
void espCommSetup();
void espCommSend(bool cooktop, String station, int randomNum);

#endif // ESP_COMM_H