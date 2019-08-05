[![N|Solid](https://cloud.brainhub.co/index.php/apps/files_sharing/ajax/publicpreview.php?x=1680&y=567&a=true&file=4040knoblogo.jpg&t=8PoEqA5PxznjsOp&scalingup=0)](https://theknob.co)

TheKnob is a volume and scroll control HID device with following features.

  * Audio volume level control on your PC (HID);
  * Scrolling (HID);
  * One audio input and two switchable audio outputs;
  * RGB led lights with the following modes:
    * VU meter rainbow mode.
    * VU meter static mode.
    * Rainbow mode.
    * Slow transaction mode.
    * Static color mode.

### Usage

By default TheKnob is in volume controll mode with VU meter rainbow mode. The leds lighting modes can be switched by a **single click** on on concrete knob. To switch to scrolling mode you need to double click on the knob.

To change the default background color you need to enter in setting mode with **long press** on the knob (LEDs indicate this with red lights). The setting mode provide two configurations:
  * **Single click** in setting mode changes the default background color of the led lighting. 
  `NOTE - you need to be in Static color mofe of the leds for easier visualizing of the curent led color`
  * **Double click** measures the noise in your settup for better VU meter visualization.
  `NOTE - by default the noise is configured and please don't try to calibrate system noise if you don't realy need it. If you enter in noise calibration mode the audio input need to be connected but without playng of any sound.`
 
To save settings and exit the setting mode you neet to long pres the knob (LEDs indicate  this with green lights)

### Tech
TheKnob uses a number of open source projects to work properly:

* [ButtonEvents](https://github.com/fasteddy516/ButtonEvents) - button arduino library;
* [HID Project](https://github.com/NicoHood/HID) - awesome HID library for arduino;
* [Encoder](https://github.com/PaulStoffregen/Encoder) - powerful rotary encoder library for arduino;
* [FastLED](https://github.com/FastLED/FastLED) - powerful led control arduino library;
* [FHT](http://wiki.openmusiclabs.com/wiki/ArduinoFHT) - The Fast Hartley Transform arduino library;
* [EEPROMEx](https://github.com/thijse/Arduino-EEPROMEx) - extension of the standard Arduino EEPROM librar;

### License

[MIT](./LICENSE.txt)


