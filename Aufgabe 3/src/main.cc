/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         M A I N                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES */

#include "machine/multiboot.h"
#include "machine/cpu.h"
#include "device/interruptmanager.h"
#include "device/keyboard.h"
#include "device/cgastr.h"
#include "device/log.h"

/* MACROS */

/// \~german  festlegen, welche Aufgabenanwendung verwendet werden soll
/// \~english define which task is desired
#define USE_TASK           30

//load the necessary header and define the class name of the task
#if USE_TASK == 10
  #include "user/task1.h"
#elif USE_TASK == 20
  #include "user/task2.h"
#elif USE_TASK == 30
  #include "user/task3A.h"
  #include "user/task3B.h"
  #include "user/task3C.h"
#endif


/* GLOBAL OBJECTS */

InterruptManager iManager;
CGA_Stream kout;
Keyboard keyboard;
CPU cpu;
Log log;

/* METHODS  */

extern "C" void kernel(uint32_t magic, const Multiboot_Info* info);

/** \brief kernel entry point
 *
 * \param magic bootloader magic value
 * \param info address of multiboot info structure
 *
 * This is the entry point of the operating system.  If this function returns
 * all interrupts will be disabled and the cpu will be halted.
 * 
 **/
void kernel(uint32_t magic, const Multiboot_Info* info){
  
#if USE_TASK == 10
  Task1 task(magic, info);
  task.action();
#elif USE_TASK == 20
  Task2 task;
  task.action();
#elif USE_TASK == 30
  kout.clear();
  kout << "Please choose subtask A-C" << endl;
  Key k;
  do 
  {
    k=keyboard.key_hit();
  }
  while(!k.valid() || k.ascii() < 'A' || k.ascii() > 'C');

  if(k.ascii()=='A'){
    Task3A task;
    task.action();
  } else if(k.ascii() == 'B'){
    Task3B task;
    task.action();
  }
  else
  {
    Task3C task;
    task.action();
    kout<<"Task3 finished";
    while(1);
  }
#endif
  while(1);
}
