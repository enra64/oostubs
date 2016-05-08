/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/pic.h"
#include "machine/io_port.h"
#include "object/cpu.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \todo extend - enabling global interrupt after pic configuration **/
PIC::PIC() {
  IO_Port ctrl_1(0x20), ctrl_2(0xa0), mask_1(0x21), mask_2(0xa1);
  // http://wiki.osdev.org/8259_PIC#Initialisation
  //
  // When you enter protected mode (or even before hand, if you're not using GRUB) the
  // first command you will need to give the two PICs is the initialise command (code 0x11).
  // This command makes the PIC wait for 3 extra "initialisation words" on the data port.
  // These bytes give the PIC:
  //  - Its vector offset. (ICW2)
  //  - Tell it how it is wired to master/slaves. (ICW3)
  //  - Gives additional information about the environment. (ICW4)

  ctrl_1.outb(0x11); // starts the initialization sequence (in cascade mode)
  ctrl_2.outb(0x11);
  
  mask_1.outb(32);   // ICW2: Master PIC vector offset
  mask_2.outb(40);   // ICW2: Slave PIC vector offset
  
  mask_1.outb(4);    // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  mask_2.outb(2);    // ICW3: tell Slave PIC its cascade identity (0000 0010)
  
  mask_1.outb(3);    // ICW4: tell Master PIC that we are in 8086/88 Mode (bit 0 == 1) and Automatic EOI (bit 1 == 1)
  mask_2.outb(3);    // ICW4: tell Master PIC that we are in 8086/88 Mode (bit 0 == 1) and Automatic EOI (bit 1 == 1)

  // save the masks in ram to avoid IO access
  mMaskMaster = 0xFB;
  mMaskSlave = 0xFF;
  
  mask_1.outb(mMaskMaster); // Tell the Master PIC to ignore every interrupt except the interrupt connected to PIC2
  mask_2.outb(mMaskSlave); // Tell the Slave PIC to ignore every interrupt

  // ToDo: your code goes here
  // set global interrupt enable flag
  cpu.enable_int();
}

/** \todo implement **/
PIC::~PIC(){
  // clear global interrupt enable flag
  cpu.disable_int();
}

/** \todo implement **/
void PIC::allow(Interrupts interrupt){
  // the first eight interrupts are on the master pic
  bool isMaster = interrupt < 40;
  
  // get appropriate io_port
  IO_Port maskPort(isMaster ? 0x21 : 0xa1);
  
  if(isMaster)
    mMaskMaster &= ~(1 << (interrupt - 32));
  else
    mMaskSlave &= ~(1 << (interrupt - 40));

  // update pic masks
  maskPort.outb(isMaster ? mMaskMaster : mMaskSlave);
}

/** \todo implement **/
void PIC::forbid(Interrupts interrupt){
  // the first eight interrupts are on the master pic
  bool isMaster = interrupt < 40;
  
  // get appropriate io_port
  IO_Port maskPort(isMaster ? 0x21 : 0xa1);
  
  // update saved masks  
  if(isMaster)
    mMaskMaster |= (1 << (interrupt - 32));
  else
    mMaskSlave |= (1 << (interrupt - 40));

  // update pic masks
  maskPort.outb(isMaster ? mMaskMaster : mMaskSlave);
}

void PIC::ack(Interrupts interrupt){
  // get appropriate io_port
  IO_Port maskPort(interrupt < 40 ? 0x20 : 0xa0);
  maskPort.outb(0x20);
}
