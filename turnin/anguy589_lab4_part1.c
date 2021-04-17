/*	Author: anguy589
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SL_States {SL_SMStart, SL_Wait, SL_S1, SL_S2} SL_State;
unsigned char tempA0 = 0x00;

void switchLights() {
   tempA0 = PINA & 0x01;

    switch(SL_State) {
      case SL_SMStart:
        SL_State = SL_Wait;
        break;
      case SL_Wait:
        if(tempA0) {
          SL_State = SL_S1;
        }
        else {
          SL_State = SL_Wait;
        }
        break;
      case SL_S1:
        if(!tempA0) {
          SL_State = SL_S1; //"staying that way after button release"
        }
        else {
          SL_State = SL_S2;
        }
        break;
      case SL_S2:
        if(!tempA0) {
          SL_State = SL_S2;
        }
        else {
          SL_State = SL_S1;
        }
        break;
      default:
        break;
    }

    switch(SL_State) {
      case SL_SMStart:
        break;
      case SL_Wait:
        PORTB = 0x01;
        break;
      case SL_S1:
        PORTB = 0x01;
        break;
      case SL_S2:
        PORTB = 0x02;
        break;
      default:
        break;
    }

}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    SL_State = SL_SMStart;

    while(1) {
      switchLights();
    }

    return 1;

}
