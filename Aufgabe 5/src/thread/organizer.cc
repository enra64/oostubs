#include "thread/organizer.h"
#include "object/lock.h"
#include "locking/scopedLock.h"
#include "common/null.h"
#include "object/log.h"

void Organizer::block(Waitingroom& room){
    room.push_back(*active());
    active()->waiting_in(&room);
    log << "Suspending Thread " << active() << endl;
    next();
}
 
void Organizer::wakeup(Customer& that){
    // remove customer from waiting room
    that.waiting_in()->remove(that);
    // reactivate via scheduler (add to queue)
    Scheduler::reactivate(that);
    log << "Reactivating Thread " << &that << endl;
}

bool Organizer::kill(Customer& that){
   // remove from waiting room
   that.waiting_in()->remove(that);
   // kill self
   return Scheduler::kill(that);
}

Customer* Organizer::active() const{
    return static_cast<Customer*>(Scheduler::active());
}
