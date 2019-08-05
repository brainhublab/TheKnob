/* MIT License
 *  Copyright (C) <2019> <brainhublab> <ideas@brainhub.co>
 *  
 * This code implements arduino compatible firmware for TheKnob.
 * 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

void buttonClick()
{

  encoderButton.update();

  //change backlight modes
  if (encoderButton.tapped())
  {
    if (!setupMode)
    {
      if (++lightMode >= MODES)
      {
        lightMode = 0;  //change mode
      }
      EEPROM.updateByte(1, lightMode); //saving mode
    }
    else
    {
      changeDefColor();//changing default color
      EEPROM.updateInt(2, defaultPassiveColor); //saving default color
    }

    //Serial.println("TAPPED----------------------------------");
  }

  //switch to scroll mode or entering in filter calibration if is setup mode
  else if (encoderButton.doubleTapped())
  {
    if (!setupMode)
    {
      if (!scrollMode)
      {
        scrollMode = true;
      }
      else
      {
        scrollMode = false;
      }
    }
    else
    {
      FastLED.setBrightness(0);
      FastLED.clear();
      FastLED.show();
      lowPass();  //filter values
      FastLED.setBrightness(activeBrightness); //return to previous backlight mode
      calibrationAnimation(); //calibration animation
      delay(100);

    }

  }

  //entering to setup mode or save settings
  else if (encoderButton.held())
  {
    if (!setupMode)
    {
      blinkOnSetupMode();
      setupMode = true;
    }
    else
    {
      blinkOnSetupMode();
      setupMode = false;
    }
  }
}

void encoderRotation()
{
  //change volume
  if (!scrollMode)
  {
    int newPosition = encoder.read();
    noInterrupts();
    if (newPosition != oldPosition && (newPosition % 2) == 0)
    {
      if (newPosition > oldPosition)
      {
        Consumer.write(MEDIA_VOLUME_UP); //volume++;
        oldPosition = newPosition;
      }
      else
      {
        Consumer.write(MEDIA_VOLUME_DOWN); //volume--;
        oldPosition = newPosition;
      }

    }
    interrupts();
  }
  //scroll
  else
  {
    int newPosition = encoder.read();
    noInterrupts();

    if (newPosition != oldPosition && (newPosition % 2) == 0)
    {
      if (newPosition > oldPosition )
      {
        Mouse.move(0, 0, 1); //scrolling ++
        oldPosition = newPosition;
      }
      else
      {
        Mouse.move(0, 0, -1); // scrolling --;
        oldPosition = newPosition;
      }

    }
    interrupts();
  }
}
