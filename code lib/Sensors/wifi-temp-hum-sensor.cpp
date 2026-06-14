/* 
This is a simple temperature and humidity sensor using an ESP32, DHT11 sensor, and an OLED display.

----------
OLED pins:
- SDA: 21
- SCL: 22

DHT11 pin:
- Data: 18

with respective 3v3 and GND connections.
----------

On boot, the sensor will initialize the OLED display, connect to WiFi, and start the webpage server.
Access the web server at the IP address displayed on the OLED screen.

http://[ip-address].com


in platformio.ini: 

lib_deps = adafruit/Adafruit SSD1306@^2.5.17

*/


#include <Arduino.h>

#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht_nonblocking.h>



// wifi settings - change these to your network
#define WIFI_SSID "cool-ssid"
#define WIFI_PASSWORD "password"
#define WIFI_CHANNEL 6


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// sensor pin 
#define DHT_SENSOR_PIN 18
#define DHT_SENSOR_TYPE DHT_TYPE_11

DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);


WebServer server(80);

// global variables
float temperature = 0.0;
float humidity = 0.0;

//sensor fucntions
bool measure_environment(float *t, float *h) {
  static unsigned long last = 0;

  if (millis() - last > 3000) {
    if (dht_sensor.measure(t, h)) {
      last = millis();
      return true;
    }
  }
  return false;
}

// Invert the display every 30 seconds to help with burn-in
unsigned long lastInvert = 0;
const unsigned long invertInterval = 5000; // milliseconds
bool inverted = false;


void setup() {
  Serial.begin(115200);
// oled pins
  Wire.begin(21, 22);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();

  // WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting");
  display.setCursor(0, 10);
  display.println("Connecting to WiFi...");
  display.display();

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");

    if (millis() - start > 15000) {
      Serial.println("\nWiFi failed");
      Serial.println(WiFi.status());
      return;
    }
  }
  display.setCursor(0, 20);
  display.println("WiFi connected!");
  display.display();

  delay(1000);  

  display.setCursor(0, 30);
  display.println("Starting web server...");
  display.display();

  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());
  display.setCursor(0, 40);
  display.println("Device IP: " + WiFi.localIP().toString());
  display.display();

  // Web route
  server.on("/", []() {
  String page =
  "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>"
  "<style>"
  "body{font-family:Arial,sans-serif;background:linear-gradient(135deg,#667eea,#764ba2);"
  "display:flex;justify-content:center;align-items:center;height:100vh;margin:0;color:#fff}"
  ".card{background:rgba(255,255,255,0.15);backdrop-filter:blur(10px);border-radius:20px;"
  "padding:40px;text-align:center;box-shadow:0 8px 32px rgba(0,0,0,0.3)}"
  "h1{margin-top:0;font-size:1.8em}"
  ".val{font-size:3em;font-weight:bold;margin:10px 0}"
  ".label{font-size:1em;opacity:0.8}"
  " .row{margin:20px 0}"
  "</style></head><body>"
  "<div class='card'>"
  "<h1>ESP32 Sensor</h1>"
  "<div class='row'><div class='val'>" + String(temperature) + " &deg;F</div><div class='label'>Temperature</div></div>"
  "<div class='row'><div class='val'>" + String(humidity) + " %</div><div class='label'>Humidity</div></div>"
  "</div>"
  "<script>setTimeout(()=>location.reload(),5000);</script>"
  "</body></html>";
  server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  float t, h;

  if (measure_environment(&t, &h)) {
    temperature = (t * 9.0 / 5.0) + 32.0;
    humidity = h;

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" F, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

  
    // Temperature
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(temperature, 1);
    display.print("F");

    // Humidity
    display.setCursor(0, 24);
    display.print(humidity, 1);
    display.print("%");

    // IP
    display.setTextSize(1);
    display.setCursor(0, 54);
    display.print(WiFi.localIP());

    display.display();
   
    // invert display
    if (millis() - lastInvert >= invertInterval) {
        inverted = !inverted;
        display.invertDisplay(inverted);
        lastInvert = millis();
        }

  }
}