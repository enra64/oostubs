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

PIC::PIC() : ctrl_1(0x20), ctrl_2(0xa0), mask_1(0x21), mask_2(0xa1) {
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
  
  mask_1.outb(0xFB); // Tell the Master PIC to ignore every interrupt except the interrupt connected to PIC2
  mask_2.outb(0xFF); // Tell the Slave PIC to ignore every interrupt

  // globally enable interrupts
  cpu.enable_int();
}

PIC::~PIC(){
  // globally disable interrupts
  cpu.disable_int();
}

void PIC::allow(Interrupts interrupt){
  // interrupt offset
  int i = interrupt - timer;

  // determine which the responsible pic
  IO_Port *port;
  if( i < 8 ) {
    port = &mask_1;
  } else {
    i -= 8;
    port = &mask_2;
  }

  // get mask from pic
  unsigned char mask = port->inb();

  // allow interrupt by deleting the corresponding bit in the mask
  mask &= 0xff ^ (1 << i);

  // apply updated mask
  port->outb(mask);
}

void PIC::forbid(Interrupts interrupt){
  // interrupt offset
  int i = interrupt - timer;

  // determine which the responsible pic
  IO_Port *port;
  if( i < 8 ) {
    port = &mask_1;
  } else {
    i -= 8;
    port = &mask_2;
  }

  // get mask from pic
  unsigned char mask = port->inb();

  // forbid interrupt by setting the corresponding bit in the mask
  mask |= (1 << i);

  // apply updated mask
  port->outb(mask);
}

void PIC::ack(Interrupts interrupt){
  // master pic always needs an ack
  ctrl_1.outb(0x20);

  // if pic2 is responsible for interrupt, it also needs an ack
  if( interrupt - timer >= 8 ) {
    ctrl_2.outb(0x20);
  }
}
