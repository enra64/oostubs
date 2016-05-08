/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S T R I N G B U F F E R                                       *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/strbuf.h"

Stringbuffer::Stringbuffer(){
  /* Empty */
}
Stringbuffer::~Stringbuffer(){
  /* Empty */
}
void Stringbuffer::put (char c) {
  // store character and advance position
  this->buffer[this->pos++] = c;

  // flush when buffer is full
  if(pos == BUFFERSIZE) {
    this->flush();
  }
}
