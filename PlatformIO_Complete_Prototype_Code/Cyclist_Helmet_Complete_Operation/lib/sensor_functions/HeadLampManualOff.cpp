#include <Arduino.h>

void headLampManualOffFunc( int pinValue)
{
    digitalWrite(pinValue, LOW);
}