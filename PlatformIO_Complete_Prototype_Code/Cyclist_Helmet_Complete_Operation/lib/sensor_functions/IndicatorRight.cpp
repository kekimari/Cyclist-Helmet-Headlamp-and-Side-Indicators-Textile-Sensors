#include <Arduino.h>
extern int counter; 

void IndicatorRightFunc( int rightPinValue,int blinkcount )
{
    
    if ( counter < blinkcount)
    {
        digitalWrite(rightPinValue, HIGH);
        delay(600);
                    
        digitalWrite(rightPinValue, LOW);
        delay(600);
        counter++;
    }
}