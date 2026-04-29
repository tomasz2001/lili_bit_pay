extern const char* depression;
extern const char* address;
extern String apiKey;
extern String network;

extern long balance;
extern long unconfirmed;
extern long history;
extern long take;

long extractBalance(String json) {
  int pos = json.indexOf("\"balance\":");
  if (pos == -1) {
    Serial.println("NO BALANCE KEY");
    return -1;
  }

  String sub = json.substring(pos + 10);
  sub.trim();

  int end = sub.indexOf(",");
  if (end == -1) end = sub.indexOf("}");

  String value = sub.substring(0, end);

  long balance = value.toInt();

  //Serial.println("PARSED BALANCE:");
  //Serial.println(balance);

  return balance;
}
long extractUnconfirmed(String json) {
  int p = json.indexOf("\"unconfirmed_balance\":");
  if (p == -1) return -1;

  String sub = json.substring(p + 24);
  int end = sub.indexOf(",");
  if (end == -1) end = sub.indexOf("}");

  return sub.substring(0, end).toInt();
}

bool getBalances(String network = "ltc") {

  String url = "/v1/" + String(network) + "/main/addrs/" + String(address) + "?token=" + apiKey;

  WiFiClientSecure client;
  client.setInsecure();

  if (!client.connect("api.blockcypher.com", 443)) {
    Serial.println("CONNECT FAIL");
    depression = "E_A0";
    return false;
  }

  client.println("GET " + url + " HTTP/1.1");
  client.println("Host: api.blockcypher.com");
  client.println("Connection: close");
  client.println();

  // skip headers
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

  if (json.length() == 0 || json.indexOf("error") != -1) {
    depression = "E_A0";
    return false;
  }

  balance = extractBalance(json);
  unconfirmed = extractUnconfirmed(json);

  return true;
}