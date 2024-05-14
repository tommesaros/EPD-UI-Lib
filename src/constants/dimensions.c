#include "../include/dimensions.h"
#include "epd_driver.h"

const int CORNER_RADIUS = 30;

// Status bar dimensions
const int STATUS_BAR_HEIGHT = 65;
const int SCREEN_MIDDLE_WITH_STATUS_BAR = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2;

const int PROGRESS_BAR_HEIGHT = 20;

const int CHECK_BOX_SIZE = 40;

const int RADIO_BUTTON_RADIUS = 20;

// Button dimensions
const int UPPER_BUTTON_ROW_Y = STATUS_BAR_HEIGHT + 20;

// Card dimensions
const int SMALL_CARD_WIDTH = 300;
const int SMALL_CARD_HEIGHT = 100;
const int CARD_PADDING = 20;
//TODO , square card, big horizontal card