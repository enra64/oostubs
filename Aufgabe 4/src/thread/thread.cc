/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         T H R E A D                                           *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   INCLUDES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/thread.h"
#include "object/lock.h"
#include "object/scheduler.h"
#include "object/log.h"
/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   METHODS                       #
\* * * * * * * * * * * * * * * * * * * * * * * * */

void Thread::kickoff(Thread* thread){
  log << "thread::start" << endl;
  
  // unlock after the scheduler locked
  // for dispatching/context switching 
  lock.unlock();
  
  // execute action
  thread->action();
  
  // exit after executing the action
  thread->exit();
}

Thread::Thread() : context(this){}

Thread::~Thread(){
    exit();
}

void Thread::yield(){
  log << "thread::yield" << endl;
  scheduler.yield();
}

void Thread::exit(){
  log << "thread::exit" << endl;
  scheduler.exit();
}
