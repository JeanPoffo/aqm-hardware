/** Include Libraries */
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_ADS1X15.h>
#include <DHT.h>

/** Define Pin Variables */
#define DHTPIN D3
#define DHTTYPE DHT22
#define DSMPIN D4

/** Define Lib Variables */
Adafruit_ADS1015 ads;
DHT dht(DHTPIN, DHTTYPE);

/** Define System Variables */
const char *ssid = "wifi-ssid";
const char *password = "wifi-password";
const char *stationId = "station-id";
const char *host = "aqm-host";
const char *hostUrlPost = "aqm-host-dataraw-route";

const long sampleTime = 30000;
unsigned long duration;
unsigned long startTime;
unsigned long endTime;
unsigned long lowPulseOccupancy = 0;

void setup()
{
  Serial.begin(115200);

  configureAds();
  configureDht();
  configureDsm();
  configureWifi();

  startTime = millis();
}

void loop()
{
  duration = pulseIn(DSMPIN, LOW);

  lowPulseOccupancy += duration;

  endTime = millis();
  if ((endTime - startTime) > sampleTime)
  {
    float ratio = lowPulseOccupancy / (sampleTime * 10.0);
    float pm25 = getParticleMgM3(ratio);
    float carbonMonoxide = ads.readADC_SingleEnded(0);
    float ozone = ads.readADC_SingleEnded(1) / 1000;
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    sendData(pm25, carbonMonoxide, ozone, temperature, humidity);

    lowPulseOccupancy = 0;
    startTime = millis();
  }
}

/**
 * Configure Pins
 */
void configureDsm()
{
  pinMode(DSMPIN, INPUT);
}

/**
 * Configure Pins
 */
void configureDht()
{
  dht.begin();
}

/**
 * Configure ADS 1015
 */
void configureAds()
{
  ads.setGain(GAIN_TWOTHIRDS);

  if (!ads.begin())
  {
    Serial.println("Failed to initialize ADS.");

    while (true)
      ;
  }
}

/**
 * Configure and Connect to Wifi
 */
void configureWifi()
{
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  for (int counter = 0; counter < 10; counter++)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      Serial.print(".");
    }
    else
    {
      break;
    }
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Failed to connect Wi-Fi.");

    while (true)
      ;
  }
  else
  {
    Serial.println("");
  }

  Serial.println("Connection Established!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

/**
 * Send Data
 */
void sendData(float pm25, float carbonMonoxide, float ozone, float temperature, float humidity)
{
  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure();

  if (client.connect(host, 443))
  {
    http.begin(client, hostUrlPost);
    http.addHeader("Content-Type", "application/json");

    char post[350];

    snprintf(post, sizeof(post), "{\"stationId\":\"%s\", \"particulateMaterialTwoFive\":\"%f\", \"carbonMonoxide\":\"%f\", \"ozone\":\"%f\", \"temperature\":\"%f\", \"humidity\":\"%f\"}", stationId, pm25, carbonMonoxide, ozone, temperature, humidity);

    int httpCode = http.POST(post);

    if (httpCode <= 0)
    {
      Serial.printf("HTTP POST Failed. Error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  else
  {
    Serial.println("Client Conection Erro");
  }
}

float getParticlePpm(float ratio)
{
  float ppm = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;
  return ppm;
}

float getParticleMgM3(float ratio)
{
  float mgm3 = 0.001915 * pow(ratio, 2) + 0.09522 * ratio - 0.04884;
  return mgm3 < 0.0 ? 0.0 : mgm3;
}