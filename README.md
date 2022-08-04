<p align="center">
  <img src="logo.png" alt="Project logo">
</p>

<h3 align="center">Air Quality Measurement - Hardware</h3>

<div align="center">

[![Status](https://img.shields.io/badge/version-1.0-blue)]()
[![Status](https://img.shields.io/badge/status-active-green)]()
[![GitHub Issues](https://img.shields.io/github/issues/JeanPoffo/aqm-hardware.svg)](https://github.com/JeanPoffo/aqm-hardware/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/JeanPoffo/aqm-hardware.svg)](https://github.com/JeanPoffo/aqm-hardware/pulls)

</div>

---

<p align="center">    
  🌬️ NodeMCU software to collect and send air quality data.
</p>

## 📝 Table of Contents

- [About](#about)
- [How it works](#working)
- [Usage](#usage)
- [Getting Started](#getting_started)
- [Built Using](#built_using)
- [Authors](#authors)

## 🧐 About <a name = "about"></a>

A project to collect and distribute air quality data.

## 💭 How it works <a name = "working"></a>

A program for NodeMCU to collect and send air quality data.

## 🎈 Usage <a name = "usage"></a>

- Open the project on Arduino IDE.

- Replace the follow variable values:

```
const char *ssid = "wifi-ssid"
const char *password = "wifi-password";
const char *stationId = "station-id";
const char *host = "aqm-host";
const char *hostUrlPost = "aqm-host-dataraw-route";
```

- Download the sketch to NodeMCU

## 🏁 Getting Started <a name = "getting_started"></a>

Just clone and follow the steps above.

### Prerequisites

```
Library ESP8266WiFi
Library ESP8266HTTPClient
Library Adafruit_ADS1X15
Library DHT
```

## ⛏️ Built Using <a name = "built_using"></a>

For this project, basically used:

- [Arduino IDE](https://www.arduino.cc/en/software)

And many C++ libraries.

## ✍️ Authors <a name = "authors"></a>

- [@JeanPoffo](https://github.com/JeanPoffo)
