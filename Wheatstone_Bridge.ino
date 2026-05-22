#include <splash.h>
const float Vcc = 5.0;
const float R1 = 1000.0;   // 1kΩ
const float R2 = 1000.0;   // 1kΩ
const int ledPin = 10; 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if defined(ESP8266)
  #define BUTTON_A  0
  #define BUTTON_B 16
  #define BUTTON_C  2
  #define WIRE Wire
#elif defined(ARDUINO_ADAFRUIT_FEATHER_ESP32C6)
  #define BUTTON_A  7
  #define BUTTON_B  6
  #define BUTTON_C  5
  #define WIRE Wire
#elif defined(ESP32)
  #define BUTTON_A 15
  #define BUTTON_B 32
  #define BUTTON_C 14
  #define WIRE Wire
#elif defined(ARDUINO_STM32_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
  #define WIRE Wire
#elif defined(TEENSYDUINO)
  #define BUTTON_A  4
  #define BUTTON_B  3
  #define BUTTON_C  8
  #define WIRE Wire
#elif defined(ARDUINO_FEATHER52832)
  #define BUTTON_A 31
  #define BUTTON_B 30
  #define BUTTON_C 27
  #define WIRE Wire
#elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
  #define BUTTON_A  9
  #define BUTTON_B  8
  #define BUTTON_C  7
  #define WIRE Wire
#else
  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
  #define WIRE Wire
#endif

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &WIRE);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("OLED NOT FOUND! Check your wiring/soldering."));
    for(;;); 
  }
  
  Serial.println(F("OLED Found and Initialized"));
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE); 
  display.display();

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

}

void loop() {
  float VA = analogRead(A1) * Vcc / 1023.0;
  float VB = analogRead(A2) * Vcc / 1023.0;

  // Calculate Potentiometer resistance from measured voltage divider
  float Rpot = (R2 * VB) / (Vcc - VB);
  float Adelta = VA - VB;
  // Bridge equation
  float Rx = (R1 * Rpot) / R2;

    // -------------------- OLED Display --------------------


  Serial.print("A0: "); Serial.print(VA, 4);
  Serial.print(" V   A1: "); Serial.print(VB, 4);
  Serial.print(" V   Rpot: "); Serial.print(Rpot, 2);
  Serial.print(" Ohm   Rx: "); Serial.print(Rx, 2); 
  Serial.println(" Ohm");

    if(abs(Adelta)<0.02){
    digitalWrite(ledPin, HIGH);
      display.clearDisplay();      
  display.setCursor(0, 0);
  display.setTextSize(1.5);      
  display.println("Value of Rx:");

  display.setCursor(0, 15);
  display.setTextSize(2);      
  display.print(Rx, 1);
  display.print(" Ohm");
  
  display.display(); // Push buffer to screen
  } else {
      digitalWrite(ledPin, LOW); 
      display.clearDisplay();      
      display.setCursor(0, 0);
      display.setTextSize(1);      
      display.println("Bridge not balanced");
       display.display(); // Push buffer to screen
  }


  delay(200);
}