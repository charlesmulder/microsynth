/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    IRCF0 = 1; // FOSC = 16MHz
    IRCF1 = 1;
    IRCF2 = 1;
    IRCF3 = 1;
    
    //SCS0 = 1;
    SCS1 = 1;

}
