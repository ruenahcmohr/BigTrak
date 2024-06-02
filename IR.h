#ifndef __irh
#define __irh

  #include<avr/io.h>
  #include <avr/interrupt.h>
  #include "avrcommon.h"

  #define IRDet                    3

  #define TimerReset()             TCNT1 = 0

  #define IRH()                    IsHigh(IRDet, PIND)
  #define IRL()                    IsLow(IRDet, PIND)


  void OnEdge();
  void TimerInit();
  void Int1Init();

  volatile unsigned int  IRData;

  // IR Data Ready set if byte is available in buffer, user clears.
  #define IRDR            7
  volatile unsigned char IRStatus;

#endif
