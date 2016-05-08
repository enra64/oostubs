/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"

CGA_Screen::CGA_Screen() : 
  screenBuffer(*reinterpret_cast<cga_element (*)[CGA_ROWS][CGA_COLS]>(CGA_ADDRESS)),
  ioIndex(0x3d4), ioData(0x3d5) {
  // set defaults
  this->defaultAttributes.bitfield.fgColor = (unsigned char) LIGHTGREY;
  this->defaultAttributes.bitfield.bgColor = (unsigned char) BLACK;
  this->defaultAttributes.bitfield.blink = 0;
  this->setpos(0,0);
}

CGA_Screen::~CGA_Screen(){
  this->print("OS ended.", 9);
}

void CGA_Screen::setpos (unsigned short x, unsigned short y) {
  // cursor offset
  unsigned short cursor = x + y * CGA_COLS;

  // lower byte
  this->ioIndex.outb(15);
  this->ioData.outb(cursor & 0xFF);

  // upper byte
  this->ioIndex.outb(14);
  this->ioData.outb((cursor >> 8) & 0xFF);
}

void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
  // cursor offset
  unsigned short cursor = 0;

  // lower byte
  this->ioIndex.outb(15);
  cursor |= this->ioData.inb();

  // upper byte
  this->ioIndex.outb(14);
  cursor |= this->ioData.inb() << 8;

  // calculate position from offset
  x = cursor % CGA_COLS;
  y = (cursor - x) / CGA_COLS;
}

void CGA_Screen::show (unsigned short x, unsigned short y, char character, unsigned char attribute) {
  // set character and attribute in video memory
  this->screenBuffer[y][x].character = character;
  this->screenBuffer[y][x].attribute.byte = attribute;
}

void CGA_Screen::print (const char* string, unsigned int n) {
  // position of screen where printing happens
  unsigned short x, y;
  // start to print from current cursor position
  getpos(x, y);

  // print each character in string
  for (unsigned int k = 0; k < n; ++k) {
    // handle newlines
    if (string[k] == '\n') {
      y++;
      x = 0;
    } else {
      // show current character
      this->show(x++, y, string[k], this->defaultAttributes.byte);
    }
    // handle line wrapping
    if (x == 80) {
      y++;
      x = 0;
    }
    // handle automatic screen scrollup
    if (y == 25) {
      this->setpos(x, y);
      this->scrollup();
    }
  }

  // update cursor position
  this->setpos(x, y);
}

void CGA_Screen::scrollup () {
  // position on screen
  unsigned short x, y;

  // move lines up
  for (x = 0; x < 80; ++x) {
    for (y = 0; y < 25 - 1; ++y) {
      this->screenBuffer[y][x] = this->screenBuffer[y + 1][x];
    }
  }

  // update cursor position
  getpos(x, y);
  if (y > 0) {
    y--;
  }
  setpos(x, y);
}

void CGA_Screen::clear () {
  // clear screen with spaces
  for (int x = 0; x < 80; ++x) {
    for (int y = 0; y < 25; ++y) {
      this->show(x, y, ' ', this->defaultAttributes.byte);
    }
  }
  // update cursor position
  setpos(0, 0);
}

void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  // update default attributes
  this->defaultAttributes.bitfield.fgColor = (unsigned char) fgColor;
  this->defaultAttributes.bitfield.bgColor = (unsigned char) bgColor;
  this->defaultAttributes.bitfield.blink = (unsigned char) blink;
}
