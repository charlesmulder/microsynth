/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */


/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

extern unsigned char msgByte;
extern unsigned char framingError;
extern unsigned char overrunError;

unsigned char isSamplingInstant = 0;
unsigned char isMidiMessageReceived = 0;

void __interrupt() isr(void)
{
    
    /**
    * PIR1: PERIPHERAL INTERRUPT REQUEST (FLAG) REGISTER 1 pg.105
    */
    if( RCIF == 1) {     
       isMidiMessageReceived = 1;
       framingError = RCSTAbits.FERR; /* NB read before RCREG */
       overrunError = RCSTAbits.OERR; 
       msgByte = RCREG;

    } else if( TMR0IF == 1 ) {
        isSamplingInstant = 1;
        TMR0IF = 0; /* clear interrupt flag*/
        TMR0 = 120; /* 256-136 => fs = 29400 Hz */   
    }
   

#if 0
    
    /* TODO Add interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if(<Interrupt Flag 1>)
    {
        <Interrupt Flag 1=0>; /* Clear Interrupt Flag 1 */
    }
    else if (<Interrupt Flag 2>)
    {
        <Interrupt Flag 2=0>; /* Clear Interrupt Flag 2 */
    }
    else
    {
        /* Unhandled interrupts */
    }

#endif

}
#endif


