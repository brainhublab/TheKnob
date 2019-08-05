/* MIT License
 *  Copyright (C) <2019> <brainhublab> <ideas@brainhub.co>
 *  
 * This code implements arduino compatible firmware for TheKnob.
 * 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */


#define FAST_ANALOG_READ_ENABLED 1
#define ENCODER_USE_INTERRUPTS
//#define ENCODER_OPTIMIZE_INTERRUPTS

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

//pins
#define INPUT_SOUND_R_PIN A1 //analog pin for right audio input
#define INPUT_SOUND_L_PIN A0 //analog pin for left audio input
#define ENCODER_BUTTON_PIN 2// 4 //encoder button digital pin 
#define LED_RING_CONTROL_PIN 11 //5 //led ring control digital pin 

//rgb ring
#define LED_RING_SIZE 16 //number of leds on rgb ring 
byte activeBrightness = 200; //default active brightness

DEFINE_GRADIENT_PALETTE(soundLevelGradientPalete) // gradient palette, more info here https://learn.adafruit.com/fancyled-library-for-circuitpython/fastled-helpers and here https://github.com/FastLED/FastLED/wiki/Gradient-color-palettes
{
  0,    0,    255,  0,  // green
  100,  255,  255,  0,  // yellow
  150,  255,  100,  0,  // orange
  255,  69,   0,    0,  // orange red
  255,  0,    0,    0   // red
};

short defaultPassiveColor = HUE_RED; //default and idle collor
short defaultPassiveColors[8] = {HUE_RED, HUE_ORANGE, HUE_YELLOW, HUE_GREEN, HUE_AQUA, HUE_BLUE, HUE_PURPLE, HUE_PINK}; //default and idle colors array for user configurations

//rgb
#define MODES 5 //number of lighting modes
#define VU_RAINBOW_STEP  5 //step of rainbow transaction
byte backLightSaturation = 200; //default saturation
byte backLightSpeed = 100; //speed of changing colors
#define ANIMATION_LOOP_PERIOD 7
byte passiveBrightness = 120;

//audio
#define SIGNAL_GAIN_EXPONENT 1.8  //amplify signal 
uint16_t lowPassTreshold = 13;  //default noise level (can be calibrated )
#define TRESHOLD_CORRECTION_COEFICIENT 2 //treshold for noise 
float inputSoundSmoothness = 0.8;
#define VOLUME_AVERAGE_COEF 1.8
