/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       K E Y B O A R D                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "device/keyboard.h"
#include "object/imanager.h"
#include "object/kout.h"
#include "config.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

void Keyboard::plugin(){
  iManager.assign((int)PIC::keyboard, *this);
}

void Keyboard::trigger(){
  // fetch last key
  Key k=key_hit();
  if(k.valid()){
    // save last key
    this->last_key = k;

    // print key
    kout.setpos(KEYBOARD_X, KEYBOARD_Y);
    kout << k.ascii() << " (" << (unsigned int)k.scancode() << ")   ";
    kout.flush();

    // reboot on ctrl+alt+q
    if(k.ctrl() && k.alt() && k.ascii() == 'q') {
      reboot();
    }
   }
}

Key& Keyboard::get_key() {
  return this->last_key;
}
