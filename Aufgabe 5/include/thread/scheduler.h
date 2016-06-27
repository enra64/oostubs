/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __schedule_include__
#define __schedule_include__

#include "thread/dispatch.h"
#include "common/queue.h"
#include "device/watch.h"

class Thread;

/**
 * \~english
 * \brief Basic Scheduler
 *  
 * This class represent a simple FIFO-Scheduler. It holds a list of the
 * currently available threads. Through the \ref Scheduler::yield method it
 * can issue a context switch to another ready thread. The resulting context
 * switch may also switch to the same thread if the ready list is empty.
 *
 **/
class Scheduler : protected Dispatcher {
private:
  /** \brief Queue of threads that are ready to be processed **/
    Queue threads;

  /** \brief flag set upon start of scheduler **/
    bool started;

  /**
   * \~english
   * \brief Idle Thread
   *
   * This thread is running when no other thread is available.
   *
   **/

  class Idle : public Thread{
    /** \brief Halts the CPU, waiting for interrupts **/
    virtual void action();
  } idle;


public:
  /** \brief Default Constructor clearing started flag **/
  Scheduler();

  /** \brief Default Destructor clearing started flag **/
  ~Scheduler();

  /** \brief Start the scheduling by starting the first thread
   **/ 
	void start();
  
  /** \brief Insert the specified thread into the queue
   *
   * of threads that are ready to be processed.
   *
   * @param that reference to the thread to be inserted
   **/
  void insert(Thread& that);

  /** \brief Remove the currently active thread from the queue
   *
   * of thread and resumes with the next thread. If there are no
   * more threads the scheduler starts an idle loop.
   **/
  void exit();

  /** \brief Yield to another ready thread **/
  void yield();

  /** \brief Returns pointer to active thread **/
  Thread* active() const;

protected:
  /** \brief helper function stop the execution of the current thread and switch to next one
   *
   *  This helper function unifies the scheduling of the next thread
   **/
  void next();

  /** \brief Reactivates an unblocked thread by reinserting it to the thread queue.
   *
   * @param unblocked thread to be reactivated
   **/
  void reactivate(Thread& unblocked);

  /** \brief Remove the specified thread from the queue of threads, killing the execution of this thread.
   *
   * @param that reference of the thread to be killed.
   * @returns whether operation was successful
   */
  bool kill(Thread& that);

private:
  /** \brief helper function to yield unguarded to another thread
   *
   *  This helper function is used by watch to preempt the currently running thread.
   **/
  void preempt();

  friend void Watch::trigger();
};

#endif
