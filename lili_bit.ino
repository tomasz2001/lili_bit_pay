#include <Adafruit_SSD1327.h>
#include <Adafruit_GFX.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <QRCodeGFX.h>
#include <SPI.h>
#include <stdlib.h>


bool debug = true;
bool qwery_history = true;
const char* drone_canister = "https://ygibg-kiaaa-aaaai-ap7yq-cai.icp0.io/";

const char* ssid = "aa--"; // your wifi network name
const char* password = "me--"; // your wifi password

const char* depression = "";
const char* spiner = "";
String coin = "";
String addres = "aaaaa";
int64_t format = 0;
int64_t balance = 0;
int64_t unconfirmed = 0;
int64_t history = 0;
int64_t take = 0;
int work = 100;

// logo
const unsigned char logo [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x8f, 0xff, 0xff, 0x8f, 0xff, 0xe0, 0x00, 
	0x03, 0x8f, 0xff, 0xff, 0x8f, 0xff, 0xe0, 0x00, 0x03, 0x8f, 0xff, 0xff, 0x8f, 0xff, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x1c, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x03, 0xff, 0xff, 0xfc, 0x0e, 0x00, 0x1c, 0x00, 
	0x03, 0xff, 0xff, 0xfc, 0x0e, 0x00, 0x1c, 0x00, 0x03, 0xff, 0xff, 0xfc, 0x0e, 0x00, 0x1c, 0x00, 
	0x00, 0x00, 0x00, 0x1c, 0x0e, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x0e, 0x00, 0x1c, 0x00, 
	0x00, 0x00, 0x00, 0x1c, 0x0e, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xe0, 0x00, 
	0x03, 0xff, 0xff, 0xfc, 0x0e, 0x00, 0x1c, 0x00, 0x03, 0xff, 0xff, 0xfc, 0x0e, 0x00, 0x1c, 0x00, 
	0x03, 0xff, 0xff, 0xfc, 0x0e, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x0e, 0x00, 0x1c, 0x00, 
	0x00, 0x00, 0x00, 0x1c, 0x0e, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x0e, 0x00, 0x1c, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x1c, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x03, 0x8f, 0xff, 0xff, 0x8f, 0xff, 0xe0, 0x00, 
	0x03, 0x8f, 0xff, 0xff, 0x8f, 0xff, 0xe0, 0x00, 0x03, 0x8f, 0xff, 0xff, 0x8f, 0xff, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0xfc, 0x0e, 0x00, 0xe0, 0x00, 
	0x03, 0xfe, 0x00, 0xfc, 0x0e, 0x00, 0xe0, 0x00, 0x03, 0xfe, 0x00, 0xfc, 0x0e, 0x00, 0xe0, 0x00, 
	0x03, 0x81, 0xc7, 0x03, 0x8e, 0x00, 0xe0, 0x00, 0x03, 0x81, 0xc7, 0x03, 0x8e, 0x00, 0xe0, 0x00, 
	0x03, 0x81, 0xc7, 0x03, 0x8e, 0x00, 0xe0, 0x00, 0x03, 0xfe, 0x07, 0xff, 0x81, 0xff, 0x00, 0x00, 
	0x03, 0xfe, 0x07, 0xff, 0x81, 0xff, 0x00, 0x00, 0x03, 0xfe, 0x07, 0xff, 0x81, 0xff, 0x00, 0x00, 
	0x03, 0x80, 0x07, 0x03, 0x80, 0x38, 0x00, 0x00, 0x03, 0x80, 0x07, 0x03, 0x80, 0x38, 0x00, 0x00, 
	0x03, 0x80, 0x07, 0x03, 0x80, 0x38, 0x00, 0x00, 0x03, 0x80, 0x07, 0x03, 0x80, 0x38, 0x00, 0x00, 
	0x03, 0x80, 0x07, 0x03, 0x80, 0x38, 0x00, 0x00, 0x03, 0x80, 0x07, 0x03, 0x80, 0x38, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char* rootCACertificate = R"EOF(
-----BEGIN CERTIFICATE-----
MIICtzCCAjygAwIBAgIRAMWKhaLGI0XgqMRSU4efWTowCgYIKoZIzj0EAwMwTzEL
MAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2VhcmNo
IEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDIwHhcNMjQwMzEzMDAwMDAwWhcN
MjcwMzEyMjM1OTU5WjAyMQswCQYDVQQGEwJVUzEWMBQGA1UEChMNTGV0J3MgRW5j
cnlwdDELMAkGA1UEAxMCRTcwdjAQBgcqhkjOPQIBBgUrgQQAIgNiAARB6ASTCFh/
vjcwDMCgQer+VtqEkz7JANurZxLP+U9TCeioL6sp5Z8VRvRbYk4P1INBmbefQHJF
HCxcSjKmwtvGBWpl/9ra8HW0QDsUaJW2qOJqceJ0ZVFT3hbUHifBM/2jgfgwgfUw
DgYDVR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQGCCsGAQUFBwMCBggrBgEFBQcDATAS
BgNVHRMBAf8ECDAGAQH/AgEAMB0GA1UdDgQWBBSuSJ7chx1EoG/aouVgdAR4wpwA
gDAfBgNVHSMEGDAWgBR8Qpau3ktIO/qS+J6Mz22LqXI3lTAyBggrBgEFBQcBAQQm
MCQwIgYIKwYBBQUHMAKGFmh0dHA6Ly94Mi5pLmxlbmNyLm9yZy8wEwYDVR0gBAww
CjAIBgZngQwBAgEwJwYDVR0fBCAwHjAcoBqgGIYWaHR0cDovL3gyLmMubGVuY3Iu
b3JnLzAKBggqhkjOPQQDAwNpADBmAjEA/e5N+wjAk945cpaFxGaeMC13fyvdbNzX
lRg9HNdElxi5mXdI4az2CykNU07iFwqEAjEAihPCDkw4b1BvfLg8VNLLuaMpn1Rb
Z1682chR6zNRCseyie4SjyTCdkvsAa+omQSf
-----END CERTIFICATE-----
)EOF";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 96

