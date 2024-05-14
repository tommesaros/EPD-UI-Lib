#ifndef COMPONENTS_H
#define COMPONENTS_H

/*******************************************************************
 * How to use components?
 * Components present building blocks for creating the UI of an application. 
 * The components is drawn by calling the draw function of the component.
 * Attributs of such functions consist mainly of coordinates, colors, font, 
 * text content, the callback function for button interaction, 
 * and the designated framebuffer in which the component should be stored.
 * 
 * To prevent display damage and ghost images, components should not be drawn directly 
 * to the display, but a framebuffer should be used instead.
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

#endif // COMPONENTS_H