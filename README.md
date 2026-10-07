# IoT Environment Monitor with Threshold Alerts

An IoT-based environment monitoring system built using ESP32, DHT22, PIR motion sensor, LED, Wokwi simulation, and Blynk Cloud.

The system monitors temperature, humidity, and motion. When a predefined threshold is exceeded or motion is detected, an alert is generated and the red LED turns ON.

## Features

- Real-time temperature monitoring
- Real-time humidity monitoring
- Motion detection using PIR sensor
- Temperature threshold alert
- Humidity threshold alert
- Motion detection alert
- Red LED alert indicator
- Blynk Cloud dashboard
- Serial Monitor output
- Fully tested using Wokwi simulation

## Hardware Components

- ESP32 DevKit C V4
- DHT22 Temperature and Humidity Sensor
- PIR Motion Sensor
- Red LED
- 220Ω Resistor

## Software and Platforms

- Arduino/C++
- Wokwi
- Blynk Cloud
- ESP32 Wi-Fi

## Pin Connections

| Component | ESP32 Pin |
|---|---|
| DHT22 Data | GPIO 15 |
| PIR OUT | GPIO 13 |
| Red LED | GPIO 2 |

## Alert Thresholds

| Parameter | Threshold |
|---|---|
| Temperature | > 35°C |
| Humidity | > 80% |
| Motion | Detected |

When any alert condition occurs, the red LED turns ON and the alert status is sent to Blynk.

## Blynk Dashboard

The system sends the following values to Blynk Cloud:

| Virtual Pin | Data |
|---|---|
| V0 | Temperature |
| V1 | Humidity |
| V2 | Motion |
| V3 | Alert Status |

The Blynk dashboard displays temperature, humidity, motion status, and the current alert status.
## System Workflow

```text
DHT22 + PIR Sensor
        |
        v
      ESP32
        |
        +------> Red LED Alert
        |
        v
   Wi-Fi Connection
        |
        v
   Blynk Cloud
        |
        v
 Blynk Dashboard
```
## Simulation

The project was developed and tested using Wokwi.

Wokwi Project:
https://wokwi.com/projects/477196815209794561

The simulation was tested for:

1. Normal temperature and humidity conditions
2. High temperature alert
3. Motion detection alert
4. LED activation during alert conditions
5. Data transmission to Blynk Cloud

## Project Files

- `sketch.ino` - ESP32 program
- `diagram.json` - Wokwi circuit configuration
- `libraries.txt` - Required libraries
- `.gitignore` - Prevents sensitive and unnecessary files from being committed

## Security

The Blynk Auth Token is not stored in this repository.

Replace the placeholder Auth Token in the code with your own token when running the project.

## Future Improvements

- Add email or push notifications
- Store historical sensor data
- Add more environmental sensors
- Add automatic fan control
- Add a buzzer for local alerts

## Author

**Aditi**

IoT Environment Monitor - College IoT Project