// SPI Pins
#define OLED_CLK  D8    // D8
#define OLED_MOSI D10   // D10
#define OLED_CS   D2    // D2
#define OLED_DC   D3    // D3
#define OLED_RESET D1   // D1

// Software SPI - 128x96
Adafruit_SSD1327 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
QRCodeGFX qrcode(display);

bool getAddres() {     
    if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure client;
    //client.setInsecure();
    client.setCACert(rootCACertificate);
    HTTPClient https;
    std::string full =
    "https://ygibg-kiaaa-aaaai-ap7yq-cai.icp0.io/";
full += "addres";
    if (https.begin(client, full.c_str())){

      int httpCode = https.GET();

      if (httpCode == HTTP_CODE_OK) {

        String response = https.getString();
        response.trim();
        addres = response;  
        if(debug) Serial.println(addres);
        
       
      }

      https.end();
    };
    return true;
  }
  
  return false;
}

bool getBalance() {
    
    if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure client;
    //client.setInsecure();
    client.setCACert(rootCACertificate);
    HTTPClient https;
std::string full =
    "https://ygibg-kiaaa-aaaai-ap7yq-cai.icp0.io/";
full += "ckusdt_balance";


    if (https.begin(client, full.c_str())){

      int httpCode = https.GET();

      if (httpCode == HTTP_CODE_OK) {

        String response = https.getString();
        response.trim();
        balance = response.toInt();
        Serial.println(balance);
        if(debug) Serial.println(balance);
       
      }

      https.end();
    };
    return true;
  }
  
  return false;
}
bool getFormat() {
    
    if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure client;
    //client.setInsecure();
    client.setCACert(rootCACertificate);
    HTTPClient https;
std::string full =
    "https://ygibg-kiaaa-aaaai-ap7yq-cai.icp0.io/";
full += "ckusdt_format";


    if (https.begin(client, full.c_str())){

      int httpCode = https.GET();

      if (httpCode == HTTP_CODE_OK) {

        String response = https.getString();
        response.trim();
        format = response.toInt();
        Serial.println(format);
        if(debug) Serial.println(format);
       
      }

      https.end();
    };
    return true;
  }
  
  return false;
}
bool getCoin() {
    
    if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure client;
    //client.setInsecure();
    client.setCACert(rootCACertificate);
    HTTPClient https;
std::string full =
    "https://ygibg-kiaaa-aaaai-ap7yq-cai.icp0.io/";
full += "howcoin";


    if (https.begin(client, full.c_str())){

      int httpCode = https.GET();

      if (httpCode == HTTP_CODE_OK) {

        String response = https.getString();
        coin = response;
        Serial.println(format);
        if(debug) Serial.println(format);
       
      }

      https.end();
    };
    return true;
  }
  
  return false;
}

