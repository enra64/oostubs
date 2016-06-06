/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         S C H E D U L E R                                     *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   INCLUDES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/scheduler.h"
#include "locking/scopedLock.h"
#include "object/lock.h"
#include "object/kout.h"
#include "object/log.h"
#include "object/cpu.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   METHODS                       #
\* * * * * * * * * * * * * * * * * * * * * * * * */

Scheduler::Scheduler() : started(false){}

Scheduler::~Scheduler(){
  started = false;
}

void Scheduler::start(){
  if(!threads.empty()){
    started = true;
    Thread* firstThread = static_cast<Thread*>(threads.pop_front());
    Dispatcher::start(*firstThread);
  }
}

void Scheduler::insert(Thread& that){
  threads.push_back(that);
}

void Scheduler::next()
{

  Thread* next = static_cast<Thread*>(threads.pop_front());
  if(!next){
    log << "No more threads, finished!" << endl;
    cpu.halt();
  }
  dispatch(*next);
}

void Scheduler::exit(){
  return;
  kill(*active());
  threads.pop_front();
  next();
}

bool Scheduler::kill(Thread& that){
  if(&that == active())
      return false;
  return threads.remove(that);
}

void Scheduler::yield(){
  threads.push_back(*active());
  next();
}

void Scheduler::preempt(){
  // todo
}
