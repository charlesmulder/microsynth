/**************************************************
 * 
 * File Name: midi.h
 * 
 * Description: MIDI lib
 * 
 * Programmer: Charles Mulder
 * 
 * Date: 07/12/2025
 * 
 * Version: 1.0.0
 * 
 *************************************************/

struct midiMessage {
    unsigned char statusByte;
    unsigned char dataBytes[2];
} channelVoiceMessage;

/**
 * Status Bytes
 */
unsigned char midiIsStatusByte( unsigned char byte );
unsigned char midiIsChannelVoiceMessage( unsigned char byte ); /* ignoring channel mode messages */
unsigned char midiIsSystemMessage( unsigned char byte );

/**
 * Data Bytes
 */
unsigned char midiIsDataByte( unsigned char byte ); 

/**
 * Channel Voice Messages
 */
unsigned char midiIsNoteOn( unsigned char byte );
unsigned char midiIsNoteOff( unsigned char byte );
unsigned char midiIsControlChange( unsigned char byte );
unsigned char midiIsProgramChange( unsigned char byte );
unsigned char midiGetChannelNumber( unsigned char statusByte );