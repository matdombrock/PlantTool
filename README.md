# Arduino Plant Tool
An Arduino based device that uses 3 sensors to give you reading on just about everything you would need to know about the state of your house or garden plants. 

## Features
* Soil Moisture Level
* Light Level
* Temperate
* Humidity
* Heat Index ([What's That?](https://www.weather.gov/safety/heat-index))

## Components
* Arduino Nano (Or compatible board)
* I2C SSD1306 OLED Display Module (Display)
* DHT11 (Temperateure & Humidity Sensor)
* Photoresistor
* Capacitive Moisture Sensor (Any analog sensor should work)
* 2x 10k Ohm Resistor (one more if your moisture sensor is missing one)
* Push Button
* Jumper Cables, Breadboards ect.

## Setup (Assuming Arduino Nano)
* All devices are powered off 3.3v
* Arduino A4 -> OLED SDA
* Arduino A5 -> OLED SDL
* Arduino A3 <- Cap sensor analog out (Ground with 10k resistor if needed)
* Arduino A2 <- Photoresistor Out (Ground with 10k resistor)
* Arduino D2 <- Button Out (Ground with 10k resistor)
* Arduino D3 <- DHT Out

## Requires
In additon to the Arduino Core, this project requires:
* [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* [DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)