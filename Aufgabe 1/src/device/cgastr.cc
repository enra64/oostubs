/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S T R E A M                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "device/cgastr.h"

void CGA_Stream::flush () {
  // print everything currently in buffer
  print(buffer, pos);
  // reset buffer position
  pos = 0;
}

void CGA_Stream::setAttributes(int fgColor, int bgColor, bool blink){
  // call unto cga_screen to set the attributes  
  CGA_Screen::setAttributes(fgColor, bgColor, blink);
}
