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

unsigned char midiIsStatusByte( unsigned char byte ) {
    return byte >= 0x80 && byte <= 0xFF;
}

unsigned char midiIsChannelVoiceMessage( unsigned char byte ) {
    return byte >= 0x80 && byte <= 0xEF;
}

unsigned char midiIsSystemMessage( unsigned char byte ) {
    return byte >= 0xF0 && byte <= 0xFF;
}

unsigned char midiIsDataByte( unsigned char byte ) {
    return byte >= 0x00 && byte <= 0x7F;
}

unsigned char midiIsNoteOn( unsigned char byte ) {
    return byte >= 0x90 && byte <= 0x9F;
}

unsigned char midiIsNoteOff( unsigned char byte ) {
    return byte >= 0x80 && byte <= 0x8F;           
}

unsigned char midiIsProgramChange( unsigned char byte ) {
    return byte >= 0xC0 && byte <= 0xCF;
}

unsigned char midiGetChannelNumber( unsigned char statusByte ) {
    /* only keep 2nd nibble, which is the channel number */
    return statusByte & 0x0F;
}

