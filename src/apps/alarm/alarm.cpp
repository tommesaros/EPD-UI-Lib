/*******************************************************************
    
*******************************************************************/

// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"
#include <OpenWeather.h>

// ----------------------------
// Internal libraries
// ----------------------------
#include "include/fonts.h"
#include "include/components.h"
#include "include/colors.h"

// ----------------------------
// Images
// ----------------------------
#include "../../../image/black_bg/alarm_icon.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../../include/handlers/epd_handler.h"
#include "../../include/handlers/touch_handler.h"
#include "../../include/handlers/framebuffer_handler.h"
#include "../../include/handlers/weather_handler.h"

// ----------------------------
// Credentials
// Make sure to import your own credentials to the credentials.h file!
// ----------------------------
#include "../../include/credentials.h"

// ----------------------------
// Apps
// ----------------------------
#include "../../include/apps/alarm/alarm.h"

//tertiary button to add new alarm, card for each alarm

void displayAlarm() {
    uint8_t *mainFramebuffer = getMainFramebuffer();
    clearTouchPoints();
    cleanFramebufferAndEPD(mainFramebuffer, epd_full_screen());
    epd_draw_status_bar(dummyFunction);

    Rect_t cardArea = {
        EPD_WIDTH / 2 - SMALL_CARD_WIDTH / 2 - 70, 
        SCREEN_MIDDLE_WITH_STATUS_BAR - SMALL_CARD_HEIGHT * 1.5 - CARD_PADDING, 
        SMALL_CARD_WIDTH, 
        SMALL_CARD_HEIGHT
    };
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(alarm_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "Tomorrow 7:20",
        "Once", // dummy data
        TEXT_FONT_BOLD,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        BLACK,
        WHITE,
        WHITE_ON_BLACK,
        mainFramebuffer,
        dummyFunction
    );

    CurrentWeather *current = getCurrentWeather();
    cardArea.y = SCREEN_MIDDLE_WITH_STATUS_BAR - SMALL_CARD_HEIGHT / 2;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(alarm_icon_data), //icon of current weather
        alarm_icon_width,
        alarm_icon_height,
        "11:40",
        "Off",
        TEXT_FONT_BOLD,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        GRAY,
        BLACK,
        BLACK_ON_WHITE,
        mainFramebuffer,
        dummyFunction
    );

    cardArea.y = SCREEN_MIDDLE_WITH_STATUS_BAR + SMALL_CARD_HEIGHT / 2 + CARD_PADDING;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(alarm_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "16:58",
        "Every Monday",
        TEXT_FONT_BOLD,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        BLACK,
        WHITE,
        WHITE_ON_BLACK,
        mainFramebuffer,
        dummyFunction
    );

    Rect_t arrowIconArea = {
        .x = EPD_WIDTH - CARD_PADDING - alarm_icon_width,
        .y = EPD_HEIGHT - 70 - alarm_icon_height / 2,
        .width = alarm_icon_width,
        .height =  alarm_icon_height
    };
    epd_copy_to_framebuffer(arrowIconArea, (uint8_t *) alarm_icon_data, mainFramebuffer);
    epd_copy_to_framebuffer(arrowIconArea, (uint8_t *) alarm_icon_data, mainFramebuffer);

    epd_draw_circle_button_icon(
        const_cast<uint8_t *>(alarm_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        EPD_WIDTH - 70,
        EPD_HEIGHT - 70,
        50, 
        BLACK,
        mainFramebuffer,
        dummyFunction
    ); 

    epd_draw_main_framebuffer();
}
