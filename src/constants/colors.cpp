#include <Arduino.h>
#include "../include/colors.h"

const int BLACK = 0;
const int WHITE = 15;
const int GRAY = 12;

int epd_convert_color_range(int color) {
    return map(color, 0, 15, 0, 255);
}
