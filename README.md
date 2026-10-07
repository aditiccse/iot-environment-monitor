# 🌡️ IoT Environment Monitor with Threshold Alerts

An IoT-based environmental monitoring project using an ESP32, DHT22 temperature/humidity sensor, PIR motion sensor, LED alert, and ThingSpeak cloud dashboard.

The project can be simulated completely in Wokwi, so physical hardware is not required.

---

## 🎯 Project Objective

The objective is to build an IoT system that:

- Collects temperature and humidity data
- Detects motion
- Sends sensor readings to a cloud dashboard
- Checks sensor values against thresholds
- Activates an alert when a threshold is exceeded
- Demonstrates basic IoT security risks

---

## 🏗️ System Architecture

```text
DHT22 Sensor
     │
     ├── Temperature
     └── Humidity
            │
            ▼
        ┌─────────┐
PIR ───►│  ESP32  │
Sensor  └────┬────┘
             │
             │ Wi-Fi
             ▼
       ┌────────────┐
       │ ThingSpeak │
       │ Dashboard  │
       └────────────┘
             
             │
             ▼
       Threshold Check
             │
             ▼
       Warning LED
```

Then continue with:

```markdown
---

## 🧰 Components

| Component | Purpose |
|---|---|
| ESP32 | Main IoT controller |
| DHT22 | Temperature and humidity sensor |
| PIR sensor | Motion detection |
| LED | Local warning indicator |
| 220Ω resistor | LED current limiting |
| Wokwi | Hardware simulation |
| ThingSpeak | Cloud dashboard |

---

## 🔌 Circuit Connections

### DHT22

| DHT22 Pin | ESP32 |
|---|---|
| VCC | 3.3V |
| DATA | GPIO 15 |
| GND | GND |

### PIR Sensor

| PIR Pin | ESP32 |
|---|---|
| VCC | 5V |
| OUT | GPIO 13 |
| GND | GND |

### LED

```text
ESP32 GPIO 2
     │
     ▼
  220Ω resistor
     │
     ▼
    LED
     │
     ▼
    GND
```

---

## 🚨 Alert Conditions

The project uses these default thresholds:

```text
Temperature > 35°C
Humidity > 80%
Motion detected
```

If any of these conditions occurs:

1. The warning LED turns ON.
2. An alert is printed in the Serial Monitor.
3. Alert status is sent to ThingSpeak as `1`.

Normal status is sent as `0`.

---

## ☁️ ThingSpeak Dashboard

Create a ThingSpeak channel with four fields:

| Field | Name |
|---|---|
| Field 1 | Temperature |
| Field 2 | Humidity |
| Field 3 | Motion |
| Field 4 | Alert Status |

The ESP32 sends sensor readings to ThingSpeak every 20 seconds.

---

## 🔑 ThingSpeak API Key

The code contains this placeholder:

```cpp
const char* THINGSPEAK_API_KEY = "YOUR_WRITE_API_KEY";
```

Create your own ThingSpeak channel and obtain the **Write API Key**.

For security, do not publish your real Write API Key in this GitHub repository.

The real key should only be entered into your private Wokwi copy when testing.

---

## 🖥️ Wokwi Simulation

This project can be simulated using Wokwi.

The simulated Wi-Fi settings are:

```cpp
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
```

### Testing

Start the Wokwi simulation.

The Serial Monitor should show sensor readings such as:

```text
Temperature: 24.00 C
Humidity: 40.00 %
Motion: No motion
Status: NORMAL
```

To test the alert, increase the simulated temperature above 35°C.

For example:

```text
Temperature: 40.00 C
```

The system should display:

```text
***** ALERT *****
High temperature detected!
```

The LED should also turn ON.

---

## 🔐 IoT Security Risks

### 1. Unencrypted Communication

Unencrypted HTTP communication can allow data to be intercepted.

Production IoT systems should use HTTPS or MQTT over TLS where possible.

### 2. Exposed API Keys

Cloud API keys should never be uploaded to a public GitHub repository.

### 3. Default Credentials

Default passwords can allow unauthorized users to access IoT devices.

### 4. Open Ports

Unnecessary open ports increase the attack surface of an IoT device.

### 5. Wi-Fi Credentials

Real Wi-Fi passwords should never be published in public source code.

---

## 📁 Project Structure

```text
iot-environment-monitor/
│
├── README.md
├── sketch.ino
├── diagram.json
├── libraries.txt
└── .gitignore
```

---

## 🎓 Learning Outcomes

This project demonstrates:

- IoT architecture
- ESP32 programming
- Sensor interfacing
- Wi-Fi communication
- Cloud data transmission
- Threshold-based alerts
- Dashboard visualization
- Basic IoT security

---

## 🚀 Future Improvements

Possible improvements include:

- MQ-2 gas sensor
- Buzzer alarm
- Email notifications
- Mobile notifications
- MQTT communication
- HTTPS/TLS security
- OLED display
- Automatic fan control
- Secure credential storage

---

## ⚠️ Disclaimer

This project is intended for educational purposes. The simulated sensors and simple threshold rules should not be used for real-world fire, gas, security, or other safety-critical monitoring.
