/**************************************************
 * 
 * File Name: wavetable.h
 * 
 * Description: Wave table library header file
 * 
 * Programmer: Charles Mulder
 * 
 * Date: 23/02/2025
 * 
 * Version: 1.0.0
 * 
 *************************************************/
unsigned char wavetableGetSamplingIncrement( unsigned char noteNumber );
unsigned char wavetableGetSquareSample( unsigned int phase );
unsigned char wavetableGetSineSample( unsigned int phase );
unsigned char wavetableGetSawtoothSample( unsigned int phase );