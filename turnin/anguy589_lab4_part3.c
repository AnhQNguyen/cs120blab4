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

enum CL_States { CL_SMStart, CL_Wait, CL_C1, CL_C2, CL_C3, CL_Open, CL_Lock} CL_State;
unsigned char tempA0 = 0x00;
unsigned char tempA1 = 0x00;
unsigned char tempA2 = 0x00;
unsigned char tempA7 = 0x00;
unsigned char tempB0 = 0x00;

void comboLock() {

tempA0 = PINA & 0x01;
tempA1 = PINA & 0x02;
tempA2 = PINA & 0x04;
tempA7 = PINA & 0x80;

  switch(CL_State) {
    case CL_SMStart:
      CL_State = CL_Wait;
      break;
    case CL_Wait:
      if(tempA7){
        CL_State = CL_Lock;
      }
      else if (tempA2) {
        CL_State = CL_C1;
      }
      else {
        CL_State = CL_Wait;
      }
      break;
    case CL_C1:
      if(tempA7) {
        CL_State = CL_Lock;
      }
      else if(!tempA2) {
        CL_State = CL_C1;
      }
      else{
        CL_State = CL_Wait;
      }
      break;
    case CL_C2:
      if(tempA7) {

        CL_State = CL_Lock;
      }
      else if(tempA1) {
        CL_State = CL_C3;
      }
      else {
          CL_State = CL_Wait;
      }

      break;
    case CL_C3:
      if(tempA7) {
        CL_State = CL_Lock;
      }
      else if(!tempA1) {
        CL_State = CL_Open;
      }
      else {
        CL_State = CL_Wait;
      }
      break;

    case CL_Open:
      if(tempA7) {
        CL_State = CL_Lock;
      }
      else {
        CL_State = CL_Open;
      }

      break;
    case CL_Lock:
      CL_State = CL_Wait;

      break;
    default:
      break;
  }



  switch(CL_State) {
      case CL_SMStart:
        break;
      case CL_Wait:
        PORTB = 0x00;
        break;
      case CL_C1:
        break;
      case CL_C2:
        break;
      case CL_C3:
        break;
      case CL_Open:
        PORTB = 0x01;
        break;
      case CL_Lock:
        PORTB = 0x00;
        break;
      default:
        break;
  }



}






int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;





    CL_State = CL_SMStart;

    while(1) {
      comboLock();
    }

    return 1;

}

