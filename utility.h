/*
Define some utility functions to avoid cluttering main code
*/
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include "State.h"
extern Adafruit_SSD1306 display;
extern State st;
extern DHT dht;
void writeToScreen(String incoming, int fsize = 3) {
  display.clearDisplay();
  display.setTextSize(fsize);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 10);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  int len = incoming.length() + 1;
  char iarray[len];
  incoming.toCharArray(iarray, len);
  display.write(iarray);
  display.display();
}

void drawBar(int per){
    display.clearDisplay();
    display.drawRect(1, 1, display.width()-1, display.height()-1, SSD1306_WHITE);
    display.fillRect(0, 0, (display.width()/100.00)*per, display.height(), SSD1306_WHITE);
    display.display();
    delay(200);
}

int toPer(int val, bool invert=false){
    int maxVal = 730;
    int rel = val;
    if(invert){
        rel = maxVal - val;
    }
    float scale = 100.00/maxVal;
    int per = rel * scale;
    return per;
}
void DHTRead(){
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    st.humidity = dht.readHumidity();
    // Read temperature as Celsius (the default)
    st.temp = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    st.tempF = dht.readTemperature(true);
    // Check if any reads failed and exit early (to try again).
    if (isnan(st.humidity) || isnan(st.temp) || isnan(st.tempF)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
    // Compute heat index in Fahrenheit (the default)
    st.heatIndexF = dht.computeHeatIndex(st.tempF, st.humidity);
    // Compute heat index in Celsius (isFahreheit = false)
    st.heatIndex = dht.computeHeatIndex(st.temp, st.humidity, false);
}