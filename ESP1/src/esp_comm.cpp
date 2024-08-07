// #include <esp_now.h>
// #include <WiFi.h>
// #include <ws.h>
// #include <oled.h>
// #include <esp_comm.h>
// #include "pinout.h"

// // MAC address of ESP2
// uint8_t esp1Address[] = {0x64, 0xB7, 0x08, 0x9C, 0x61, 0x1C};
// esp_now_peer_info_t esp1Info;

// typedef struct struct_message {
//     bool cooktop; // whether to come ASAP to cooktop or not
//     String station; // which station currently at
//     int randomNum; // random number for now
// } struct_message;

// struct_message myData;
// struct_message incomingData;

// // Function declarations
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
// void OnDataRecv(const uint8_t * mac, const uint8_t *data, int len);

// void espCommSetup() {
//     //oledDisplay("Initializing ESP-NOW");

//     // Set device as a Wi-Fi Station (has already been done in wsSetup())
//     WiFi.mode(WIFI_STA);

//     // Init ESP-NOW
//     if (esp_now_init() != ESP_OK) {
//         // oledDisplay("Error initializing ESP-NOW");
//         return;
//     }

//     // Register for a callback function that will be called when data is sent
//     esp_now_register_send_cb(OnDataSent);

//     // Register esp2
//     memcpy(esp1Info.peer_addr, esp1Address, 6);
//     esp1Info.channel = 0;
//     esp1Info.encrypt = false;

//     // Add peer
//     // if (esp_now_add_peer(&esp1Info) != ESP_OK) {
//     //     oledDisplay("Failed to add ESP2");
//     //     return;
//     //}

//     // Register for a callback function that will be called when data is received
//     esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

//     // oledDisplay("ESP-NOW initialized!");
// }

// // Callback when data is sent
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   oledDisplay("ESP-NOW Packet Send Status:");
//   oledAppendDisplay(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success :)" : "Delivery Fail :(");
// }

// // Callback when data is received
// void OnDataRecv(const uint8_t * mac, const uint8_t *data, int len) {
//   memcpy(&incomingData, data, sizeof(incomingData));
// //   oledDisplay("ESP-NOW Bytes received:" + len);
// //   oledAppendDisplay("Cooktop: " + String(incomingData.cooktop));
// //   oledAppendDisplay("Station: " + String(incomingData.station));
// //   oledAppendDisplay("Random Number: " + String(incomingData.randomNum));
// }

// void espCommSend(bool cooktop, String station, int randomNum) {
//     myData.cooktop = cooktop;
//     myData.station = station;
//     myData.randomNum = randomNum;

//     esp_err_t result = esp_now_send(esp1Address, (uint8_t *) &myData, sizeof(myData));
//     if (result == ESP_OK) {
//         // oledDisplay("Sent with success");
//     } else {
//         // oledDisplay("Error sending the data");
//     }
// }