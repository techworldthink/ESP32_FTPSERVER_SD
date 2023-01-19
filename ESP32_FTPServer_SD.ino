#include <WiFi.h>
#include "ESP32FtpServer.h"

const char* ssid = "Black_hat:)";
const char* password = "1010101010";

FtpServer ftpSrv;

// SD card options
#define SD_CS 5

void setup(void) {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  pinMode(19, INPUT_PULLUP);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //FTP Setup, ensure SD is started before ftp;
  if (SD.begin(SD_CS)) {
    Serial.println("SD opened!");
    //username, password for ftp.  set ports in ESP32FtpServer.h  (default 21, 50009 for PASV)
    ftpSrv.begin("esp32", "esp32");
  } else {
    Serial.println("SD open failed!");
  }
}

void loop(void) {
  ftpSrv.handleFTP();
}