String formatCoin(int64_t value) {
  int64_t scale = 1;
  for (uint8_t i = 0; i < format; i++) {
    scale *= 10;
  }

  int64_t whole = value / scale;
  int64_t frac = value % scale;

  if (frac < 0) frac = -frac;

  String fracStr = String(frac);

  // Dopisz zera z lewej strony
  while (fracStr.length() < format) {
    fracStr = "0" + fracStr;
  }

  // Usuń zera na końcu części ułamkowej
  while (fracStr.length() > 0 && fracStr.endsWith("0")) {
    fracStr.remove(fracStr.length() - 1);
  }

  if (fracStr.length() == 0) {
    return String(whole);
  }

  return String(whole) + "." + fracStr;
}
void ensureWiFiConnected() {
  while (WiFi.status() != WL_CONNECTED) {
    if(debug) Serial.println("[WiFi] Disconnected - reconnecting...");
    WiFi.begin(ssid, password);
    
    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 20) {
      delay(500);
      retry++;
      if(debug) Serial.print(".");
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      if(debug) Serial.println();
      if(debug) Serial.println("[WiFi] Reconnected!");
      break;
    }
  }
}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  if (!display.begin(0x3D)) {
    while (1) yield();
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);
  display.drawBitmap(70, 5, logo, 60, 60, SSD1327_WHITE);
  display.setCursor(5, 70);
  display.println("by bas_ic");
  display.display();
  
  delay(1000);
  
  // Configure time with NTP (required for SSL certificate validation)
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  if(debug) Serial.println("[SETUP] Waiting for NTP time synchronization...");
  time_t now = time(nullptr);
  int ntp_timeout = 0;

  while (now < 24 * 3600 && ntp_timeout < 20) {
    delay(500);
    now = time(nullptr);
    ntp_timeout++;
    if(debug) Serial.print(".");
  }
  
  
  if(debug) Serial.println();
  if(debug) Serial.println("[SETUP] NTP time: " + String(ctime(&now)));
  
  

  int wifi_count = 0;
  while (WiFi.status() != WL_CONNECTED && wifi_count < 20) {
    delay(500);
    wifi_count++;
    if(debug) Serial.print(".");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    if(debug) Serial.println();
    if(debug) Serial.println("[WiFi] Connected!");
    getBalance();
  } else {
    if(debug) Serial.println();
    if(debug) Serial.println("[WiFi] Connection failed");
    depression = "E_WiFi";
  }

  delay(500);
  display.setCursor(5, 5);
  display.println("netw ready");
  randomSeed(analogRead(0));
   display.display();
  getAddres();
  delay(500);
  display.setCursor(5, 25);
  display.println("addr ready");
   display.display();
  getFormat();
  delay(500);
  display.setCursor(5, 35);
  display.println("form ready");
   display.display();
  getCoin();
  delay(500);
  display.setCursor(5, 45);
  display.println("coin ready");
   display.display();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 

  work = work + 1;

  if(work == 2 || work == 4 || work == 6 || work >= 8){
    display.clearDisplay();
    display.setTextColor(SSD1327_WHITE);
    
    display.setTextSize(1);
    display.setCursor(5, 5);
    display.println("network");
    display.setCursor(5, 15);
    display.println("  ICP");
    display.setCursor(5, 30);
    display.println("akcept");
    display.setCursor(10, 40);
    display.println(coin);

    qrcode.setScale(2);
    qrcode.draw(addres.c_str(), 50, -2);
    
    if(take != 0 && take != balance){
      display.setCursor(50, 80);
      display.setTextSize(2);
      display.println(formatCoin(take));
      display.setCursor(0, 80);
      display.println("take");
      display.setTextSize(1);
      display.setCursor(20, 60);
      display.println(spiner);
      display.setCursor(10, 60);
      display.println(spiner);
      display.setCursor(0, 60);
      display.println(spiner);
      digitalWrite(LED_BUILTIN, LOW); 
    }

    if(work >= 8){
      getBalance();
      if(balance != history){
        take = balance - history;
        history = balance;
        if(debug == false and take != balance){ Serial.println(take); };
          if(spiner == "X"){
            spiner = "O";
          }else{
            spiner = "X";
          }

      }
      work = 0;
      display.setTextSize(1);
      display.setCursor(5, 67);
      display.println("update");
      digitalWrite(LED_BUILTIN, LOW); 
    }
    
    display.display();
  }

  if(strlen(depression) > 0){
      display.clearDisplay();
      display.fillRect(0, 0, 128, 96, SSD1327_WHITE);
      display.setTextSize(1);
      display.setTextColor(SSD1327_BLACK);
      display.setCursor(10, 10);
      display.println("DEPRESSION");
      display.setCursor(10, 25);
      display.println("CHECK");
      display.setCursor(10, 40);
      display.println("README");
      display.setTextSize(2);
      display.setCursor(45, 60);
      display.println(depression);
      display.display();
  };
  
  yield();
  delay(1000);
};

