/* MIT License
 *  Copyright (C) <2019> <brainhublab> <ideas@brainhub.co>
 *  
 * This code implements arduino compatible firmware for TheKnob.
 * 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */


void drawPixels()
{

  if (lightMode == 0)
  {
    ranbowVUmeter();
  }
  else if (lightMode == 1)
  {
    standartVUmeter();
  }
  else if (lightMode == 2)
  {
    rainbow();
  }
  else if (lightMode == 3)
  {
    slowTransaction();
  }
  else if (lightMode == 4)
  {
    backLight();
  }

}

void ranbowVUmeter()
{
  if (millis() - rainbowTransactionTimer > 30)
  {
    rainbowTransactionTimer = millis();
    rainBowTransColor = floor((float)rainBowTransColor + VU_RAINBOW_STEP);
  }
  VUiter = 0;
  for (short i = (ledsPerChannel - 1); i > ((ledsPerChannel - 1) - rightLength); i--)
  {
    leds[i] = ColorFromPalette(RainbowColors_p, (VUiter * transactionCoeficient) / 2 - rainBowTransColor);
    VUiter++;
  }
  VUiter = 0;
  for (short i = (ledsPerChannel); i < (ledsPerChannel + leftLength); i++ )
  {
    leds[i] = ColorFromPalette(RainbowColors_p, (VUiter * transactionCoeficient) / 2 - rainBowTransColor);
    VUiter++;
  }
  if (passiveBrightness > 0)
  {
    CHSV curentDark = CHSV(defaultPassiveColor, 255, passiveBrightness);
    for (short i = ((ledsPerChannel - 1) - rightLength); i > 0; i--)
    {
      leds[i] = curentDark;
    }
    for (short i = ledsPerChannel + leftLength; i < LED_RING_SIZE; i++)
    {
      leds[i] = curentDark;
    }
  }
}

void standartVUmeter()
{
  VUiter = 0;
  for (short i = (ledsPerChannel - 1); i > ((ledsPerChannel - 1) - rightLength); i--)
  {
    leds[i] = ColorFromPalette(knobPalette, (VUiter * transactionCoeficient));
    VUiter++;
  }
  VUiter = 0;
  for (short i = (ledsPerChannel); i < (ledsPerChannel + leftLength); i++ )
  {
    leds[i] = ColorFromPalette(knobPalette, (VUiter * transactionCoeficient));
    VUiter++;
  }
  if (passiveBrightness > 0)
  {
    CHSV curentDark = CHSV(defaultPassiveColor, 255, passiveBrightness);
    for (short i = ((ledsPerChannel - 1) - rightLength); i > 0; i--)
    {
      leds[i] = curentDark;
    }
    for (short i = ledsPerChannel + leftLength; i < LED_RING_SIZE; i++)
    {
      leds[i] = curentDark;
    }
  }
}

void rainbow() //here you can find more modes https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#PreparingyourArduinoandyourLEDstrip
{


  if (millis() - rainbowTransactionTimer >= 10)
  {
    rainbowTransactionTimer = millis();
    if (jIter < 256 * 5)
    {
      for (iIter = 0; iIter < LED_RING_SIZE; iIter++)
      {
        rainbowCol = Wheel(((iIter * 256 / LED_RING_SIZE) + jIter) & 255);
        setPixel(iIter, *rainbowCol, *(rainbowCol + 1), *(rainbowCol + 2));
      }
      jIter++;
    }
    else
    {
      jIter = 0;
    }
  }


}

void setPixel(int Pixel, byte red, byte green, byte blue)
{

  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

void slowTransaction()
{
  if (millis() - colorTransactionTimer > backLightSpeed)
  {
    colorTransactionTimer = millis();
    if (++transactionColor > 255)
    {
      transactionColor = 0;
    }
  }
  for (short i = 0; i < LED_RING_SIZE; i++)
  {
    leds[i] = CHSV(transactionColor, backLightSaturation, 255);
  }
}

void backLight()
{
  for (short i = 0; i < LED_RING_SIZE; i++)
  {
    leds[i] = CHSV(defaultPassiveColor, backLightSaturation, 200);
  }

}

void blinkOnSetupMode()
{
  short loadingColor;
  if (!setupMode)
  {
    loadingColor = HUE_RED;
  }
  else
  {
    loadingColor = HUE_GREEN;
  }


  for (short i = 0; i < LED_RING_SIZE; i++)
  {
    // leds[i] = loadingColor;
    leds[i] = CHSV( loadingColor, 200, 255);
    FastLED.show();
    delay(50);

  }


}

void calibrationAnimation()
{

  for (short j = 0; j < LED_RING_SIZE; j++)
  {
    leds[j] = CHSV( defaultPassiveColor, 200, 255);
    FastLED.show();
    delay(30);

  }

}

void draw()//main animation loop
{

  if (millis() - mainTimer > ANIMATION_LOOP_PERIOD) //need to check if needed
  {
    rightSoundLevel = 0.0f;
    lefSoundLevel = 0.0f;

    //select mode
    if (lightMode == 0 || lightMode == 1)
    {
      if (VUmeter())
      {
        drawPixels();
      }

    }
    else if (lightMode == 2 || lightMode == 3 || lightMode == 4)
    {
      drawPixels();
    }
    FastLED.show();
    //FastLED.clear();
    mainTimer = millis();
  }

}

void changeDefColor()
{
  if (++defaultColorIter >= (sizeof(defaultPassiveColors) / sizeof(int)))
  {
    defaultColorIter = 0;   //change default color
  }
  defaultPassiveColor = defaultPassiveColors[defaultColorIter];
}
