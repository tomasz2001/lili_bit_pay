#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


extern const unsigned char logo [];
extern const unsigned char qr_code [];
extern const char* depression;

extern long balance;
extern long unconfirmed;
extern long history;
extern long take;

String formatLTC(long value) {

  long whole = value / 100000000;
  long frac  = value % 100000000;


  String fracStr = String(frac);
  while (fracStr.length() < 8) {
    fracStr = "0" + fracStr;
  }


  while (fracStr.endsWith("0")) {
    fracStr.remove(fracStr.length() - 1);
  }

  if (fracStr.length() == 0) {
    return String(whole);
  }

  return String(whole) + "." + fracStr;
}

void depression_check() {
  if(depression != ""){
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

};

void run_screen(){
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println("OLED error");
    while (true);
  };
};

void clear_screen(){
  display.clearDisplay();
};

void bot_screen(){

  display.setTextColor(SSD1306_WHITE);

  display.drawBitmap(70, 2, logo, 60, 60, SSD1306_WHITE);


  display.setTextSize(1);
  display.setCursor(5, 55);
  display.println("by bas_ic");
};
void bot_screen_wifi(){
  display.setCursor(5, 10);
  display.println("try WIFI");
  display.display();
};
void bot_screen_api(){
  display.setCursor(5, 25);
  display.println("try API");
  display.display();
};
void home_screen(){
  display.drawBitmap(66, 0, qr_code, 62, 62, SSD1306_WHITE);
  display.setCursor(0, 5);
  display.println(formatLTC(balance));
  display.setCursor(0, 15);
  display.println("balance");
};
void take_screen(){
  display.setCursor(0, 35);
  display.setTextSize(1);
  display.println(formatLTC(take));
  display.setCursor(0, 45);
  display.println("take");
  display.setTextSize(1);
};
void update_screen(){
  display.setCursor(0, 55);
  display.println("update..");
  digitalWrite(LED_BUILTIN, LOW); 
};
void end_screen(){
  display.display();
}