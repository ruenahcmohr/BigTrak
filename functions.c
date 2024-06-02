
#include "functions.h"


  IOPin_t LIGHT      = { 5, &PINB };
  
  IOPin_t MotorL_EN  = { 1, &PINC };
  IOPin_t MotorL_DIR = { 0, &PINC };
  
  IOPin_t MotorR_EN  = { 3, &PINC };
  IOPin_t MotorR_DIR = { 2, &PINC };  
  
  
void Fn_stop() {
   SetPin(MotorR_EN, 0);
   SetPin(MotorL_EN, 0);
          
   SetPin(MotorR_DIR, 0);
   SetPin(MotorL_DIR, 0); 
}  
  
void Fn_forward(uint8_t n) { // forward one robot length
  
  for (; n; n--){
    SetPin(MotorR_DIR, 0); 
    SetPin(MotorL_DIR, 1); 
    SetPin(MotorR_EN, 1);     
    SetPin(MotorL_EN, 1);
    //Delay(2600000); // one rev
    Delay(1290000);
    SetPin(MotorR_EN, 0);     
    SetPin(MotorL_EN, 0);  
  }  
  
}

void Fn_reverse(uint8_t n) { // back one robot length

  for (; n; n--){
    SetPin(MotorR_DIR, 1); 
    SetPin(MotorL_DIR, 0); 
    SetPin(MotorR_EN, 1);     
    SetPin(MotorL_EN, 1);
    //Delay(2600000); // one rev
    Delay(1290000);
    SetPin(MotorR_EN, 0);     
    SetPin(MotorL_EN, 0);  
  }
  
}

void Fn_left(uint8_t n) { // turn 3 degrees left

  for (; n; n--){
    SetPin(MotorR_DIR, 0); 
    SetPin(MotorL_DIR, 0); 
    SetPin(MotorR_EN, 1);     
    SetPin(MotorL_EN, 1);
    Delay(66667);
    SetPin(MotorR_EN, 0);     
    SetPin(MotorL_EN, 0);
  }
  
}  

void Fn_right(uint8_t n) { // turn 3 degrees right

  for (; n; n--){
    SetPin(MotorR_DIR, 1); 
    SetPin(MotorL_DIR, 1); 
    SetPin(MotorR_EN, 1);     
    SetPin(MotorL_EN, 1);
    Delay(66667);
    SetPin(MotorR_EN, 0);     
    SetPin(MotorL_EN, 0);
  }
  
}

void Fn_pause(uint8_t param) { // pause 1/10 of a second
  Delay(225000*param);
}


void Fn_party(uint8_t param) { // aux fn 1

  int melody[] = {
    NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
    NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
    NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
    NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
  };

  int durations[] = {
    8, 8, 8, 4, 4, 4, 
    4, 5, 8, 8, 8, 8, 
    8, 8, 8, 4, 4, 4, 
    4, 5, 8, 8, 8, 8
  };
  
  int thisNote;

  int songLength = sizeof(melody)/sizeof(melody[0]);

  for ( thisNote = 0; thisNote < songLength; thisNote++){
    beep( melody[thisNote], durations[thisNote]*20);
  }
}


void Fn_acc(uint8_t param) { // aux fn 2, acccessory activate
  uint8_t i;
    
  for( i = 0; i < 4; i++) {
    SetPin(LIGHT, 1);
    Delay(32768*4);
    SetPin(LIGHT, 0);
    Delay(32768*4);
  }
}


