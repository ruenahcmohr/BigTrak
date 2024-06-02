
#include "events.h"


IOPin_t BEEPER = { 1, &PINB };

// for 16Mhz
void beep(uint8_t delay, uint8_t cycles) {
  while(cycles--) {
   Delay(delay*32);
   SetPin(BEEPER, 0);
   Delay(delay*32);
   SetPin(BEEPER, 1);
  }
}




void event_error() {
   beep(200, 45);
}

void event_cmdOK() {
   beep(20, 128);
}

void event_digitOK() {
   beep(16, 128);
}

/*
 // I would like a "command commited" diddy
  beep(20, 32);
  Delay(65535);
  beep(32, 128);

*/





    
