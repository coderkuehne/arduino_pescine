#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

const char* ssid = "42Wolfsburg_FabLab";
const char* password = "0nly5ky15theL1m17";

ESP8266WebServer server(80);

void handleRoot() {
    File file = SPIFFS.open("index.html", "r+");
    if (file) {
        String html = "";
        while (file.available()) {
            String line = file.readStringUntil('\n');
            html += line;
        }
        file.close();
        server.send(200, "text/html", html);
    } else {
        server.send(404, "text/plain", "File not found");
    }
}

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println("IP to connect: " + WiFi.localIP().toString());
    
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }
    
    server.on("/", handleRoot);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}
