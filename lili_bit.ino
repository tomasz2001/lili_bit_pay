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
MIIE9DCCBHqgAwIBAgISBSdzm7V6bHRuZEccCRgB4HnjMAoGCCqGSM49BAMDMDMx
CzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQwwCgYDVQQDEwNZ
RTIwHhcNMjYwODI4MDgxODA5WhcNMjYxMTI2MDgxODA4WjASMRAwDgYDVQQDEwdp
YzAuYXBwMHYwEAYHKoZIzj0CAQYFK4EEACIDYgAEpSze0fexttMcV5G9xpq2iBgP
C9sVg2dQguOpNXEVvhXGwJqWNE9guPB990tNhiMa5mzkskq5QYjpOipCUA/oCVhG
MzO7jfb24njGIShe4l5rOLaiNHrRz+TSTjZ2mngho4IDcDCCA2wwDgYDVR0PAQH/
BAQDAgeAMBMGA1UdJQQMMAoGCCsGAQUFBwMBMAwGA1UdEwEB/wQCMAAwHQYDVR0O
BBYEFKKgKto6DQH6IrvDbuTH9zPHbRaRMB8GA1UdIwQYMBaAFLlZ8o7PIvCG0zdI
/3YUGLqC2FWHMDMGCCsGAQUFBwEBBCcwJTAjBggrBgEFBQcwAoYXaHR0cDovL3ll
Mi5pLmxlbmNyLm9yZy8wggFpBgNVHREEggFgMIIBXIIPKi5jYWZmZWluZS5zaXRl
ghIqLmNhZmZlaW5lLndlYnNpdGWCDiouY2FmZmVpbmUueHl6ghIqLmRldi5jYWZm
ZWluZS54eXqCCSouaWMwLmFwcIIJKi5pY3AubmV0ggkqLmljcDAuaW+CCSouaWNw
MS5pb4IWKi5pbnRlcm5ldGNvbXB1dGVyLm9yZ4IaKi5wcm9kLXN0cmVzcy5jYWZm
ZWluZS54eXqCFioucmF3LmNhZmZlaW5lLndlYnNpdGWCDSoucmF3LmljMC5hcHCC
DSoucmF3LmljcC5uZXSCDSoucmF3LmljcDAuaW+CDSoucmF3LmljcDEuaW+CDWNh
ZmZlaW5lLnNpdGWCEGNhZmZlaW5lLndlYnNpdGWCDGNhZmZlaW5lLnh5eoIHaWMw
LmFwcIIKaWNwLWFwaS5pb4IHaWNwLm5ldIIHaWNwMC5pb4IHaWNwMS5pbzATBgNV
HSAEDDAKMAgGBmeBDAECATAvBgNVHR8EKDAmMCSgIqAghh5odHRwOi8veWUyLmMu
bGVuY3Iub3JnLzEwMC5jcmwwggENBgorBgEEAdZ5AgQCBIH+BIH7APkAdwCUTkOH
+uzB74HzGSQmqBhlAcfTXzgCAT9yZ31VNy4Z2AAAAaBHqC4mAAAEAwBIMEYCIQDS
NZG9NlXuXVuXrtH0bo7qt/mgM2iF0Oxx/3BBiIqeagIhAObrKJ/+Jx1K2WuO24bO
0nFyZhlmLcSuMVdtmr4aUH1sAH4AJuNkblhpISO8ND9HJDWbN5LNJFqI2BXTkzP9
mRirRyMAAAGgR6gnXwAIAAAFADoN6BYEAwBHMEUCIQD73eQHhqNAbfruHpYYSKEc
cB00l0sW9qx4VC8YU74NxAIgZRcGH9nk25N82yJX0CjdHgUmFf/m1O/q/g84Do7C
xkEwCgYIKoZIzj0EAwMDaAAwZQIwOMc/yPyxVya4ZIUPUFV6ywzEmnf1GE99tf3F
CDwfdKeuYMl25FEQySAbxF8UF5HpAjEAuGUCCuzzrMVFSxRXKsYyMcfbZXyG2yZJ
NLB+msU1sgPHLeALewYPOXec3gI12MOM
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIICjDCCAhGgAwIBAgIQTfOxXdbAeExQfNN7WObxFTAKBggqhkjOPQQDAzAuMQsw
CQYDVQQGEwJVUzENMAsGA1UEChMESVNSRzEQMA4GA1UEAxMHUm9vdCBZRTAeFw0y
NTA5MDMwMDAwMDBaFw0yODA5MDIyMzU5NTlaMDMxCzAJBgNVBAYTAlVTMRYwFAYD
VQQKEw1MZXQncyBFbmNyeXB0MQwwCgYDVQQDEwNZRTIwdjAQBgcqhkjOPQIBBgUr
gQQAIgNiAARxmrQzkdbEEL3MqXt3dJQttYc47axkdDTHud5TPqM2z5uSD5cmk0Wr
HlWXvnlvqBLqiB34kluxIbmMyAiq3/YD6e80/vV259K8XQIdjFXloYOa0mIU71f7
HQ09PvYDlw+jge4wgeswDgYDVR0PAQH/BAQDAgGGMBMGA1UdJQQMMAoGCCsGAQUF
BwMBMBIGA1UdEwEB/wQIMAYBAf8CAQAwHQYDVR0OBBYEFLlZ8o7PIvCG0zdI/3YU
GLqC2FWHMB8GA1UdIwQYMBaAFKPIJlqOoUzQNWP8myPIOq5W809WMDIGCCsGAQUF
BwEBBCYwJDAiBggrBgEFBQcwAoYWaHR0cDovL3llLmkubGVuY3Iub3JnLzATBgNV
HSAEDDAKMAgGBmeBDAECATAnBgNVHR8EIDAeMBygGqAYhhZodHRwOi8veWUuYy5s
ZW5jci5vcmcvMAoGCCqGSM49BAMDA2kAMGYCMQDIcnw5dcZLN9ffynXnnkLD/itS
JEycJPb3sRkzeqBowup7vOsAwaqoCnNn/jh9wycCMQCJM6CPlaOC4pQYYbJtVPYb
DKrIb2EKk5NpOpE6/XttQYZV/3gilB9l+Cc/DOVwmyg=
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIICpjCCAiugAwIBAgIRAIchZfw0tuX7qK3Vs3BftTowCgYIKoZIzj0EAwMwTzEL
MAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2VhcmNo
IEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDIwHhcNMjYwNTEzMDAwMDAwWhcN
MzIwOTAyMjM1OTU5WjAuMQswCQYDVQQGEwJVUzENMAsGA1UEChMESVNSRzEQMA4G
A1UEAxMHUm9vdCBZRTB2MBAGByqGSM49AgEGBSuBBAAiA2IABDwS/6vhrcVqcbBo
+wgdI3fwn9x7DNJJOY/lTOti0vkwuRN87RhEhTH17E7XyFjWsPYhIPt/wzOqxTd2
b+4ZJNy9ID04YywF9U5zasDVyGSNErVNtz8uSGh5izW87j77GaOB6zCB6DAOBgNV
HQ8BAf8EBAMCAQYwEwYDVR0lBAwwCgYIKwYBBQUHAwEwDwYDVR0TAQH/BAUwAwEB
/zAdBgNVHQ4EFgQUo8gmWo6hTNA1Y/ybI8g6rlbzT1YwHwYDVR0jBBgwFoAUfEKW
rt5LSDv6kviejM9ti6lyN5UwMgYIKwYBBQUHAQEEJjAkMCIGCCsGAQUFBzAChhZo
dHRwOi8veDIuaS5sZW5jci5vcmcvMBMGA1UdIAQMMAowCAYGZ4EMAQIBMCcGA1Ud
HwQgMB4wHKAaoBiGFmh0dHA6Ly94Mi5jLmxlbmNyLm9yZy8wCgYIKoZIzj0EAwMD
aQAwZgIxAMU19WCtmxVND8UHBZRoma49Z7jPs64Dma0eTu1OChVbB/2J7GV3nvYK
Ax54uk1G9QIxAO0miLVJu8PLNiXXXkiE/gsK3CTRTF/aeo4bMX42Zw40csRU6AC2
6hSW1/IWaas6dg==
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIICGzCCAaGgAwIBAgIQQdKd0XLq7qeAwSxs6S+HUjAKBggqhkjOPQQDAzBPMQsw
CQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJuZXQgU2VjdXJpdHkgUmVzZWFyY2gg
R3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBYMjAeFw0yMDA5MDQwMDAwMDBaFw00
MDA5MTcxNjAwMDBaME8xCzAJBgNVBAYTAlVTMSkwJwYDVQQKEyBJbnRlcm5ldCBT
ZWN1cml0eSBSZXNlYXJjaCBHcm91cDEVMBMGA1UEAxMMSVNSRyBSb290IFgyMHYw
EAYHKoZIzj0CAQYFK4EEACIDYgAEzZvVn4CDCuwJSvMWSj5cz3es3mcFDR0HttwW
+1qLFNvicWDEukWVEYmO6gbf9yoWHKS5xcUy4APgHoIYOIvXRdgKam7mAHf7AlF9
ItgKbppbd9/w+kHsOdx1ymgHDB/qo0IwQDAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0T
AQH/BAUwAwEB/zAdBgNVHQ4EFgQUfEKWrt5LSDv6kviejM9ti6lyN5UwCgYIKoZI
zj0EAwMDaAAwZQIwe3lORlCEwkSHRhtFcP9Ymd70/aTSVaYgLXTWNLxBo1BfASdW
tL4ndQavEi51mI38AjEAi/V3bNTIZargCyzuFJ0nN6T5U6VR5CmD1/iQMVtCnwr1
/q4AaOeMSQ+2b1tbFfLn
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
while (addres == "") {
  if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure client;
    client.setCACert(rootCACertificate);

    HTTPClient https;

    std::string full = "https://ygibg-kiaaa-aaaai-ap7yq-cai.icp0.io/";
    full += "addres";

    if (https.begin(client, full.c_str())) {
      int httpCode = https.GET();

      if (httpCode == HTTP_CODE_OK) {
        String response = https.getString();
        response.trim();
        addres = response;

        if (debug) Serial.println(addres);
      }

      https.end();
    }
  }

  if (addres == "") {
    delay(10000);  // Odczekaj 1 sekundę przed kolejną próbą
  
  }
}
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

  int64_t whole = value / scale;
  int64_t frac = value % scale;

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

  delay(2500);
  display.setCursor(5, 5);
  display.println("netw ready");
  randomSeed(analogRead(0));
   display.display();
  getAddres();
  while (!getAddres()) {
    delay(100);
  }
  display.setCursor(5, 25);
  display.println("addr ready");
   display.display();
  //getFormat();
  delay(2500);
  display.setCursor(5, 35);
  display.println("form ready");
   display.display();
  //getCoin();
  delay(2500);
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

