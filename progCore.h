#ifndef __progCore
#define __progCore

#include <stdint.h>
#include "events.h"
#include "functions.h"
#include "avrcommon.h"



#define PROGSIZE 64


   
// program instructions match order with FSMIP_e
typedef enum Instructions_e {
    Inst_none = 0,
    Inst_fwd,
    Inst_rev,
    Inst_left,
    Inst_right,
    Inst_pause,
    Inst_acc,
    Inst_party,
    Inst_repeat    
    
} Instrustions_t;   
   
   
// FSM event inputs  if these are changed, the FSM needs to be recompiled.
typedef enum FSMIP_e {
   EV_none   = 0,
   
   EV_forward   , //  program commands
   EV_reverse   ,
   EV_left      ,
   EV_right     ,
   EV_pause     ,
   EV_acc       ,
   EV_party     ,
   EV_repeat    ,
      
   EV_clearMem  , // immediate commands
   EV_delCmd    ,
   EV_check     ,
   EV_go        ,
   
   EV_0         , // values
   EV_1         ,
   EV_2         ,
   EV_3         ,
   EV_4         ,
   EV_5         ,
   EV_6         ,
   EV_7         ,
   EV_8         ,
   EV_9         ,
   
   EV_memLock   ,
   
   EV_LAST
   
} FSMIP_t;
   
// FSM event outputs   if these are changed, the FSM needs to be recompiled.
typedef enum FSMOP_e {

  ER_none         = 0,
  ER_incWriteCmd     ,
  ER_writeCmd        ,
  ER_writeParam1     ,
  ER_writeParam2     ,
  ER_clrProg         ,
  ER_delLast         ,
  ER_delCurrent      ,
  ER_incExecLast     ,
  ER_execLast        ,
  ER_run             ,
  

  ER_LAST

} FSMOP_t;   
   
   


   

typedef struct inst_s {
   uint8_t cmd;
   uint8_t val;
} inst_t;

extern inst_t   prog[PROGSIZE+1];
extern uint8_t  progPtr;

void proc_writeCmd    ( uint8_t cmd) ;
void proc_writeparam1 ( uint8_t param) ;
void proc_writeparam2 ( uint8_t param) ;


void IF_FSM           ( uint8_t key) ;
void proc_clearmem    ( ) ;
void proc_delCurr     ( ) ; 
void proc_testCmd     ( ) ;
void proc_doCmd       ( uint8_t cmd, uint8_t param) ;
void proc_runProg     ( ) ;



#endif




























