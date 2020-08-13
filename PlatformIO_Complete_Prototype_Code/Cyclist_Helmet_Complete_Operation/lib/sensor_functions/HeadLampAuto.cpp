#include <Arduino.h>
bool manualStateClear; 

bool HeadLampAutoFunc( int adcpinValue, int headLightpinValue)
{
  int adc_value; 
  adc_value = analogRead(adcpinValue);
  delay(600);
  
  if (adc_value > 670 ) 
    {
      digitalWrite(headLightpinValue, HIGH);
    }

  else if (adc_value < 420 )
    {
      digitalWrite(headLightpinValue, LOW);
    }
    return manualStateClear = false;
}