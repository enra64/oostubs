/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S T R I N G B U F F E R                                       *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/strbuf.h"

Stringbuffer::Stringbuffer(){
  pos = 0;
  for(unsigned int i = 0; i < BUFFERSIZE; i++){
    buffer[i] = 0;
  }
}

Stringbuffer::~Stringbuffer(){
}

void Stringbuffer::put (char c) {
  buffer[pos++] = c;
  if(pos >= BUFFERSIZE - 1)
    flush();
}
