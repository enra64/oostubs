/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"
#include "machine/io_port.h"





CGA_Screen::CGA_Screen(){
  // set the pointer to the starting position of the regeneration
  // buffer
  regen_buffer = (unsigned char*) VIDEO_BASE_ADDR;
  setAttributes(0x2, 0x1, true);
}

CGA_Screen::~CGA_Screen(){
  // currently, we dont need to destroy anything, since we didnt
  // allocate any memory
}

// set the cursor position
void CGA_Screen::setpos (unsigned short x, unsigned short y) {
  // check whether the input is legit  
  if(x < TERMINAL_WIDTH && y < TERMINAL_HEIGHT){
    // get IOPort access
    IO_Port index_reg_cga(0x3D4);
    IO_Port data_reg_cga(0x3D5);

    // calculate offset
    unsigned short offset = x + (y * TERMINAL_WIDTH);

    unsigned char lowByte = offset & 0xFF;
    unsigned char highByte = (offset >> 8) & 0xFF;

    // write index register for high byte
    index_reg_cga.outb(CURSOR_POSITION_INDEX_HIGH);
    // write new cursor high byte
    data_reg_cga.outb(highByte);

    // write index register for high byte
    index_reg_cga.outb(CURSOR_POSITION_INDEX_LOW);
    // write new cursor high byte
    data_reg_cga.outb(lowByte);
  }
}

void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
  // get IOPort access
  IO_Port index_reg_cga(0x3D4);
  IO_Port data_reg_cga(0x3D5);

  // write index register for high byte
  index_reg_cga.outb(CURSOR_POSITION_INDEX_HIGH);
  // read high byte
  unsigned char high_byte = data_reg_cga.inb();
  
  // write index register for low byte    
  index_reg_cga.outb(CURSOR_POSITION_INDEX_LOW);
  // read low byte
  unsigned char low_byte = data_reg_cga.inb();

  // create short from high and low byte
  unsigned short offset = low_byte | (high_byte << 8);

  x = offset % TERMINAL_WIDTH;
  y = offset / TERMINAL_WIDTH; 
}

void CGA_Screen::show (unsigned short x, unsigned short y, char character, unsigned char attribute) {
  // kk is this shit valid
  if(x < TERMINAL_WIDTH && y < TERMINAL_HEIGHT){
    // get pointer to regen buffer
    char* buf = (char*) VIDEO_BASE_ADDR;    

    // calculate the byte position
    unsigned short pos = CGA_BYTES_PER_CHAR*((y*TERMINAL_WIDTH) + x);
    
    // write out to buffer
    buf[pos] = character;
    buf[pos + 1] = attribute;
  }
}

void CGA_Screen::print (const char* string, unsigned int n) {
  // get current cursor position
  unsigned short ccx;// Current Cursor X
  unsigned short ccy;// Current Cursor Y

  getpos(ccx, ccy);

  // "show" each character - extreme performance mode
  for(unsigned int i = 0; i < n; i++){
    // if the character is a newline, increase the line at x=0
    if(string[i] == '\n'){
      setpos(0, ccy + 1);
    } 
    // not a newline - show char, increase position, update
    // variables
    else {
      // show character
      show(ccx, ccy, string[i], default_attribute);
      // increase cursor position
      setpos(++ccx, ccy);
      // update cursor position in case of changes in y
      getpos(ccx, ccy);
    }
  }
}

void CGA_Screen::scrollup () {
  // copy values from the next line to each line  
  for(unsigned char y = 0; y < TERMINAL_HEIGHT - 1; y++){
    for(unsigned char x = 0; x < TERMINAL_WIDTH; x++){
      regen_buffer[y * BYTES_PER_LINE + x] = 
        regen_buffer[y * (BYTES_PER_LINE + 1) + x];
    }
  }
  // clear lowest line
  for(unsigned short x = 0; x < TERMINAL_WIDTH; x++){
    regen_buffer[(TERMINAL_HEIGHT -1) * BYTES_PER_LINE + x] = 0;
  }
}

void CGA_Screen::clear () {
  for(unsigned int i = 0; i < BYTES_PER_PAGE; i++){
    regen_buffer[i] = 0;
  }
  
  setpos(0, 0);
}

void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  // cap & shift values
  fgColor = (fgColor & 0b00001111);
  bgColor = ((bgColor & 0b00000111) << 4);
  default_attribute = 0;
  // handle blink values
  if(blink)
    default_attribute = (1 << 7);
  // OR into the default attribute
  default_attribute =(char)(bgColor | fgColor);
}
