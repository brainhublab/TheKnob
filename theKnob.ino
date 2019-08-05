/* MIT License
 *  Copyright (C) <2019> <brainhublab> <ideas@brainhub.co>
 *  
 * This code implements arduino compatible firmware for TheKnob.
 * 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

//includings
#include <ButtonEvents.h> //buttton lib --> https://github.com/fasteddy5/ButtonEvents
#include "HID-Project.h" //lib for make easier using of HID functions --> https://github.com/NicoHood/HID
#include <Encoder.h>  //rotaary encoder lib  --> https://github.com/PaulStoffregen/Encoder
#include "FastLED.h"  //led controll lib --> https://github.com/FastLED/FastLED
#include <FHT.h>  // hartley transformation --> http://wiki.openmusiclabs.com/wiki/ArduinoFHT
#include <EEPROMex.h> //non-volatile memory using lib --> https://github.com/thijse/Arduino-EEPROMEx

//settings header
#include "config.h"

//libraries objects
#define FHT 64 //spectre boundwidht

#define FASTLED_ALLOW_INTERRUPTS 1 //using led with interrupts
CRGB leds[LED_RING_SIZE]; //initialisation of leds
byte ledsPerChannel = LED_RING_SIZE / 2;
int rainBowTransColor; //transformation color
float transactionCoeficient = 255.0f / ledsPerChannel;   //pallete transaction coeficient
CRGBPalette32 knobPalette = soundLevelGradientPalete; //color palette for leds
short transactionColor;

ButtonEvents encoderButton; //rotary encoder lib

Encoder encoder(1, 0); //or 3 2 for arduino pro micro

int oldPosition  = -999;

byte rightLength = 0, leftLength = 0; //needed for color transformation calculation
int rightSoundLevel = 0, lefSoundLevel = 0, lefSoundLevelFiltered = 0, rightSoundLevelFiltered = 0; //variables for containig sound levels before and after filtering
int currentRightLevel = 0, currentLeftLevel = 0; //levels for drawing

int averageLevel = 50; //calculation levels per chanels
short maxLevel = 100;

unsigned long mainTimer = 0, colorTransactionTimer = 0, rainbowTransactionTimer = 0; //timers

float averageCoeficient = 0.012; //multiplying coeficient for better drawing of animation
byte VUiter = 0; //VU step iterator

byte lightMode =  EEPROM.readByte(1); //contains saved mode
bool setupMode = false;
int defaultColorIter = 0;
bool scrollMode = false;

byte *rainbowCol;
uint16_t iIter, jIter;

void setup()
{
  lowPassTreshold = EEPROM.readInt(12);
  //  interrupts();
  defaultPassiveColor = EEPROM.readInt(2);
  Consumer.begin();
  delay(1000);

  pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);
  encoderButton.attach(ENCODER_BUTTON_PIN);

  Serial.begin(9600);
  //preparing faster analog read if it's enabled
  if (FAST_ANALOG_READ_ENABLED)
  {
    //increase to 16 by prescailing
    //more information here -> https://forum.arduino.cc/index.php?topic=6549.0
    sbi(ADCSRA, ADPS2);
    cbi(ADCSRA, ADPS1);
    sbi(ADCSRA, ADPS0);
  }
  //standard led preparing
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  //preparing neopixel ring
  FastLED.addLeds<NEOPIXEL, LED_RING_CONTROL_PIN>(leds, LED_RING_SIZE);
  FastLED.setBrightness(activeBrightness);

  //set analog reference for more precize measurments
  analogReference(INTERNAL);

  digitalWrite(13, HIGH);

}

void loop()
{
  //unsigned long startl = millis();
  //Serial.println(lowPassTreshold);
  buttonClick();     // button check
  encoderRotation(); //rotary encoder check
  draw();       // led animatoin
  //Serial.print("-------------------------| ");
  //Serial.print(millis() - startl);
  //Serial.print(" |-----");

}
