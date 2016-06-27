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
#include "object/log.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */
Keyboard::Keyboard() : sem(0){

}

void Keyboard::plugin(){
  iManager.assign(InterruptManager::keyboard, *this);
}

void Keyboard::trigger(){
  k = key_hit();
  if(k.valid()){
    // reboot on ctrl+alt+q
    if(k.ctrl() && k.alt() && k.ascii() == 'q') {
      reboot();
    } else {
      sem.interrupt_signal();
    }
  }
}

Key Keyboard::getkey(){
    log << "Thread stored in Waitingroom " << endl;
    sem.wait();
    return k;
}
