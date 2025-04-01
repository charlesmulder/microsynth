#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

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
    
    






