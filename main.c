/*

avr @ 16Mhz
9600 baud


on pro mini:

0   rxd   
1   txd   

2   pd2   
3   pd3    <--- IR 


4   pd4    
5   pd5   
6   pd6    
7   pd7    

8   pb0    
9   pb1    <-- beeper
10  pb2    


11  pb4
12  pb3
13  pb5 (LED)


A0  pc0    left motor dir
A1  pc1    left motor enable
A2  pc2    right motor dir
A3  pc3    right motor enable

A4  pc4    
A5  pc5    


A6  adc6
A7  adc7



*/
#include <avr/io.h>
#include "usart.h"
#include "hiComms2.h"
#include <avr/interrupt.h>
#include "avrcommon.h"
#include "IR.h"
#include "progCore.h"
#include "events.h"
#include "main.h"

#define OUTPUT  1
#define INPUT   0

void keySubmit(uint8_t k) ;


int main( void ) {
 
  uint8_t code;
 
    // set up directions 
  DDRB = (INPUT << PB0 | OUTPUT << PB1 | INPUT << PB2 |INPUT << PB3 |INPUT << PB4 |OUTPUT << PB5 |INPUT << PB6 |INPUT << PB7);
  DDRD = (INPUT << PD0 | INPUT << PD1 | INPUT << PD2 |INPUT << PD3 |INPUT << PD4 |INPUT << PD5 |INPUT << PD6 |INPUT << PD7);        
  DDRC = (OUTPUT << PC0 | OUTPUT << PC1 |OUTPUT << PC2 |OUTPUT << PC3 |INPUT << PD4 |INPUT << PD5 |INPUT << PD6 |INPUT << PD7); 

  PORTD = 0xFF; // pullups on

  Fn_stop();  // stop motors!
//  USART_Init( 103 ); // 9600 baud
  USART_Init( 51 );    // 19200 baud   
   
  TimerInit();
  Int1Init();
  IRStatus = 0;
  sei();
         
  USART_printstring("Hello terminal.\r");  
  
  while(1) {     
     
     if (IRStatus) {
       code = IRData;
       IRStatus = 0;
       
       keySubmit(code);
             
     }
     
  } 
 
    
}


void keySubmit(uint8_t k) {


    switch(k) {
      case Key_forward  : IF_FSM( EV_forward ) ;  break;
      case Key_reverse  : IF_FSM( EV_reverse ) ;  break;
      case Key_left     : IF_FSM( EV_left    ) ;  break;
      case Key_right    : IF_FSM( EV_right   ) ;  break;
      case Key_pause    : IF_FSM( EV_pause   ) ;  break;
      case Key_acc      : IF_FSM( EV_acc     ) ;  break;
      case Key_party    : IF_FSM( EV_party   ) ;  break;
      case Key_repeat   : IF_FSM( EV_repeat  ) ;  break;
      case Key_clearMem : IF_FSM( EV_clearMem) ;  break;
      case Key_delCmd   : IF_FSM( EV_delCmd  ) ;  break;
      case Key_check    : IF_FSM( EV_check   ) ;  break;
      case Key_go       : IF_FSM( EV_go      ) ;  break;
      case Key_0        : IF_FSM( EV_0       ) ;  break;
      case Key_1        : IF_FSM( EV_1       ) ;  break;
      case Key_2        : IF_FSM( EV_2       ) ;  break;
      case Key_3        : IF_FSM( EV_3       ) ;  break;
      case Key_4        : IF_FSM( EV_4       ) ;  break;
      case Key_5        : IF_FSM( EV_5       ) ;  break;
      case Key_6        : IF_FSM( EV_6       ) ;  break;
      case Key_7        : IF_FSM( EV_7       ) ;  break;
      case Key_8        : IF_FSM( EV_8       ) ;  break;
      case Key_9        : IF_FSM( EV_9       ) ;  break;
      default           : event_error(       ) ;  break; 
    }

}















