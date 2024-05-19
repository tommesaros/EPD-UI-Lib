// #include "../include/components.h"
#include "epd_driver.h"

const int CORNER_RADIUS = 30;
const int BORDER_WIDTH = 3;
const int STATUS_BAR_SAFE_ZONE = 65;

// Button
const int UPPER_BUTTON_ROW_Y = STATUS_BAR_SAFE_ZONE + 20;
const int LOWER_BUTTON_ROW_Y = EPD_HEIGHT - 70;
const int BUTTON_HEIGHT = 65;
const int SMALL_CIRCLE_BUTTON_RADIUS = 40;
const int BIG_CIRCLE_BUTTON_RADIUS = 50;

// Card
const int CARD_PADDING = 20;

const int SMALL_CARD_WIDTH = 300;
const int SMALL_CARD_HEIGHT = 100;

const int SQUARE_CARD_SIZE = SMALL_CARD_HEIGHT * 2 + CARD_PADDING;

const Rect_t BIG_CARD_AREA = {
    .x = CARD_PADDING * 3,
    .y = STATUS_BAR_SAFE_ZONE + CARD_PADDING * 3,
    .width = EPD_WIDTH - CARD_PADDING * 6,
    .height = EPD_HEIGHT - STATUS_BAR_SAFE_ZONE - CARD_PADDING * 6
};

// Check box
const int CHECK_BOX_SIZE = 40;
const int CHECK_BOX_INNER_PADDING = 5; // Same for radio buttons

// Notification
const int NOTIFICATION_DURATION = 5000;

// Popup
extern const Rect_t POPUP_AREA = BIG_CARD_AREA;

// Progress bar
const int PROGRESS_BAR_HEIGHT = 30;

// Radio button
const int RADIO_BUTTON_RADIUS = 20;

// Slider
const int SLIDER_WIDTH = 100;
const int SLIDER_HEIGHT = 200;
const char *SLIDER_UPPER_LABEL = "+";
const char *SLIDER_LOWER_LABEL = "-";

// Status bar
const int SCREEN_MIDDLE_WITH_STATUS_BAR = STATUS_BAR_SAFE_ZONE + (EPD_HEIGHT - STATUS_BAR_SAFE_ZONE) / 2;
const int STATUS_BAR_PADDING = 10; // Same for notifications
const int STATUS_BAR_HEIGHT = 50;

// Toggle
const int TOGGLE_WIDTH = RADIO_BUTTON_RADIUS * 4;
const int TOGGLE_HEIGHT = RADIO_BUTTON_RADIUS * 2.2;
