/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       T A S K 2                                               * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __task2_include__
#define __task2_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "user/appl.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * \brief Second test application
 *
 * This application test the functionality of the implemented interrupt system.
 * It prints the task identification and then repeatedly draws a line in an
 * endless loop.  Interrupts from the keyboard are printed onto the screen to a
 * fixed location. This should disturb the drawing of the line.
 **/

class Task2 : public Application{
  public:
    /** 
     * \brief Default constructor
     *
     * prints task information and enables interrupts
     **/
    Task2();
    
    /** 
     * \brief prints the line 
     */
    virtual void action();
};

#endif
