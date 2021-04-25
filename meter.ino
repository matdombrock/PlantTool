// DHT CODE
// Based on code written by ladyada, public domain
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
// Custom
#include "State.h"
#include "utility.h"
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Setup DHT
#define DHTPIN 3
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
// Setup pins and state
#define BTNPIN 2
#define CAPPIN A3
#define PRPIN A2 
State st;

void modeCap(){
    st.capRead = analogRead(CAPPIN);
    int per = toPer(st.capRead,true);
    writeToScreen(String(per)+"%",3);
}
void modeCap2(){
    st.capRead = analogRead(CAPPIN);
    int per = toPer(st.capRead,true);
    drawBar(per);
}
void modePR(){
    st.prRead = analogRead(PRPIN);
    int per = toPer(st.prRead);
    writeToScreen(String(per)+"%",3);
}
void modePR2(){
    st.prRead = analogRead(PRPIN);
    int per = toPer(st.prRead);
    drawBar(per);
}
void modeHumidity(){
    st.humidity = dht.readHumidity();
    writeToScreen(String(st.humidity)+"% H",3);
}
void modeTempC(){
    st.temp = dht.readTemperature();
    writeToScreen(String(st.temp)+"C",3);
}
void modeTempF(){
    st.tempF = dht.readTemperature(true);
    int per = toPer(st.tempF);
    writeToScreen(String(st.tempF)+"F",3);
}
void modeHIF(){
    st.heatIndexF = dht.computeHeatIndex(st.tempF, st.humidity);
    writeToScreen(String(st.heatIndexF)+"F",3);
}
void modeHIC(){
    st.heatIndex = dht.computeHeatIndex(st.temp, st.humidity,false);
    writeToScreen(String(st.heatIndex)+"C",3);
}
void switchMode(){
    st.mode++;
    if(st.mode>6){
        st.mode=0;
    }
    switch(st.mode){
        case 0:
            writeToScreen("WATER");
            break;
        case 1:
            writeToScreen("WATER2");
            break;
        case 2:
            writeToScreen("LIGHT");
            break;
        case 3:
            writeToScreen("LIGHT2");
            break;
        case 4:
            writeToScreen("HUMID");
            break;
        case 5:
            writeToScreen("TEMP C");
            break;
        case 6:
            writeToScreen("TEMP F");
            break;
        case 7:
            writeToScreen("HI F");
            break;
        case 8:
            writeToScreen("HI C");
            break;
    }
    delay(500);
}
void runMode(){
    switch(st.mode){
        case 0:
            modeCap();
            break;
        case 1:
            modeCap2();
            break;
        case 2:
            modePR();
            break;
        case 3:
            modePR2();
            break;
        case 4:
            modeHumidity();
            break;
        case 5:
            modeTempC();
            break;
        case 6:
            modeTempF();
            break;
        // case 7:
        //     writeToScreen("HI F");
        //     break;
        // case 8:
        //     writeToScreen("HI C");
        //     break;
    }
}
void setup(){
    pinMode(BTNPIN, INPUT);
    Serial.begin(115200);
    dht.begin();
    Serial.println("Start");
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    writeToScreen("EnvMonX",3);
    DHTRead();//Grab inital reading
    delay(500);
}
void loop(){
    st.btn = digitalRead(BTNPIN);
    if (st.btn == HIGH) {
        switchMode();
    } else {
        
    }
    runMode();
}