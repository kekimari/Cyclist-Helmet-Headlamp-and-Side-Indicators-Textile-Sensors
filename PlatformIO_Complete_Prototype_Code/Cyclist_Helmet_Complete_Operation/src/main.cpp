/* Macro Definitions */
#include <Arduino.h>
#include <pinDefinition_GlobalVariable.h>
#include <CapacitiveSensor.h>
#include <HeadLampAuto.h>
#include <AutoMode.h>
#include <IndicatorLeft.h>
#include <IndicatorRight.h>
#include <HeadLampManualOff.h>
#include <HeadLampManualOn.h>
#include <IndicatorRight.h>

 /*
 * ICACHE_RAM_ATTR is used to place the interrupt routines in the RAM 
 * when using Arduino platform
 */  
void ICACHE_RAM_ATTR rightSensor();
void ICACHE_RAM_ATTR leftSensor();
void ICACHE_RAM_ATTR headLampSensor();
void ICACHE_RAM_ATTR autoModeTest();

/* Setting up the send and receive pins for Capacitive sensing*/
CapacitiveSensor  Sensor = CapacitiveSensor(sendCapacitivePin,touchSensorAutoModeSet);
CapacitiveSensor  Sensor1 = CapacitiveSensor(sendCapacitivePin,touchSensorLeft);
CapacitiveSensor  Sensor3 = CapacitiveSensor(sendCapacitivePin,touchSensorRight);
CapacitiveSensor  Sensor2 = CapacitiveSensor(sendCapacitivePin,touchSensorHeadLamp);




void setup() {
  pinMode(rightLed, OUTPUT);
  pinMode(leftLed, OUTPUT);
  pinMode(headLampLed, OUTPUT);
  pinMode(touchSensorRight, INPUT);
  pinMode(touchSensorLeft, INPUT);
  pinMode(touchSensorHeadLamp, INPUT);
  pinMode(autoModePin, OUTPUT);
  pinMode(touchSensorAutoModeSet, INPUT);

  
  /* Assigning interrupt routines to the pin and the mode of triggering the interrupt */
  attachInterrupt(digitalPinToInterrupt(touchSensorRight), rightSensor, RISING);
  attachInterrupt(digitalPinToInterrupt(touchSensorLeft), leftSensor, RISING);
  attachInterrupt(digitalPinToInterrupt(touchSensorHeadLamp), headLampSensor, RISING);
  attachInterrupt(digitalPinToInterrupt(touchSensorAutoModeSet), autoModeTest, RISING);
  Serial.begin(115200);
}

void loop() 
{
  /*
   * @ AutomodeFunc - bool function, takes in 2 inputs, returns a bool value
   * ------------------ Inputs ----------------------------------------------------------------------------
   * @ autoModePin     - the auto mode LED pin Value  
   * @ autoModeState   - state of whether the system is automode or not, if 1, system in Automode
   * ------------------------------------------------------------------------------------------------------
   * ------------------ Output -----------------------------------------------------------------------------
   * @ return          - the state in which the system is
   * -------------------------------------------------------------------------------------------------------
   * This function computes whether to turn on or of the right or left LED 
   * based on the  rightState or leftState
   * rightState is toggled in the interrupt routine @ rightSensor
   * leftState is toggled in the interrupt routine @ leftSensor
   */

  /*Testing Notes this works and has been tested. The only issue is the debounce of the circuit 
  * I plan to put a cap parallel to the sense cap to stabilize it, decoupling as spoken in electronics
  * 
  */
  AutomodeOnOff = AutomodeFunc( autoModePin, autoModeState);
   

   if (AutomodeOnOff == 1)
    {
        /*
        * @ HeadLampAutoFunc     - void function, takes in three inputs, no return value
        * ------------------ Inputs ------------------------------------------------------------------------
        * @ ADC0                 - ADC pin Value
        * @ headLampLed          - HeadLamp pin Value 
        * --------------------------------------------------------------------------------------------------
        * This function computes whether to turn on or of the HeadLamp in Auto mode
        * based on a threshold value, > 670, returns True, < 40 returns False
        */

        /* Clear the manual headLampState value so if we exist Auto Mode we start at when the headlamp is off
        * and the user has to manually turn it on
        */

        headLampState = false; 
        headLampStateAutoMode = HeadLampAutoFunc(ADC0, headLampLed );
      }
   else if (AutomodeOnOff == 0) 
      {
        /*
        * @ headLampManualFunc      - void function, takes in two inputs, no return value
        * ------------------ Inputs ------------------------------------------------------------------------
        * @ headLampLed             - HeadLamp pin Value 
        * @ headLampState           - HeadLamp State
        * --------------------------------------------------------------------------------------------------
        * This function computes whether to turn on or of the HeadLamp in Manual mode
        * based on the headLampSate
        * HeadLampState is toggled in the interrupt routine @ headLampSensor
        */
       digitalWrite(autoModePin, LOW);
       if (headLampState == 1)
        {
            /*
            * @ headLampManualOnFunc  - void function, takes in one inputs, no return value
            * ------------------ Inputs ------------------------------------------------------------------------
            * @ headLampLed           - HeadLamp pin Value 
            * --------------------------------------------------------------------------------------------------
            * This function turns on the HeadLamp in Manual mode
            * based on the headLampSate
            * HeadLampState is toggled in the interrupt routine @ headLampSensor
            */
            headLampManualOnFunc(headLampLed);
        }
       else if (headLampState == 0)
        {
           /*
            * @ headLampManualOffFunc   - void function, takes in one inputs, no return value
            * ------------------ Inputs ------------------------------------------------------------------------
            * @ headLampLed             - HeadLamp pin Value 
            * --------------------------------------------------------------------------------------------------
            * This function turns off the HeadLamp in Manual mode
            * based on the headLampSate
            * HeadLampState is toggled in the interrupt routine @ headLampSensor
            */
            headLampManualOffFunc(headLampLed);
        }
      }
   
  if (rightState == 1) 
    {
      /*
      * @ IndicatorRightFunc    - void function, takes in two inputs,no return value
      * ------------------ Inputs ---------------------------------------------------------------------------
      * @ rightLed              - right LED pin Value 
      * @ blinkcount            - max value of how many times the LEDs can blink
      * ------------------------------------------------------------------------------------------------------
      * This function computes whether to turn on or of the right LED 
      * based on the  rightState 
      * rightState is toggled in the interrupt routine @ rightSensor
      */
      IndicatorRightFunc(rightLed,blinkcount);
    }

    else if (leftState == 1)
      {
      /*
      * @ IndicatorLeftFunc   - void function, takes in two inputs,no return value
      * ------------------ Inputs ---------------------------------------------------------------------------
      * @ leftLed             - left LED pin Value 
      * @ blinkcount          - max value of how many times the LEDs can blink
      * -----------------------------------------------------------------------------------------------------
      * This function computes whether to turn on or of the left LED 
      * based on the  leftState 
      * leftState is toggled in the interrupt routine @ leftSensor
      */
        IndicatorLeftFunc(leftLed,blinkcount);
      }
}

/* ************************************************************************* */
/* Interrupt Routines functions ISR's */
void rightSensor()
  {
    rightState = !rightState;  
    leftState = 0; 
    counter = 0;
  }
 void leftSensor()
  {
    leftState = !leftState; 
    rightState = 0; 
    counter = 0;
  }

 void headLampSensor()
  {
    headLampState = !headLampState;
  }

  void autoModeTest()
  {
    autoModeState = !autoModeState;
    Serial.println(autoModeState);   
  }
  /* ************************************************************************* */