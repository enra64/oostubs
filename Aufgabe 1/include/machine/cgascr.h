/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __screen_include__
#define __screen_include__

/* INCLUDES */

#include "machine/io_port.h"
#include "common/colors.h"

/* CLASSES */

/** \brief CGA-Dispaly driver
 *
 * CGA_Screen enables the basic control of the screen of a computer by accessing
 * the screen memory and I/O ports directly.
 */
class CGA_Screen {
  public:
    
    /** 
     * \brief Constructor
     *
     * Sets up memory mapping of CGA driver, sets default attribute for output and clears the screen.
     */
    CGA_Screen();
    
    /** 
     * \brief Destructor 
     *
     * Prints a warning that the os ended.
     */
    ~CGA_Screen();
    
    /** \brief set the cursor position
     *
     * @param x column number of new position 
     * @param y row number of new position
     */
    void setpos(unsigned short x, unsigned short y);
    
    /** \brief get the cursor position
     *
     * @param x reference for column number of current position
     * @param y reference for row number of current position
     */
    void getpos(unsigned short& x, unsigned short& y) const;
    
    /** \brief print a character to a specific position
     *
     * @param x column number of display position
     * @param y row number of display position
     * @param character character to be displayed
     * @param attribute display attributes
     */
    void show(unsigned short x, unsigned short y, char character, unsigned char attribute);
    
    /** 
     * \~german
     * \brief gibt eine Zeichenkette an der aktuellen Position aus
     * 
     * Als Attribute werden die hinterlegten, aktuellen, Standardwerte verwendet.
     * 
     * @param string 
     *    Zeichenkette, die ausgegeben werden soll
     * @param n 
     *    Anzahl an Zeichen, die von \c string ausgegeben werden soll
     * 
     * 
     * \~english
     * \brief print a string to the current position
     * 
     * @param string 
     *    string of characters to be displayed
     * @param n 
     *    number of characters in string
     */
    void print(const char* string, unsigned int n);
    
    /** 
     * \~german
     * \brief das aktuelle Display wird eine Zeile nach oben gescrollt
     *
     * Die so entstandene neue Zeile wird mit Leerzeichen aufgefüllt.
     * Die Attribute dafür sind die aktuellen Standardwerte.
     * 
     * \~english
     * \brief scroll the display one line upwards
     *
     * The new row at the bottom of the screen is filled with spaces. The default 
     * attributes are used.
     */
    void scrollup();
    
    /** 
     * \~german
     * \brief leert den aktuellen Bildschirm
     * 
     * Dabei werden alle Zeilen mit Leerzeichen gefüllt. Als Attribute werden die
     * in einer Variable hinterlegten, aktuellen Standardwerte verwendet.
     * 
     * \~english
     * \brief clear the screen 
     */
    void clear();
    
    /** 
     * \~german
     * \brief ändert die aktuellen Standardattribute
     * 
     * Diese aktuellen Standardattribute werden von den meisten Funktionen dieser Klasse 
     * beim Setzen der CGA-Attribute genutzt.
     * 
     * \param fgColor
     *    Vordergrundfarbe
     * 
     * \param bgColor
     *    Hintergrundfarbe
     * 
     * \param blink
     *    Soll der Text blinken? (true = blinken)
     * 
     * \~english
     * \brief changes the used default attribute values 
     * 
     * Most of the function uses these attribute values to determine which values the new printed
     * text should have.
     * 
     * \param fgColor
     *    foregorund color
     * 
     * \param bgColor
     *    backgorund color
     * 
     * \param blink
     *    indecates if the text should blink (true = should blink)
     */
    void setAttributes(int fgColor, int bgColor, bool blink);

private:
    const static unsigned char TERMINAL_HEIGHT = 25;
    const static unsigned char TERMINAL_WIDTH = 80;
    const static unsigned char CGA_BYTES_PER_CHAR = 2;
    const static unsigned char BYTES_PER_LINE = 
        TERMINAL_WIDTH * CGA_BYTES_PER_CHAR;
    const static unsigned short BYTES_PER_PAGE = 
        BYTES_PER_LINE * TERMINAL_HEIGHT;
    const static unsigned char CURSOR_POSITION_INDEX_HIGH = 14;
    const static unsigned char CURSOR_POSITION_INDEX_LOW = 15;
    const static unsigned long VIDEO_BASE_ADDR = 0xB8000;

    /** \brief storage field for the default attribute**/
    unsigned char default_attribute;

    /** \brief pointer to the regeneration buffer**/
    unsigned char* regen_buffer;
};

#endif
