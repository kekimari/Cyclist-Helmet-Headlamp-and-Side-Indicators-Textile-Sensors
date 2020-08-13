#include <Arduino.h>
extern int counter; 

void IndicatorLeftFunc( int leftPinValue,int blinkcount )
{
    
    if ( counter < blinkcount)
    {
        digitalWrite(leftPinValue, HIGH);
        delay(600);
                    
        digitalWrite(leftPinValue, LOW);
        delay(600);
        counter++;
    }
}


   