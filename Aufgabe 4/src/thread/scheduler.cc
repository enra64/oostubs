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
    mQueueSize--;
    log << "scheduler::started" << ", queue:" << mQueueSize << endl;
    Dispatcher::start(*firstThread);
  }
  else
    log << "scheduler: no thread for start"<< ", queue:" << mQueueSize  << endl;
}

void Scheduler::next()
{
  Thread* next = static_cast<Thread*>(threads.pop_front());
  mQueueSize--;
  log << "scheduler::Next thread"<< ", queue:" << mQueueSize  << endl;
  if(!next){
    log << "scheduler::No more threads, finished!"<< ", queue:" << mQueueSize  << endl;
    cpu.halt();
  }
  Dispatcher::dispatch(*next);
}

void Scheduler::insert(Thread& that){
  threads.push_back(that);
  mQueueSize++;
  log << "scheduler::insert" << ", queue:" << mQueueSize << endl;
}

void Scheduler::exit(){
  next();
  log << "scheduler::exit"<< ", queue:" << mQueueSize  << endl;
  if(threads.empty()){
      log << "halt" << endl;
      cpu.halt();
  }
}

bool Scheduler::kill(Thread& that){
  bool removed = threads.remove(that);
  if(removed)
    mQueueSize--;
  log << "scheduler::kill" << ", queue:" << mQueueSize << endl;
  return removed;
}

void Scheduler::yield(){
  threads.push_back(*active());
  mQueueSize++;
  log << "scheduler::yield" << ", queue:" << mQueueSize << endl;
  next();
}

void Scheduler::preempt(){
  // todo
}
