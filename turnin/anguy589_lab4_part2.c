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

enum IN_States {IN_SMStart, IN_Init, IN_WaitIN_Plus, IN_Minus, IN_Reset} IN_State;

void incrementC() {
    unsigned char tempA0 = PINA & 0x01;
    unsigned char tempA1 = PINA & 0x02;
    
    switch(IN_State) {
      case IN_SMStart:
        IN_State = IN_Init;
        break;
      case IN_Init:
        if(tempA0 && !tempA1){
          IN_State = IN_Plus;
        }
        else if(!tempA0 && tempA1) {
          IN_State = IN_Minus;
        }
        else if(tempA0 && tempA1) {
          IN_State = IN_Reset;
        }
        else {
          IN_State = IN_Wait;
        }
        break;
        case IN_Wait:
            if(tempA0 && tempA0) [
                IN_State = IN_Reset;    
            }
            else if(!tempA0 && !tempA) {
                 IN_State = IN_Init; //no chance of reset
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
        PORTC = 0x07;
        break;
     case IN_Init:
         break;
      case IN_Wait:
        break;
      case IN_Plus:
        if(PORTC < 9){
          PORTC++;
        }
        else {
            PORTC = 0x09; //stop at 9
        }
        break;
      case IN_Minus:
        if(PORTC > 0) {
          PORTC--;
        }
        else {
            PORTC = 0x00; //stop at 0
        }
        break;
      case IN_Reset:
        PORTC = 0x00;
        break;
      default:
        break;
    }

}

int main(void) {
  DDRA = 0x00; PORTA = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;


 
  while(1) {
   
    incrementC();
  
  }


  return 1;
}
