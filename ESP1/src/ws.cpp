#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <AsyncTCP.h>

#include "main.h"
#include "ws.h"
#include "bluepill_uart.h"
#include "esp2_uart.h"
#include "crane.h"
#include "pinout.h"
#include "vacuum.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
const char* ssid = "";
const char* password = "";
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xA5, 0xB6, 0xC7};

// function declaration
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

void wsSetup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "WebSocket server running.");
    });
    server.begin();

    // Serial.println("Servers started!"); 
    // Serial.println("IP: " + WiFi.localIP().toString());
    // Serial.println("ESP1 MAC: " + WiFi.macAddress());
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        ws.textAll("WebSocket client connected");
    } else if (type == WS_EVT_DISCONNECT) {
    } else if (type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo*)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
            data[len] = 0; // Null-terminate the data
            ws.textAll("WS received: " + String((char*)data));

            // PARSE
            String msg = String((char*)data);

            if(msg == "stop") {
                run = false;

            } else if(msg== "start") {
                run = true;

            } else if (msg.substring(0, 2).equalsIgnoreCase("RF")) {
                String distStr = msg.substring(2);
                String numericPart = "";
                for (int i = 0; i < distStr.length(); i++) {
                    if (isDigit(distStr.charAt(i))) {
                        numericPart += distStr.charAt(i);
                    }
                }
                int dist = numericPart.toInt();
                craneSetDirectionRB(1);
                moveR = -1*dist;
                ws.textAll("Set MoveR to " + String(moveR));

            } else if (msg.substring(0, 2).equalsIgnoreCase("RB")) {
                String distStr = msg.substring(2);
                String numericPart = "";
                for (int i = 0; i < distStr.length(); i++) {
                    if (isDigit(distStr.charAt(i))) {
                        numericPart += distStr.charAt(i);
                    }
                }
                int dist = numericPart.toInt();
                craneSetDirectionRB(-1);
                moveR = -1*dist;
                ws.textAll("Set MoveR to " + String(moveR));

            } else if (msg.substring(0, 2).equalsIgnoreCase("YD")) {
                craneSetDirectionYB(1);
                moveY = 1;
                ws.textAll("Set MoveY to " + String(moveY));

            } else if (msg.substring(0, 2).equalsIgnoreCase("YU")) {
                craneSetDirectionYB(-1);
                moveY = -1;
                ws.textAll("Set MoveY to " + String(moveY));

            } else if (msg.substring(0, 3).equalsIgnoreCase("ZCW")) {
                String distStr = msg.substring(3);
                String numericPart = "";
                for (int i = 0; i < distStr.length(); i++) {
                    if (isDigit(distStr.charAt(i))) {
                        numericPart += distStr.charAt(i);
                    }
                }
                int dist = numericPart.toInt();
                craneSetDirectionZB(1);
                moveZ = dist;
                ws.textAll("Set MoveZ to " + String(moveZ));

            } else if (msg.substring(0, 4).equalsIgnoreCase("ZCCW")) {
                String distStr = msg.substring(4);
                String numericPart = "";
                for (int i = 0; i < distStr.length(); i++) {
                    if (isDigit(distStr.charAt(i))) {
                        numericPart += distStr.charAt(i);
                    }
                }
                int dist = numericPart.toInt();
                craneSetDirectionZB(-1);
                moveZ = -1*dist;
                ws.textAll("Set MoveZ to " + String(moveZ));

            } else if (msg.substring(0, 3).equalsIgnoreCase("VON")) {
                String powerStr = msg.substring(3);
                String numericPart = "";
                for (int i = 0; i < powerStr.length(); i++) {
                    if (isDigit(powerStr.charAt(i))) {
                        numericPart += powerStr.charAt(i);
                    }
                }
                int power = numericPart.toInt();
                vacuumOnB(power);
                wsSend("Vacuum on at power " + String(power));

            } else if (msg.substring(0, 4).equalsIgnoreCase("VOFF")) {
                vacuumOffB();
                wsSend("Vacuum off");

            } else if (msg.substring(0, 4).equalsIgnoreCase("CUPD")) {
                esp2UartSend("CupD");
                wsSend("Sent to ESP2: CupD");

            } else {
                bluepillUartSend(String((char*)data));
                wsSend("Sent to BP: " + String((char*)data));
            }
        }
    }
}


void wsSend(String message) {
    ws.textAll(message);
}