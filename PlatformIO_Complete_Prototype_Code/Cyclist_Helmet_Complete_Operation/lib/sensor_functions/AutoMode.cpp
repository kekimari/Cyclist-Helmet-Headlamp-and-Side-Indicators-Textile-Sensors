#include <Arduino.h>
bool AutoState ;

bool AutomodeFunc(int pinValue, bool stateValue)
{
  if (stateValue == 1)
      {
        digitalWrite(pinValue, HIGH);
        AutoState = stateValue;
        
      }
  else if (stateValue == 0)
      {
        digitalWrite(pinValue, LOW);
        AutoState = stateValue;
      }

    return AutoState;
}