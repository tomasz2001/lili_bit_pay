#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

extern const char* depression;
extern const char* address;
extern String apiKey;
extern String heliusCluster;

extern int64_t balance;
extern int64_t unconfirmed;
extern int64_t history;
extern int64_t take;

String heliusHost() {
  if (heliusCluster == "devnet") {
    return "devnet.helius-rpc.com";
  }

  return "mainnet.helius-rpc.com";
}

bool getBalances() {
  String host = heliusHost();
  String path = "/?api-key=" + apiKey;
  String body = "{\"jsonrpc\":\"2.0\",\"id\":\"lili-bit-pay\",\"method\":\"getBalance\",\"params\":[\"" + String(address) + "\"]}";

  WiFiClientSecure client;
  client.setInsecure();

  if (!client.connect(host.c_str(), 443)) {
    Serial.println("CONNECT FAIL");
    depression = "E_A0";
    return false;
  }

  client.println("POST " + path + " HTTP/1.1");
  client.println("Host: " + host);
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(body.length()));
  client.println("Connection: close");
  client.println();
  client.print(body);

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  String json = "";
  unsigned long t = millis();

  while (millis() - t < 5000) {
    while (client.available()) {
      json += (char)client.read();
      t = millis();
    }
  }

  if (json.length() == 0 || json.indexOf("\"error\"") != -1) {
    Serial.println(json);
    depression = "E_A0";
    return false;
  }

  StaticJsonDocument<768> doc;
  DeserializationError error = deserializeJson(doc, json);

  if (error || doc["result"]["value"].isNull()) {
    Serial.println("PARSE FAIL");
    Serial.println(json);
    depression = "E_A0";
    return false;
  }

  balance = doc["result"]["value"].as<int64_t>();
  unconfirmed = 0;

  return true;
}
