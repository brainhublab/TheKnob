/* MIT License
 *  Copyright (C) <2019> <brainhublab> <ideas@brainhub.co>
 *  
 * This code implements arduino compatible firmware for TheKnob.
 * 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */


bool VUmeter()
{
  for (byte i = 0; i < 120; i ++) //TODO
  {
    currentRightLevel = analogRead(INPUT_SOUND_R_PIN);
    currentLeftLevel = analogRead(INPUT_SOUND_L_PIN);
    if (rightSoundLevel < currentRightLevel)
    {
      rightSoundLevel = currentRightLevel;
    }

    if (lefSoundLevel < currentLeftLevel)
    {
      lefSoundLevel = currentLeftLevel;
    }

  }

  //simple filtering and sharpening the signal
  rightSoundLevel = map(rightSoundLevel, lowPassTreshold, 1023, 0, 1000);
  lefSoundLevel = map(lefSoundLevel, lowPassTreshold, 1023, 0, 1000);


  rightSoundLevel = constrain(rightSoundLevel, 0, 1000);
  lefSoundLevel = constrain(lefSoundLevel, 0, 1000);


  rightSoundLevel = pow(rightSoundLevel, SIGNAL_GAIN_EXPONENT);

  lefSoundLevel = pow(lefSoundLevel, SIGNAL_GAIN_EXPONENT);

  rightSoundLevelFiltered = rightSoundLevel * inputSoundSmoothness + rightSoundLevelFiltered * (1 - inputSoundSmoothness);

  lefSoundLevelFiltered = lefSoundLevel * inputSoundSmoothness + lefSoundLevelFiltered * (1 - inputSoundSmoothness);


  for (short i = 0; i < LED_RING_SIZE; i++)
  {
    leds[i] = CHSV(defaultPassiveColor, 255, passiveBrightness);
  }

  //calculation of sound levels for drawing
  if (rightSoundLevelFiltered > 12 || lefSoundLevelFiltered > 12)
  {

    averageLevel = (rightSoundLevelFiltered + lefSoundLevelFiltered) / 2 * averageCoeficient + averageLevel * (1 - averageCoeficient);

    maxLevel = averageLevel * VOLUME_AVERAGE_COEF;

    rightLength = map(rightSoundLevelFiltered, 0, maxLevel, 0, ledsPerChannel);
    leftLength = map(lefSoundLevelFiltered, 0, maxLevel, 0, ledsPerChannel);

    rightLength = constrain(rightLength, 0, ledsPerChannel);
    leftLength = constrain(leftLength, 0, ledsPerChannel);

    return true;
  }
  return false;
}

void lowPass()
{
  delay(20);
  short currentMax = 0;
  short currentLevel = 0;
  for (byte i = 0; i < 210; i++)
  {
    currentLevel = analogRead(INPUT_SOUND_R_PIN);
    if (currentLevel > currentMax)
    {
      currentMax = currentLevel;
    }
    delay(20);
  }
  lowPassTreshold = currentMax + TRESHOLD_CORRECTION_COEFICIENT;
  EEPROM.updateInt(12, lowPassTreshold);

}
