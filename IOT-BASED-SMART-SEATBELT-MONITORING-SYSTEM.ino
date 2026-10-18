#include "HX711.h"
#include <WiFi.h>
#include <WebServer.h>

// HX711 pins
#define DT 4
#define SCK 5

// Other components
#define PROX_SENSOR 18
#define BUZZER 19

HX711 scale;

// WiFi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

// Calibration factor (adjust later)
float calibration_factor = -7050;  // you will tune this

float weight = 0;

void handleRoot() {
  String seatStatus;
  String beltStatus;
  String buzzerStatus;

  weight = scale.get_units(5);

  if (weight > 5) {
    seatStatus = "OCCUPIED";

    if (digitalRead(PROX_SENSOR) == HIGH) {
      beltStatus = "NOT FIXED";
      digitalWrite(BUZZER, HIGH);
      buzzerStatus = "ON";
    } else {
      beltStatus = "FIXED";
      digitalWrite(BUZZER, LOW);
      buzzerStatus = "OFF";
    }

  } else {
    seatStatus = "EMPTY";
    beltStatus = "NO NEED";
    digitalWrite(BUZZER, LOW);
    buzzerStatus = "OFF";
  }

  String page = "<html><head><title>Seatbelt Monitor</title></head><body>";
  page += "<h1>SMART SEATBELT SYSTEM</h1>";
  page += "<h2>Seat: " + seatStatus + "</h2>";
  page += "<h2>Belt: " + beltStatus + "</h2>";
  page += "<h2>Buzzer: " + buzzerStatus + "</h2>";
  page += "<h2>Weight: " + String(weight) + "</h2>";
  page += "</body></html>";

  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting System...");

  pinMode(PROX_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);

  // HX711 setup
  scale.begin(DT, SCK);
  scale.set_scale(calibration_factor);
  scale.tare();  // reset weight

  Serial.println("HX711 Ready");

  // WiFi connect
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start server
  server.on("/", handleRoot);
  server.begin();

  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();

  // Debug prints
  weight = scale.get_units(3);
  Serial.print("Weight: ");
  Serial.println(weight);

  Serial.print("Proximity: ");
  Serial.println(digitalRead(PROX_SENSOR));

  delay(1000);
}
