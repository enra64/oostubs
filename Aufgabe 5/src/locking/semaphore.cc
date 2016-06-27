#include "locking/semaphore.h"
#include "object/scheduler.h"
#include "object/lock.h"
#include "locking/scopedLock.h"

Semaphore::Semaphore(unsigned int value) : value(value){
}

void Semaphore::p(){
  ScopedLock scopedLock(lock);
	if(value==0) {
		scheduler.block(*this);
	} else {
		value--;
	}
}

void Semaphore::v(){
  // call organizer to wake up thread/customer
  ScopedLock sc(lock);

  if(empty())
    value++;
  else
    scheduler.wakeup(*static_cast<Customer*>(pop_front()));
}

void  Semaphore::interrupt_signal(){
  // try to wake up
  signal();
}
