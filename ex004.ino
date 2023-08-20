
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>
#include <FS.h>

#define NUM_LEDS 64
#define DATA_PIN 0
CRGB leds[NUM_LEDS];
const char* ssid = "42Wolfsburg_FabLab";
const char* password = "0nly5ky15theL1m17";

ESP8266WebServer server(80);

  void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (file) {
    server.streamFile(file, "text/html");
    file.close();
  } else {
    server.send(404, "text/plain", "File not found");
  }
}


void handleButton() {
  int i = 0;
  const char *switchIdCharPtr;
  String switchId = server.arg("id");
  String pattern =server.arg("pattern_state");
  switchIdCharPtr = switchId.c_str();
  String state = server.arg("state");
  // Handle the button state data here
  Serial.print("Switch ID: ");
  Serial.println(switchId);
  Serial.print("State: ");
  Serial.println(state);
  Serial.println("Pattern_state ");
  Serial.println(pattern);

   //Update LEDs based on the switch state
  if(pattern == "on")
  {
       
       while(i < 63){
        if (i < 8)
          leds[i] = CRGB::White;
        if (i >= 8 && i < 16)
          leds[i] = CRGB::Red;
        if (i >= 16 && i < 24)
          leds[i] = CRGB::Blue;
        if (i >= 24 && i < 32)
          leds[i] = CRGB::Green;
        if (i >= 32 && i < 40)
          leds[i] = CRGB::Yellow;
        if (i >= 40 && i < 48)
          leds[i] = CRGB::Purple;
        if (i >= 48 && i < 56)
          leds[i] = CRGB::Brown;
        if (i >= 56 && i < 64)
          leds[i] = CRGB::Cyan;
        pattern =server.arg("pattern_state");
        i++;
        delay(25);
        FastLED.show();
       }
       while(i >= 0){
        leds[i] = CRGB::White;
        pattern =server.arg("pattern_state");
        i--;
        delay(25);
        FastLED.show();
       }
  }
    else if (pattern == "off"){
      int j = 0;
      while (j < 64){
        leds[j++] = CRGB::Black;
        FastLED.show();
      }
    }
   else if (state == "true") {
       leds[atoi(switchIdCharPtr)] = CRGB::White;
    } 
    else if (state == "false"){
      leds[atoi(switchIdCharPtr)] = CRGB::Black;
    }
  // Send a response back to the client
  server.send(200, "text/plain", "Data received");
  FastLED.show(); // Update the LED display
}


void setup() {
  pinMode(DATA_PIN, OUTPUT);
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
  FastLED.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
  FastLED.setBrightness(50);
}

void  loop()
{
  server.handleClient();
}
