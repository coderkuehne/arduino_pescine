#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <FS.h>


const char* ssid = "42Wolfsburg_FabLab";
const char* password = "0nly5ky15theL1m17";

ESP8266WebServer server(80);

  void handleRoot() {
  File file = SPIFFS.open("/test1.html", "r");
  if (file) {
    server.streamFile(file, "text/html");
    file.close();
  } else {
    server.send(404, "text/plain", "File not found");
  }
}

void handleButton() {
  String switchId = server.arg("switchId");
  String state = server.arg("state");

  // Handle the button state data here
  Serial.print("Switch ID: ");
  Serial.println(switchId);
  Serial.print("State: ");
  Serial.println(state);
  // Send a response back to the client
  server.send(200, "text/plain", "Data received");
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP to connect: " + WiFi.localIP().toString());
  server.on("/", handleRoot);
  server.on("/switch", HTTP_GET, handleButton); // Handle the button data

  server.begin();
}

