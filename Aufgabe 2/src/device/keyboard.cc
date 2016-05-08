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
#include "object/keyboard.h"
#include "machine/keyctrl.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

void Keyboard::plugin(){
    iManager.assign(33, *this);
}

void Keyboard::trigger(){
    Key k = keyboard.key_hit();
    unsigned short x,y;
    if(k.valid()){
      if(k.ctrl() && k.alt() && (((char)k) == 'q')){
        reboot();
      }
      kout.getpos(x, y);
      kout.setpos(KEYBOARD_X, KEYBOARD_Y);
      kout << k.ascii();
      kout.flush();
      kout.setpos(x, y);
    }
}
