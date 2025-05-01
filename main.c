/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "midi.h"
#include "led.h"
#include "wavetable.h"

/* Sampling */
extern unsigned char isSamplingInstant;

/* MIDI */
extern unsigned char isMidiMessageReceived;
unsigned char midiNote, midiVelocity, midiChannel, framingError, overrunError, msgByteCounter, msgByte = 0;
struct midiMessage channelVoiceMessage = {0};

/* Wavetables */
unsigned int N = 4096; /* wave table length */
unsigned int fs = 29400; /* audio sampling rate */
unsigned int phase = 0; /* index of the current wavetable iteration */
unsigned int samplingIncrement = 0; /* amount to increment the phase by */

/**
 * see https://microcontrollerslab.com/dac-module-pic-microcontroller-mplab-xc8-programming/
 */
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    while (1) {

        if( isMidiMessageReceived == 1) {

            if( framingError == 1) {
                ledYellowOn();
            } else {
                framingError = 0; /* reset framing error */
                ledYellowOff();
            }

            if( overrunError == 1 ) {
                ledRedOn();
            } else {
                ledRedOff();
            }

            /**
            * We can't assume that msgByte is a data byte when it isn't a status byte
            * because status byte could not yet be set.
            */
           if( midiIsStatusByte( msgByte ) ) {
              channelVoiceMessage.statusByte = msgByte;
              midiChannel = midiGetChannelNumber( msgByte );
              isMidiMessageReceived = 0;
              msgByteCounter = 0;

           }

           /**
            * For each Status byte the correct number of Data bytes must
            * always be sent. Inside a receiver, action on the message should wait
            * until all Data bytes required under the current status are received.
            */
           if ( midiIsDataByte( msgByte ) && channelVoiceMessage.statusByte != 0 ) {

               if( msgByteCounter < 2 ) {
                   channelVoiceMessage.dataBytes[msgByteCounter] = msgByte;
                   isMidiMessageReceived = 0;
                   msgByteCounter++;
               }
               /**
                * Set the sampling increment once per complete data byte instead
                * of once each sampling instant.
                */
               if( msgByteCounter == 2 ) {

                   midiNote = channelVoiceMessage.dataBytes[0];
                   midiVelocity = channelVoiceMessage.dataBytes[1]; /* @todo */

                   if( midiIsNoteOn( channelVoiceMessage.statusByte ) ) {
                       samplingIncrement = wavetableGetSamplingIncrement( midiNote );
                       ledGreenOn();
                   }

                   /**
                    * For running status, when two notes are held down, the
                    * released note, may not be sounding anymore, in which case,
                    * we want to continue playing the unreleased note.
                    */
                   if( midiIsNoteOff( channelVoiceMessage.statusByte ) &&
						wavetableGetSamplingIncrement( midiNote ) == samplingIncrement ) {
                       samplingIncrement = 0;
                       ledGreenOff();
                   }

                   /**
                    * To handle running status.
                    * When a 2nd note is pressed without releasing the first note,
                    * then a new status byte is not sent meaning we should
                    * use the value of the previous status byte.
                    */
                   msgByteCounter = 0;
               }

           }
        }

        /** 
         * Sounding a note is independent of receiving midi messages 
         * as we are sounding to the sampling rate 
         */
        if( isSamplingInstant == 1) {
            isSamplingInstant = 0;

            if( samplingIncrement > 0 ) {

                switch( midiChannel ) {

                    /* sawtooth */
                    case 1:
                        DAC1CON1bits.DAC1R = wavetableGetSawtoothSample(phase);
                        break;

                    /* square */
                    case 2:
                        DAC1CON1bits.DAC1R = wavetableGetSquareSample(phase);
                        break;

                    /* sine */
                    default:
                        DAC1CON1bits.DAC1R = wavetableGetSineSample(phase);

                }

                phase += samplingIncrement;

                if (phase > N-1) {
                    phase = 0;
                }
            }
        }
    }

}

