#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

bool debug = true;

const char* ssid = "aa--"; // your wifi network name
const char* password = "me--"; // your wifi password

const char* depression = "";

const char* address = "4yGf--"; // Solana public address
String apiKey = "d3c95--"; // Helius API key
String heliusCluster = "devnet"; // use devnet

int64_t balance = 0;
int64_t unconfirmed = 0;
int64_t history = 0;
int64_t take = 0;
int work = 100;

// you walllet qrcode bitmap
// generator qrcode here https://qrcode.tec-it.com/en
// generate bitmap for qrcode here https://javl.github.io/image2cpp/ !! TAKE [Invert image colors] !! size bitmap 62x62
const unsigned char qr_code [] PROGMEM = {
	0xff, 0xfe
};

//logo
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
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String heliusHost() {
  if (heliusCluster == "devnet") return "devnet.helius-rpc.com";
  return "mainnet.helius-rpc.com";
}

bool getBalances() {
  String host = heliusHost();
  String path = "/?api-key=" + apiKey;
  String body = "{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"getBalance\",\"params\":[\"" + String(address) + "\"]}";

  if(debug) Serial.println("[API] Connecting to " + host);
  if(debug) Serial.println("[API] Request body: " + body);

  WiFiClientSecure client;
  client.setInsecure();

  if (!client.connect(host.c_str(), 443)) {
    if(debug) Serial.println("[ERROR] CONNECT FAIL");
    depression = (char*)"E_A0";
    return false;
  }

  client.println("POST " + path + " HTTP/1.1");
  client.println("Host: " + host);
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(body.length()));
  client.println("Connection: close");
  client.println();
  client.print(body);

  if(debug) Serial.println("[API] Sent request");

  // skip headers
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  // skip chunk size line (HTTP chunked encoding)
  client.readStringUntil('\n');

  String json = "";
  unsigned long t = millis();
  while (millis() - t < 5000) {
    while (client.available()) {
      json += (char)client.read();
      t = millis();
    }
  }

  if(debug) Serial.println("[API] Response: " + json);

  if (json.length() == 0) {
    if(debug) Serial.println("[ERROR] Empty response");
    depression = "E_A0";
    return false;
  }

  if (json.indexOf("\"error\"") != -1) {
    if(debug) Serial.println("[ERROR] JSON-RPC error in response");
    depression = "E_A0";
    return false;
  }

  StaticJsonDocument<1024> doc;
  DeserializationError err = deserializeJson(doc, json);
  if (err) {
    if(debug) Serial.print("[ERROR] JSON parse error: ");
    if(debug) Serial.println(err.c_str());
    depression = "E_A0";
    return false;
  }

  // Parse: {"jsonrpc":"2.0","result":{"context":{...},"value":500000000},"id":1}
  if (!doc.containsKey("result")) {
    if(debug) Serial.println("[ERROR] No 'result' field in response");
    if(debug) Serial.println("[DEBUG] Available keys:");
    for (JsonPair kv : doc.as<JsonObject>()) {
      if(debug) Serial.println(String("  - ") + kv.key().c_str());
    }
    depression = "E_A0";
    return false;
  }

  JsonObject result = doc["result"].as<JsonObject>();
  
  // Try to find 'value' - could be in result or at top level
  int64_t val = 0;
  if (result.containsKey("value")) {
    val = result["value"].as<int64_t>();
    if(debug) Serial.print("[DEBUG] Found 'value' in result: ");
    if(debug) Serial.println(val);
  } else if (doc.containsKey("value")) {
    val = doc["value"].as<int64_t>();
    if(debug) Serial.print("[DEBUG] Found 'value' at top level: ");
    if(debug) Serial.println(val);
  } else {
    if(debug) Serial.println("[ERROR] No 'value' field found in response");
    if(debug) Serial.println("[DEBUG] Result keys:");
    for (JsonPair kv : result) {
      if(debug) Serial.println(String("  - ") + kv.key().c_str());
    }
    depression = "E_A0";
    return false;
  }

  balance = val;
  unconfirmed = 0;
  depression = ""; // clear error on success
  if(debug) Serial.print("[API] SUCCESS - Balance: ");
  if(debug) Serial.print(balance);
  if(debug) Serial.print(" lamports = ");
  if(debug) Serial.print(formatSOL(balance));
  if(debug) Serial.println(" SOL");
  return true;
}

// removed LTC helper; using formatSOL for Solana (lamports -> SOL)


String formatSOL(int64_t value) {
  int64_t whole = value / 1000000000LL;
  int64_t frac = value % 1000000000LL;
  if (frac < 0) frac = -frac;

  String fracStr = String(frac);
  while (fracStr.length() < 9) fracStr = "0" + fracStr;
  while (fracStr.endsWith("0")) fracStr.remove(fracStr.length() - 1);

  if (fracStr.length() == 0) return String(whole);
  return String(whole) + "." + fracStr;
}

// BlockCypher code removed — using Helius JSON-RPC getBalances() above
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println("OLED error");
    while (true);
  }

  randomSeed(analogRead(0));


  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.drawBitmap(70, 2, logo, 60, 60, SSD1306_WHITE);


  display.setTextSize(1);
  display.setCursor(5, 55);
  display.println("by bas_ic");

  display.setCursor(5, 10);
  display.println("try WIFI");
  display.display();
  WiFi.begin(ssid, password);

  int wifi_count = 0;
  while (WiFi.status() != WL_CONNECTED && wifi_count < 20) {
    delay(500);
    wifi_count++;
    if(debug) Serial.print(".");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    if(debug) Serial.println();
    if(debug) Serial.println("[WiFi] Connected!");
    getBalances();
  } else {
    if(debug) Serial.println();
    if(debug) Serial.println("[WiFi] Connection failed");
    depression = "E_WiFi";
  }
  display.setCursor(5, 25);
  display.println("try API");
  display.display();

  //Serial.print("IP: ");
  //Serial.println(WiFi.localIP());

  delay(500);
  display.clearDisplay();

}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 

  work = work + 1;

  

  if(work == 100 || work == 200 || work == 300 || work >= 400){
    display.clearDisplay();
    
    display.drawBitmap(66, 0, qr_code, 62, 62, SSD1306_WHITE);
    display.setCursor(0, 5);
    display.println(formatSOL(balance));
    display.setCursor(0, 15);
    display.println("SOL");
    if(take != 0 && take != balance){
      display.setCursor(0, 35);
      display.setTextSize(1);
      display.println(formatSOL(take));
      if(debug == false){ Serial.println(formatSOL(take)); };
      display.setCursor(0, 45);
      display.println("take");
      display.setTextSize(1);
      digitalWrite(LED_BUILTIN, LOW); 
    }

      if(work >= 400){
      
      getBalances();
      if(balance != history){
        take = balance - history;
        history = balance;
      }

      work = 0;
      display.setCursor(0, 55);
      display.println("update..");
      digitalWrite(LED_BUILTIN, LOW); 
    
    }
    
    display.display();
  }

  if(strlen(depression) > 0){
      display.fillRect(0, 0, 128, 70, SSD1306_WHITE); // biały pasek
      
      display.setTextColor(SSD1306_BLACK); // czarny tekst
      display.setCursor(5, 5);
      display.println("THIS TERMINAL HAVE  A DEPRESSION");
      display.setCursor(5, 25);
      display.println("PLESSE CHECK README.md by fix this problem");
      display.setCursor(40, 45);
      display.setTextSize(2);
      display.println(depression);

      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(1);
      display.display();
  };
  yield();
  delay(100);
  
};


