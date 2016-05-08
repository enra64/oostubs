/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                               I N T E R R U P T _ S T O R A G E                               * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "common/interruptstorage.h"
#include "object/kout.h"
#include "object/cpu.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

InterruptStorage::InterruptStorage(){
  for(int i=0; i < 48; i++)
    assign(i, mPanic);
  mKeyboardHandlerAssigned = false;
}

void InterruptStorage::assign(int iNum, InterruptHandler& handler){
  mHandlers[iNum] = &handler;
  if(iNum == 33)
    mKeyboardHandlerAssigned = true;
}

void InterruptStorage::handle(int iNum){
  
  if(iNum == 33 && !mKeyboardHandlerAssigned)
    return;
  mPanic.currentInterrupt(iNum);
  mHandlers[iNum]->trigger();
}

//bool InterruptStorage::currentInterrupt(int& iNum){
//  
//}