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
}

void InterruptStorage::assign(int iNum, InterruptHandler& handler){
  mHandlers[iNum] = &handler;
}

void InterruptStorage::handle(int iNum){
  mPanic.currentInterrupt(iNum);
  mHandlers[iNum]->trigger();
}

//bool InterruptStorage::currentInterrupt(int& iNum){
//  
//}