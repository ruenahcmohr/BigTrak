#ifndef __events
#define __events

#include <stdint.h>
#include "avrcommon.h"
#include "nopDelay.h"
#include <avr/io.h>

extern IOPin_t BEEPER ;

void beep(uint8_t delay, uint8_t cycles);
void event_error  ( ) ;
void event_cmdOK  ( ) ;
void event_digitOK( ) ;
    




#endif
