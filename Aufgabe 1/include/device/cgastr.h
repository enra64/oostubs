/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                   C G A _ S T R E A M                                         *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __cgastr_include__
#define __cgastr_include__

#include "common/o_stream.h"
#include "machine/cgascr.h"

/** 
 * \~german
 * \brief CGA basierte Ausgabe, ählich zu std::cout von C++
 * 
 * CGA_Stream ermöglicht die Ausgabe verschiedener Daten als Zeichenkette über den CGA-Modus der
 * Grafikkarte. Die Klasse ist sowohl von \ref CGA_Screen und \ref O_Stream abgeleitet. Dadurch
 * sind weitere Ausgabeformate und Effekte möglich.
 * 
 * \~english
 * \brief CGA based output mechanism, similar to cout
 *
 * CGA_Stream enables the output of different data as string using the CGA 
 * screen. It is derived from the class CGA_Screen which makes additional 
 * formats and effects available.
 * CGA_Stream extends the functionality of the classes CGA_Screen and O_Stream.
 */
class CGA_Stream  : public O_Stream, public CGA_Screen {
  public:
    /** 
     * \~german
     * \brief ausgeben des Inhaltes des internen Puffers
     * 
     * Diese Funktion wird automatisch aufgerufen, sobald der Puffer voll ist oder eine 
     * "neue Zeile" als Zeichen zum Puffer hinzugefügt werden soll.
     * 
     * \~english
     * \brief flush the content of the internal buffer
     *
     * It is called automaticaly as soon as the buffer is full or if a newline is
     * encountered.
     **/
    virtual void flush();
    
    /**
     * \~german
     * \brief verbindet die setAttributes-Funktion von O_Stream mit dem CGA-Treiber
     * 
     * \~english
     * \brief combine the setAttributes function of O_Stream with the presented interface of the
     *        CGA driver
     */
    virtual void setAttributes(int fgColor, int bgColor, bool blink);
    
};

#endif
