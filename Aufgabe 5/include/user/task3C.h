/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                      T A S K 3 A                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __task3C_include__
#define __task3C_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "user/appl.h"
#include <stdint.h>
/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** \brief Third test application, part 3
 *
 * This application represents possibly malicious code an attacker could insert
 * into our system.
 * It should print "Decimal: 100 hexadecimal: 0x64", instead it writes something 
 * to your framebuffer
 **/
class Task3C : public Application{
    
  public:
    
    /** \brief Default constructor
     *
     * 
     **/
    Task3C();
    
    /** \brief Destructor
     *
     * 
     **/
    virtual ~Task3C();
    
    /** \brief main part of the class **/
    virtual void action();
};

#endif
