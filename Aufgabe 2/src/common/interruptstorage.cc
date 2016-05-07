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


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \todo implement **/
InterruptStorage::InterruptStorage(){
  for(int i=0; i < 32; i++)
    mHandlers[i] = &mPanic;
}

void InterruptStorage::assign(int iNum, InterruptHandler& handler){
  mHandlers[iNum] = &handler;
}

void InterruptStorage::handle(int iNum){
  // if this is uncommented, the keyboard interrupt does not work.
  //mPanic.currentInterrupt(iNum);
  mHandlers[iNum]->trigger();
}

//bool InterruptStorage::currentInterrupt(int& iNum){
//  
//}