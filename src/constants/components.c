// #include "../include/components.h"
#include "epd_driver.h"

const int CORNER_RADIUS = 30;
const int BORDER_WIDTH = 2;
const int STATUS_BAR_SAFE_ZONE = 65;

// Button
const int UPPER_BUTTON_ROW_Y = STATUS_BAR_SAFE_ZONE + 20;

// Card
const int SMALL_CARD_WIDTH = 300;
const int SMALL_CARD_HEIGHT = 100;
const int CARD_PADDING = 20;
//TODO , square card, big horizontal card Rect_t area

// Check box
const int CHECK_BOX_SIZE = 40;
const int CHECK_BOX_INNER_PADDING = 5; // Same for radio buttons

// Notification
const int NOTIFICATION_DURATION = 5000;

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
