/*	Author: anguy589
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.*/

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum IN_States {IN_SMStart, IN_Wait, IN_Plus, IN_Minus, IN_Reset} IN_State;
unsigned char tempC = 0x00;


void incrementC() {
    switch(IN_State) {
      case IN_SMStart:
        break;
      case IN_Wait:
        if(PINA == 0x01){
          IN_State = IN_Plus;
        }
        else if(PINA == 0x02) {
          IN_State = IN_Minus;
        }
        else if(PINA == 0x03) {
          IN_State = IN_Reset;
        }
        else {
          IN_State = IN_Wait;
        }
        break;
      case IN_Plus:
        IN_State = IN_Wait;
        break;
      case IN_Minus:
        IN_State = IN_Wait;
        break;
      case IN_Reset:
        IN_State = IN_Wait;
        break;
        default:
          break;
    }



    switch(IN_State) {
      case IN_SMStart:
        break;
      case IN_Wait:
        break;
      case IN_Plus:
        if(tempC < 9){
          tempC++;
        }
        break;
      case IN_Minus:
        if(tempC > 0) {
          tempC--;
        }
        break;
      case IN_Reset:
        tempC = 0;
        break;
      default:
        break;
    }

}

int main(void) {
  DDRA = 0x00; PORTA = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;


    
  while(1) {
    tempC = 7;
    incrementC();
    PORTC =  tempC;
  }


  return 1;
}
