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
#include "object/imanager.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

InterruptStorage::InterruptStorage(){
  for(int i=0; i < 48; i++)
    assign(i, mPanic);
}

void InterruptStorage::assign(int iNum, InterruptHandler& handler){
  mHandlers[iNum] = &handler;
}

void InterruptStorage::handle(int iNum){
  mCurrentInterrupt = iNum;
  mPanic.currentInterrupt(iNum);
  mHandlers[iNum]->trigger();
  iManager.ack(iNum);
  mCurrentInterrupt = -1;
}

bool InterruptStorage::currentInterrupt(int& iNum){
  if(mCurrentInterrupt == -1)
    return false;
  iNum = mCurrentInterrupt;
  return true;
}