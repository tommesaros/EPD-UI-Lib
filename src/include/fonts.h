/**
 * @file fonts.h
 * @brief Header file containing font definitions and utility functions for EPD-UI-Lib.
 * 
 * This file defines various fonts used in EPD-UI-Lib and provides utility functions for working with fonts.
 * It also includes instructions on how to include new fonts and how to use them in the code.
 */

#ifndef FONTS_H
#define FONTS_H

/*******************************************************************
 * This file defines various fonts used in EPD-UI-Lib and provides 
 * utility functions for working with fonts.
 * 
 * How to include new font?
 * The conversion is done by a utility tool available on Lilygo’s GitHub repository.
 * See the documentation in the readme file:
 * https://github.com/Xinyuan-LilyGO/LilyGo-EPD47/blob/esp32s3/scripts/fontconvert.py
 * 
 * How to use the font in the code?
 * 1) Use one of the predefined constants: 
 *      HEADLINE_FONT for , 
 *      TITLE_FONT for , 
 *      TEXT_FONT_BOLD for , 
 *      TEXT_FONT for .
 * 2) Use the getFont function to get the OpenSans 
 *    font based on the size and boldness.
 * 3) Use the raw font data in the code.
 *      const GFXfont *font = (GFXfont *)&FontName;   or
 *      writeln(GFXfont *)&FontName, "Text", &x, &y, framebuffer);
 *******************************************************************/

#include "../../font/opensans6.h"
#include "../../font/opensans8.h"
#include "../../font/opensans8b.h"
#include "../../font/opensans9.h"
#include "../../font/opensans9b.h"
#include "../../font/opensans10.h"
#include "../../font/opensans10b.h"
#include "../../font/opensans11.h"
#include "../../font/opensans11b.h"
#include "../../font/opensans12.h"
#include "../../font/opensans12b.h"
#include "../../font/opensans13.h"
#include "../../font/opensans13b.h"
#include "../../font/opensans14.h"
#include "../../font/opensans14b.h"
#include "../../font/opensans15.h"
#include "../../font/opensans16.h"
#include "../../font/opensans16b.h"
#include "../../font/opensans18.h"
#include "../../font/opensans18b.h"
#include "../../font/opensans20.h"
#include "../../font/opensans20b.h"
#include "../../font/opensans24.h"
#include "../../font/opensans24b.h"
#include "../../font/opensans26.h"
#include "../../font/opensans26b.h"

extern const GFXfont *HEADLINE_FONT; 
extern const GFXfont *TITLE_FONT;
extern const GFXfont *TEXT_FONT_BOLD;
extern const GFXfont *TEXT_FONT;

/**
 * @brief Get the font based on the specified size and boldness.
 * 
 * This function returns the OpenSans font based on the specified size and boldness.
 * 
 * @param size The size of the font.
 * @param bold Whether the font should be bold or not.
 * @return The requested font.
 */
GFXfont* getFont(int size, bool bold);

/**
 * Calculates the dimensions of the given text string when rendered using the specified font.
 * 
 * @param font The font used to render the text.
 * @param string The text string to measure.
 * @param width A pointer to an integer where the width of the text will be stored.
 * @param height A pointer to an integer where the height of the text will be stored.
 */
void epd_get_text_dimensions(
    const GFXfont *font,
    const char *string,
    int32_t *p_width,
    int32_t *p_height);

#endif // FONTS_H