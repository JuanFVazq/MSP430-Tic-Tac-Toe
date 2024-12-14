/** \file lcddraw.h
 *  \brief Adapted from RobG's EduKit
 */

#ifndef lcddraw_included
#define lcddraw_included

/** Draw single pixel at col, row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR);

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, u_int colorBGR);

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR);

/** Draw character using 5x7 font
 *
 *  \param col Column to start drawing character
 *  \param row Row to start drawing character
 *  \param c Character to draw
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawChar5x7(u_char col, u_char row, char c, u_int fgColorBGR, u_int bgColorBGR);

/** Draw string using 5x7 font
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string to draw
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		   u_int fgColorBGR, u_int bgColorBGR);

/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR);

/** Draw character using 11x16 font
 *
 *  \param col Column to start drawing character
 *  \param row Row to start drawing character
 *  \param c Character to draw
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawChar11x16(u_char col, u_char row, char c, u_int fgColorBGR, u_int bgColorBGR);

/** Draw string using 11x16 font
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string to draw
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString11x16(u_char col, u_char row, char *string, u_int fgColorBGR, u_int bgColorBGR);

#endif // included
