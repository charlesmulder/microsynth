/**************************************************
 * 
 * File Name: led.c
 * 
 * Description: LED status indicator library file
 * 
 * Programmer: Charles Mulder
 * 
 * Date: 23/02/2025
 * 
 * Version: 1.0.0
 * 
 *************************************************/
#define GREEN_LED PORTBbits.RB2
#define YELLOW_LED PORTBbits.RB1
#define RED_LED PORTBbits.RB0

void ledRedToggle(void) {
    RED_LED = ~RED_LED;
}

void ledYellowToggle(void) {
    YELLOW_LED = ~YELLOW_LED;
}

void ledGreenToggle(void) {
    GREEN_LED = ~GREEN_LED;
}

void ledRedOn(void) {
    RED_LED = 0;
}

void ledGreenOn(void) {
    GREEN_LED = 0;
}

void ledYellowOn(void) {
    YELLOW_LED = 0;
}

void ledRedOff(void) {
    RED_LED = 1;
}

void ledGreenOff(void) {
    GREEN_LED = 1;
}

void ledYellowOff(void) {
    YELLOW_LED = 1;
}

void ledAllOff(void) {
    ledRedOff();
    ledGreenOff();
    ledYellowOff();
}

void ledAllOn() {
    ledRedOn();
    ledGreenOn();
    ledYellowOn();
}
    
    






