/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/o_stream.h"

O_Stream::O_Stream() : Stringbuffer(), fgColor(WHITE), bgColor(BLACK), blink(false), base(dec){
  // nothing to do
}

O_Stream::~O_Stream(){
  // nothing to do
}

O_Stream& O_Stream::operator << (char value) {
  put(value);
  return *this;
}

O_Stream& O_Stream::operator << (unsigned char value) {
  return *this << (char)value;
}

O_Stream& O_Stream::operator << (char* value) {
  return *this << (const char*)value;
}

O_Stream& O_Stream::operator << (const char* value) {
  // put C string
  // dereference iteratively increasing pointer
  // until termination char 0 is reached
  while(*value != 0) {
    put(*value);
    ++value;
  }
  return *this;
}

O_Stream& O_Stream::operator << (short value) {
  return *this << (long)value;
}

O_Stream& O_Stream::operator << (unsigned short value) {
  return *this << (unsigned long)value;
}


O_Stream& O_Stream::operator << (int value) {
  return *this << (long)value;
}


O_Stream& O_Stream::operator << (unsigned int value) {
  return *this << (unsigned long)value;

}

O_Stream& O_Stream::operator << (long value) {
  if(value < 0) {
    put('-');
    value *= -1;
  }
  return *this << (unsigned long) value;
}

O_Stream& O_Stream::operator << (unsigned long value) {
  // allocate buffer to build the string of the number
  char buf[32];
  int i = 0;
  int digit;
  do {
    // cut digit from value and advance to next digit
    digit = value % base;
    value /= base;
    // put the corresponding character in the buffer
    if(digit < 10) {
      buf[i++] = digit + '0';
    } else {
      buf[i++] = digit - 10 + 'A';
    }
    // repeat while not all digits are processed
  } while (value > 0);

  // put prefix to indicate base
  switch (base) {
    case 2:  // 0b...
      put('0');
      put('b');
      break;
    case 8:  // 0...
      put('0');
      break;
    case 10: // no prefix
      break;
    case 16: //0x...
      put('0');
      put('x');
      break;
  }

  // write the string of the number
  while(i>0) {
    put(buf[--i]);
  }
  return *this;
}

O_Stream& O_Stream::operator << (void* value) {
  return *this << (unsigned long) value;
}

O_Stream& O_Stream::operator << (FGColor color){
  flush();
  fgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}


O_Stream& O_Stream::operator << (BGColor color){
  flush();
  bgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}


O_Stream& O_Stream::operator << (Blink blink){
  flush();
  this->blink = blink.blink;
  setAttributes(fgColor, bgColor, this->blink);
  return *this;
}

O_Stream& endl (O_Stream& os) {
  os.put('\n');
  os.flush();
  return os;
}


O_Stream& bin (O_Stream& os) {
  os.base = O_Stream::bin;
  return os;
}


O_Stream& oct (O_Stream& os) {
  os.base = O_Stream::oct;
  return os;
}


O_Stream& dec (O_Stream& os) {
  os.base = O_Stream::dec;
  return os;
}


O_Stream& hex (O_Stream& os) {
  os.base = O_Stream::hex;
  return os;
}

O_Stream& O_Stream::operator << (O_Stream& (*f) (O_Stream&)) {
  return f(*this);
}
