/******************************************************************************
 Title:    Code for an IR reciever 
 
 made for a SONY RM-D505 remote,
 tiny26 running at 1Mhz,
 
 0           1ms       8-10   counts
         Barrier at 14
 1           2.5ms     18-19 counts
         Barrier at 28 
 start bit   5ms       37-38 counts

 
 Author:   rue_mohr
 Date:     Jan 8-14 2006
 Software: AVR-GCC 3.3 
 Hardware: attiny26
 
 ******************************************************************************
 
 New Hardware M32 at 6Mhz
 IO on D3 (int 1)
 
  0           0.5ms       12   counts
         Barrier at 18
 1           1ms          23 counts
         Barrier at 41
 start bit   2.5ms       58 counts
 
    
*******************************************************************************/
#include"IR.h"

/*
int main (void)  {
 
      
  TimerInit();   // initialize timer    
  Int0Init();    // initialize int0  
  sei();         // turn on interrupts
  
  SetBit(IRDet, PORTB);            // sets pullup on IR reciever
                  
  while(1) {      
     if (IsHigh(IRDR, IRStatus)) { // when the flag gets set
       if (IRData == 0x0AD1) { SetBit(2, PORTA); }
       if (IRData == 0x0831) { ClearBit(2, PORTA); }
       ClearBit(IRDR, IRStatus);   // this is to ack the byte was read
     }
  }
}
    */
//------------------------| FUNCTIONS |------------------------


//------| Timerc Functions |--------

void TimerInit() { //8 bit timer, set up 10Khz  (15.625Khz)
// tho it dosn't have to be a 8 bit timer, it dosn't matter really
// as long as all the diodes down my left side hurt, nothing really matters.
// robot with a brain the size of a planet, and they have me writing c code, pathetic.

  TCCR1B = (1<<CS10)|(1<<CS12);  // 16MHz / 1024  !!!PROCESSOR!!!!
  TimerReset();
}

void Int1Init() {

  EICRA = (1<<ISC10);  // trigger interrupt on any edge !!!PROCESSOR!!!!
  SetBit(INT1, EIMSK); // enable the interrupt !!!PROCESSOR!!!!
  
}

ISR (INT1_vect) { 
  if (IRH()) {  // bit just went high, reset timer    
    TimerReset();  // start timing          
  } else {      // bit just went low, check value of time   
    OnEdge();
  }
}

#define STARTTHRES 40
#define HIGHTHRES  17


void  OnEdge() {
  volatile static unsigned      BitCount;
  volatile static unsigned int  IRRecReg;
  unsigned int         count;  
  
  count = TCNT1;   // snap shot of timer0 !!!PROCESSOR!!!!
  
  if (0) {
  } else if (count > STARTTHRES) {    // 4.5ms     
      BitCount = 0;  // clear reciever register counter
      IRRecReg = 0;
  } else if (count > HIGHTHRES) {    // 1.64 pulse = 1     
      IRRecReg <<= 1;   
      IRRecReg |= 0x01;  // no this is not an error, dont ask!
      BitCount++; 
  } else {                    // 0.5ms pulse = 0  
      IRRecReg <<= 1;
      BitCount++;
  } 
  
  // set to recieve 8 bits
  if (BitCount == 32){    
     if ((~IRRecReg & 0xFF) == (IRRecReg >> 8)) { // error checking
       IRData = IRRecReg >> 8;     
       SetBit(IRDR, IRStatus); // set data ready flag
     }
  }
  
}


