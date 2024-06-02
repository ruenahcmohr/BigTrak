

typedef enum KeyPad_e {
   Key_none      = 0xFF,
   
   Key_forward   = 0x08, //  program commands
   Key_reverse   = 0x88,
   Key_left      = 0x48,
   Key_right     = 0xC8,
   Key_pause     = 0xA2,
   Key_acc       = 0xB0, // OPEN-CLOSE
   Key_party     = 0xB8, // PBC
   Key_repeat    = 0x18, // REPEAT
   
   
   Key_clearMem  = 0x92, // PROG immediate commands
   Key_delCmd    = 0x02, // REV
   Key_check     = 0x72, // STEP
   Key_go        = 0x58, // PLAY
   
   Key_0         = 0xD0, // values
   Key_1         = 0x00,
   Key_2         = 0x80,
   Key_3         = 0x40,
   Key_4         = 0xC0,
   Key_5         = 0x20,
   Key_6         = 0xA0,
   Key_7         = 0x60,
   Key_8         = 0xE0,
   Key_9         = 0x10,
   
   Key_stop      = 0x32
   
} KeyPad_t;
