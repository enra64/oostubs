/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/o_stream.h"

O_Stream::O_Stream() : Stringbuffer(), fgColor(WHITE), bgColor(BLACK), blink(false), base(dec){
}

O_Stream::~O_Stream(){
}

O_Stream& O_Stream::operator << (char value) {
  put(value);
  return *this;
}

O_Stream& O_Stream::operator << (unsigned char value) {
  return *this << (char)value;
}

O_Stream& O_Stream::operator << (char* value) {
  // put all chars in value to the stringbuffer  
  while(*value != '\0'){
    put(*value);
    value++;
  }
  return *this;
}

O_Stream& O_Stream::operator << (const char* value) {
  // put all chars in value to the stringbuffer  
  while(*value != '\0'){
    put(*value);
    value++;
  }
  return *this;
}

void O_Stream::writeIntoBuffer(unsigned long value){
  if(value < base){
    // whatever the base, if the digit is < 10 we can use this
    if(value < 10)
      put((char)(value + '0'));
    //digit may be A-F, and 55 + 10 = 'A'
    else
      put((char)(55 + value));
  }
  else{
    writeIntoBuffer(value / base);
    writeIntoBuffer(value % base);
  }
}

void O_Stream::printBasePrefix(){
    switch(base){
        case bin:
          *this << '0' << 'b';
          break;
        case oct:// wtf is this the prefix for oct??
          *this << '0';
          break;
        case hex:
          *this << '0' << 'x';
          break;
        case dec:        
        default:
          return;
    }
}

O_Stream& O_Stream::operator << (unsigned long value) {
  printBasePrefix();
  writeIntoBuffer(value);
  return *this;
}

O_Stream& O_Stream::operator << (long value) {
  // negative value?
  if(value < 0){
    // prepend minus sign
    put('-');
    // make positive    
    value *= -1;
  }
  *this << ((unsigned long) value);
  return *this;;
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

O_Stream& O_Stream::operator << (void* value) {
  Base prev_base = base;
  base = hex;
  *this << ((unsigned long) value);
  base = prev_base;
  return *this;
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
  // heavy magic
  os << '\n';
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
