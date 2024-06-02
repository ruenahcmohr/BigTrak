#include "progCore.h"


uint8_t progPtr;

inst_t prog[PROGSIZE+1];

/*
uint8_t writeProgMem(uint16_t address, uint8_t data) { // returns error if full
 if (address == PROGSIZE) return 0;
 prog[address] = data;
}

uint8_t readProgMem(uint16_t address, uint8_t * data) {// returns error if EOF
  if (address == PROGSIZE) return 0;
  *data = prog[address];
}
*/

//f/p/c/ROMCTRL/bigtrakFSM
uint8_t FSMLUT[]   = { 
 0x00, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x05, 0x06, 0x09, 0x0A, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x05, 0x06, 0x10, 0x10, 0x23, 0x23, 0x23,
 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
 0x20, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x05, 0x07, 0x08, 0x0A, 0x04, 0x04, 0x04,
 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x05, 0x06, 0x09, 0x0A, 0x30, 0x30, 0x30,
 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
 };

void IF_FSM(uint8_t E) {
  static uint8_t state = 0;  
  uint8_t EO, IP;  
  
  IP = (E & 0x1F) | (state << 5);
  state = FSMLUT[IP] >> 4;
  EO    = FSMLUT[IP] & 0x0F;
  
  switch (EO) {
    case ER_none        : event_error();                                   break;     
    case ER_incWriteCmd : progPtr++; proc_writeCmd( E );                   break;     
    case ER_writeCmd    : proc_writeCmd(     E );                          break;     
    case ER_writeParam1 : proc_writeparam1(  E - EV_0);                    break;     
    case ER_writeParam2 : proc_writeparam2(  E - EV_0);                    break;     
    case ER_clrProg     : event_cmdOK();   proc_clearmem();                break;     
    case ER_delLast     : event_cmdOK();   progPtr--;  proc_delCurr();     break;    
    case ER_delCurrent  : event_cmdOK();   proc_delCurr();                 break;    
    case ER_incExecLast : event_cmdOK();   progPtr++;  proc_testCmd();     break;                
    case ER_execLast    : event_cmdOK();   proc_testCmd();                 break;    
    case ER_run         : event_cmdOK();   proc_runProg();                 break;    
  }

}


void proc_writeCmd(uint8_t cmd) {
  if (progPtr == PROGSIZE) { IF_FSM(EV_memLock); return;  } 
  prog[progPtr].cmd = cmd;
  event_cmdOK();
}

void proc_writeparam1(uint8_t param) {
  prog[progPtr].val = param;
  event_digitOK();
}

void proc_writeparam2(uint8_t param) {
  prog[progPtr].val = (prog[progPtr].val*10) + param;
  progPtr++;
  event_digitOK();
}


// -- immediate user commands

void proc_clearmem() {
      
  for ( progPtr = 0; progPtr < PROGSIZE; progPtr++) 
    prog[progPtr].cmd = prog[progPtr].val = 0;
    
  progPtr = 0;  
}

void proc_delCurr() {
  prog[progPtr].cmd = 0;
  prog[progPtr].val = 0;
}


void proc_testCmd() {  
  if (progPtr == 0) { event_error();  return; }
  proc_doCmd( prog[progPtr-1].cmd,  prog[progPtr-1].val );  
}


void proc_doCmd(uint8_t cmd, uint8_t val) {

  switch (cmd) {  
    case Inst_fwd:     Fn_forward(val);   break;    
    case Inst_rev:     Fn_reverse(val);   break;    
    case Inst_left:    Fn_left(val);      break;  
    case Inst_right:   Fn_right(val);     break;  
    case Inst_pause:   Fn_pause(val);     break;     
    case Inst_party:   Fn_party(val);     break;     
    case Inst_acc:     Fn_acc(val);       break;           
  }
}



void proc_runProg() {
  uint8_t loopFlag = 0;
  
  for(progPtr = 0; prog[progPtr].cmd != Inst_none; progPtr++) {
  
    if(0) {
    } else if( prog[progPtr].cmd != Inst_repeat ) {
      proc_doCmd( prog[progPtr].cmd,  prog[progPtr].val );  
    } else if( prog[progPtr].cmd == Inst_repeat ) {
      if (loopFlag == 0) {
        progPtr -= Min( prog[progPtr].val, progPtr) ;
        loopFlag = 1;
      }
    }        
  }
    
}


