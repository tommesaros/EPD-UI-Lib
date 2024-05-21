#ifndef COLORS_H
#define COLORS_H

extern const int BLACK;
extern const int WHITE;
extern const int GRAY;

/**
 * This function takes a font color (range 0-15) as input and converts it 
 * to a format for epd_draw_* and epd_fill_* functions (range 0-255).
 *
 * @param color The font color to be converted (range 0 as black, 15 as white).
 * @return The converted font color (range 0 as black, 255 as white).
 */
int epd_convert_color_range(int color);

#endif // COLORS_H