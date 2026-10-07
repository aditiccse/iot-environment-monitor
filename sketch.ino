/*
 * IoT Environment Monitor with Threshold Alerts
 * ESP32 + DHT22 + PIR + LED + Blynk
 */

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL30bQQP7yq"
#define BLYNK_TEMPLATE_NAME "IoT Environment Monitor"
#define BLYNK_AUTH_TOKEN "PASTE_YOUR_BLYNK_AUTH_TOKEN_HERE"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h>

// Pins
#define DHT_PIN 15
#define PIR_PIN 13
#define LED_PIN 2

// Alert thresholds
const float TEMP_THRESHOLD = 35.0;
const float HUMIDITY_THRESHOLD = 80.0;

// Wokwi Wi-Fi
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

DHTesp dhtSensor;
BlynkTimer timer;

void sendSensorData()
{
  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  float temperature = data.temperature;
  float humidity = data.humidity;

  int motion = digitalRead(PIR_PIN);

  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("Failed to read DHT22 sensor.");
    return;
  }

  bool temperatureAlert = temperature > TEMP_THRESHOLD;
  bool humidityAlert = humidity > HUMIDITY_THRESHOLD;
  bool motionAlert = motion == HIGH;

  bool alert = temperatureAlert ||
               humidityAlert ||
               motionAlert;

  digitalWrite(LED_PIN, alert ? HIGH : LOW);

  Serial.println();
  Serial.println("-------------------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity, 2);
  Serial.println(" %");

  Serial.print("Motion: ");

  if (motion == HIGH)
  {
    Serial.println("DETECTED");
  }
  else
  {
    Serial.println("No motion");
  }

  if (alert)
  {
    Serial.println();
    Serial.println("***** ALERT *****");

    if (temperatureAlert)
    {
      Serial.println("High temperature detected!");
    }

    if (humidityAlert)
    {
      Serial.println("High humidity detected!");
    }

    if (motionAlert)
    {
      Serial.println("Motion detected!");
    }
  }
  else
  {
    Serial.println("Status: NORMAL");
  }

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, motion);
  Blynk.virtualWrite(V3, alert ? 1 : 0);

  Serial.println("Data sent to Blynk.");
}

void setup()
{
  Serial.begin(115200);

  Serial.println();
  Serial.println("===============================");
  Serial.println(" IoT Environment Monitor");
  Serial.println("===============================");

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  Serial.println("Connecting to Blynk...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Blynk connected!");

  timer.setInterval(20000L, sendSensorData);

  sendSensorData();
}

void loop()
{
  Blynk.run();
  timer.run();
}
