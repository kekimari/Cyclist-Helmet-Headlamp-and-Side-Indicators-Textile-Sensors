#include <Arduino.h>
#define touchSensorRight 5              /* Capactive Sensor Right - D1 on ESP8266*/
#define rightLed 10                      /* RED INDICATOR - TX on ESP8266 - changed to 9*/
#define touchSensorLeft 14              /* Capactive Sensor Left - D5 on ESP8266*/
#define leftLed 15                      /* LEFT INDICATOR - D8 on ESP8266 */
#define touchSensorHeadLamp 13          /* Capactive Sensor HeadLamp - D7 on ESP8266*/
#define headLampLed 2                   /* HEADLAMP - D4 on ESP8266 */
#define autoModePin 0                   /* RED LED INDICATOR FOR AUTOMODE, autoMode=1 if activated - D3 on ESP8266 */
#define touchSensorAutoModeSet 12       /* Capactive Sensor AutoMode - D6 on ESP8266*/
#define sendCapacitivePin 4             /* The pin sending the signal to charge the Capacitive Sensors - D2 on ESP8266*/
#define ADC0 A0                         /* ADC pin - A0 on ESP8266*/
#define blinkcount 10                   /* The number of time the right and left LED indicators will blink if not interrupted */


/* 
  * counter, variable to incremment the counter for the number of times the LEDs blink 
  * adc_value, variable to hold the ADC value and used to determine whether to turn on the HeadLamp
*/

int counter = 0 ; 
int adc_value = 0; 
long val = 0;

/* 
* variables to keep state of the various modes of operations 
*/
volatile static boolean rightState = false;
volatile static boolean leftState = false;
volatile static boolean headLampState = false;
volatile static boolean autoModeState = false;
volatile static boolean headLampStateAutoMode = false;
bool AutomodeOnOff = false; 