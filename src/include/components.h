#ifndef COMPONENTS_H
#define COMPONENTS_H

/*******************************************************************
 * How to use components?
 * Components present building blocks for creating the UI of an application. 
 * The components are drawn by calling the draw function of the component.
 * Attributes of such functions consist mainly of coordinates, colors, fonts, 
 * text content, the callback function for button interaction, 
 * and the designated framebuffer in which the component should be stored.
 * 
 * To prevent display damage and ghost images, components should not be drawn directly 
 * to the display, but a framebuffer should be used instead.
 * 
 * Before drawing anything that is not black, the area needs to be refreshed
 * by calling the clearArea function from the epd_handler.h file.
 * 
 * Take a look at Figma prototype to see how the components look like.
 * https://www.figma.com/file/5f3T7Kzn7FPU1AODnGr8Qp/EPD-UI-library?type=design\&node-id=0\%3A1\&mode=design\&t=BmxetsLEClQbiwkX-1
 * 
 * Need more information?
 * For more details about specific components, see their respective header files.
 * For more details about the fonts, see fonts.h.
 * For more details about the framebuffers, see framebuffer_handler.h.
 * For more details about drawing on EPD, see epd_handler.h.
 * For more details about drawing a text, see epd_driver.h:
 *  - writeln for writing a simple line of black text,
 *  - write_mode for more advanced font properties and colors,
 *  - write_string for writing a simple multiple lines of a long string.
*******************************************************************/

#include "components/button.h"
#include "components/card.h"
#include "components/check_box.h"
#include "components/notification.h"
#include "components/popup.h"
#include "components/progress_bar.h"
#include "components/radio_button.h"
#include "components/slider.h"
#include "components/status_bar.h"
#include "components/toggle.h"

extern const int BORDER_WIDTH;
extern const int CORNER_RADIUS;

// Button
extern const int UPPER_BUTTON_ROW_Y;
extern const int LOWER_BUTTON_ROW_Y;
extern const int BUTTON_HEIGHT;
extern const int SMALL_CIRCLE_BUTTON_RADIUS;
extern const int BIG_CIRCLE_BUTTON_RADIUS;

// Card
extern const int CARD_PADDING;

extern const int SMALL_CARD_WIDTH;
extern const int SMALL_CARD_HEIGHT;

extern const int SQUARE_CARD_SIZE;

extern const Rect_t BIG_CARD_AREA;

// Check box
extern const int CHECK_BOX_SIZE;
extern const int CHECK_BOX_INNER_PADDING;

// Notification
extern const int NOTIFICATION_DURATION;

// Popup
extern const Rect_t POPUP_AREA;

// Progress bar
extern const int PROGRESS_BAR_HEIGHT;

// Radio button
extern const int RADIO_BUTTON_RADIUS;

// Slider
extern const int SLIDER_WIDTH;
extern const int SLIDER_HEIGHT;
extern const char *SLIDER_UPPER_LABEL;
extern const char *SLIDER_LOWER_LABEL;

// Status bar
extern const int STATUS_BAR_SAFE_ZONE;
extern const int SCREEN_MIDDLE_WITH_STATUS_BAR;
extern const int STATUS_BAR_PADDING;
extern const int STATUS_BAR_HEIGHT;

// Toggle
extern const int TOGGLE_WIDTH;
extern const int TOGGLE_HEIGHT;

#endif // COMPONENTS_H