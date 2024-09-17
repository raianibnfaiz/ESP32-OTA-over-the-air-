#include <Arduino.h>

#include <WiFi.h>

#include <HTTPClient.h>
#include <ESP32httpUpdate.h>  // Correct library for OTA updates

const char* ssid = "BJIT_ADMIN";       // Your Wi-Fi SSID
const char* password = "Bjit#@dmin";   // Your Wi-Fi Password

const char* firmwareURL = "http://your-server.com/firmware.bin"; // URL of the firmware file

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi.");

  // Start the OTA update process
  t_httpUpdate_return result = ESPhttpUpdate.update(firmwareURL);

  // Check the result of the update process
  switch (result) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("Update failed. Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
      break;
    
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No updates available.");
      break;

    case HTTP_UPDATE_OK:
      Serial.println("Update successful! Restarting...");
      ESP.restart();
      break;
  }
}

void loop() {
  // Nothing to do in the loop
}
