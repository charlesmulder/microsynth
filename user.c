/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"
#include "led.h"
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

#define _XTAL_FREQ 16000000

static void initLedIndicators(void) {
    /**
     * LED status indicators
     */
    TRISB0 = 0; /* red output */
    TRISB1 = 0; /* yellow output */
    TRISB2 = 0; /* green output */
    ANSB0 = 0; /* digital */
    ANSB1 = 0; /* digital */
    ANSB2 = 0; /* digital */
    
    ledAllOff();
    ledAllOn();
    __delay_ms(200);
    ledAllOff();
    __delay_ms(200);
    ledAllOn();
    __delay_ms(200);
    ledAllOff();
    __delay_ms(200);
    ledAllOn();
    __delay_ms(200);
    ledAllOff();

}

static void initMidiIn(void) {
    RXPPSbits.RXPPS = 0x17; /* Set EUSART RX pin to RC7 0b10111*/
       
    /**
     * MIDI input
     */
    TRISC7 = 1; /* set PORTC5 as input */
    ANSC7 = 0; /* set PORTC5 as digital */
    
    /**
     * EUSART BAUD rate
     */
    SYNC = 0; /* Asynchronous mode */
    BRGH = 0;
    BRG16 = 0;
    SPBRGH = 0;
    //SPBRGL = 25; /* for Proteus simulation using COMPIN */
    SPBRGL = 7; /* for MIDI hardware */
    SPEN = 1; /* Serial Port Enable */ 
    CREN = 1; /* Continuous Receive Enable bit */
    RCIE = 1; /* Enable EUSART receive interrupt */ 
    PEIE = 1; /* Enable peripheral interrupts */
    
}

static void initDac(void) {
    /**
     * DAC
     */
    DAC1EN = 1; /* enable DAC */
    
    DAC1OE1 = 1; /* enable DAC1 output on DAC1OUT1 pin */
    DAC1OE2 = 0; /* disable DAC2 output on DAC1OUT2 pin */
    DAC1CON0bits.DAC1PSS = 0; /* set DAC1 positive source = VDD*/
    DAC1CON0bits.DAC1NSS = 0; /* set DAC1 negative source = VSS*/
      
    TRISA2 = 0;
    ANSA2 = 1;  
    
    LATA2 = 0; /* NB! */
  
    
}

static void initSampling(void) {
    /**
     * Timer0
     * Used to simulate sampling rate (fs) 44100
     * @note When TMR0 is written, the increment is inhibited for two instruction cycles immediately following the write
     */
    TMR0CS = 0; /* set clock source = FOSC/4 */
    PSA = 1; /* disable prescaler */
    
    /**
     * Interrupt flag bits are set when an interrupt
        condition occurs, regardless of the state of
        its corresponding enable bit or the Global
        Enable bit, GIE, of the INTCON register.
        User software should ensure the
        appropriate interrupt flag bits are clear
        prior to enabling an interrupt.
     */
    
    TMR0IF = 0;
    
    /**
     * Calculations indicate a sampling rate of 44100 requires TMR0 = 167
     * However, middle C sounds like A below middle C
     * TMR0 = 185 sounds like middle C, but we are adjusting the sampling rate
     */
    TMR0 = 120; /* 256-136 => fs = 29400 Hz */ 
    
    TMR0IE = 1; /* enable interrupt */
    GIE = 1; /* Enable global interrupts */
}

void InitApp(void)
{
    initLedIndicators();
    
    initMidiIn();
    
    initDac();

    initSampling();
            
}

