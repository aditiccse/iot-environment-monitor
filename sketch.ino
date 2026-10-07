/*
 * IoT Environment Monitor with Threshold Alerts
 * ESP32 + DHT22 + PIR + LED + ThingSpeak
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHTesp.h>

// -------------------------------
// Pin configuration
// -------------------------------

#define DHT_PIN 15
#define PIR_PIN 13
#define LED_PIN 2

// -------------------------------
// Alert thresholds
// -------------------------------

const float TEMP_THRESHOLD = 35.0;
const float HUMIDITY_THRESHOLD = 80.0;

// -------------------------------
// Wokwi Wi-Fi
// -------------------------------

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

// -------------------------------
// ThingSpeak
// -------------------------------

// Keep this as a placeholder on GitHub.
// Add your real key only in your private Wokwi copy.
const char* THINGSPEAK_API_KEY = "YOUR_WRITE_API_KEY";

const char* THINGSPEAK_SERVER =
  "http://api.thingspeak.com/update";

// -------------------------------
// DHT sensor
// -------------------------------

DHTesp dhtSensor;

// -------------------------------
// Connect to Wi-Fi
// -------------------------------

void connectWiFi() {

  Serial.print("Connecting to WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {

    delay(500);
    Serial.print(".");

    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println();
    Serial.println("WiFi connected!");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

  } else {

    Serial.println();
    Serial.println("WiFi connection failed.");
  }
}

// -------------------------------
// Send data to ThingSpeak
// -------------------------------

void sendToThingSpeak(
  float temperature,
  float humidity,
  int motion,
  int alertStatus
) {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi disconnected.");

    connectWiFi();

    return;
  }

  HTTPClient http;

  String url = String(THINGSPEAK_SERVER);

  url += "?api_key=";
  url += THINGSPEAK_API_KEY;

  url += "&field1=";
  url += String(temperature, 2);

  url += "&field2=";
  url += String(humidity, 2);

  url += "&field3=";
  url += String(motion);

  url += "&field4=";
  url += String(alertStatus);

  Serial.println("Sending data to ThingSpeak...");

  http.begin(url);

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {

    Serial.print("ThingSpeak response: ");
    Serial.println(httpResponseCode);

  } else {

    Serial.print("HTTP error: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

// -------------------------------
// Setup
// -------------------------------

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("===============================");
  Serial.println(" IoT Environment Monitor");
  Serial.println("===============================");

  // Start DHT22
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // PIR sensor
  pinMode(PIR_PIN, INPUT);

  // Warning LED
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  // Connect to Wi-Fi
  connectWiFi();
}

// -------------------------------
// Main loop
// -------------------------------

void loop() {

  // Read DHT22
  TempAndHumidity data =
    dhtSensor.getTempAndHumidity();

  float temperature = data.temperature;
  float humidity = data.humidity;

  // Read PIR
  int motion = digitalRead(PIR_PIN);

  // Check sensor reading
  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("Failed to read DHT22 sensor.");

    delay(2000);

    return;
  }

  // -----------------------------
  // Display sensor readings
  // -----------------------------

  Serial.println();
  Serial.println("-------------------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Motion: ");

  if (motion == HIGH) {

    Serial.println("DETECTED");

  } else {

    Serial.println("No motion");
  }

  // -----------------------------
  // Check alert conditions
  // -----------------------------

  bool temperatureAlert =
    temperature > TEMP_THRESHOLD;

  bool humidityAlert =
    humidity > HUMIDITY_THRESHOLD;

  bool motionAlert =
    motion == HIGH;

  bool alert =
    temperatureAlert ||
    humidityAlert ||
    motionAlert;

  // -----------------------------
  // Alert
  // -----------------------------

  if (alert) {

    digitalWrite(LED_PIN, HIGH);

    Serial.println();
    Serial.println("***** ALERT *****");

    if (temperatureAlert) {

      Serial.println(
        "High temperature detected!"
      );
    }

    if (humidityAlert) {

      Serial.println(
        "High humidity detected!"
      );
    }

    if (motionAlert) {

      Serial.println(
        "Motion detected!"
      );
    }

  } else {

    digitalWrite(LED_PIN, LOW);

    Serial.println("Status: NORMAL");
  }

  // -----------------------------
  // Send to ThingSpeak
  // -----------------------------

  sendToThingSpeak(
    temperature,
    humidity,
    motion,
    alert ? 1 : 0
  );

  // Wait 20 seconds before next upload
  delay(20000);
}
