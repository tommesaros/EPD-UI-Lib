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
#include "../../../image/black_bg/edit_black_icon.h"
#include "../../../image/gray_bg/alarm_gray_icon.h"
#include "../../../image/gray_bg/edit_gray_icon.h"
#include "../../../image/white_bg/up_icon.h"
#include "../../../image/white_bg/down_icon.h"

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

    // 1st alarm card
    Rect_t cardArea = {
        CARD_PADDING * 2, 
        SCREEN_MIDDLE_WITH_STATUS_BAR - SMALL_CARD_HEIGHT * 1.5 - CARD_PADDING, 
        EPD_WIDTH - CARD_PADDING * 6 - up_icon_width, 
        SMALL_CARD_HEIGHT
    };
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(alarm_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "7:20",
        "",
        HEADLINE_FONT,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        BLACK,
        WHITE,
        WHITE_ON_BLACK,
        mainFramebuffer,
        dummyFunction
    );

    int textWidth;
    int textHeight;
    epd_get_text_dimensions(TEXT_FONT, "On - Every weekday", &textWidth, &textHeight);
    int textX = cardArea.x + CARD_PADDING * 2 + alarm_icon_width + 160;
    int textY = cardArea.y + cardArea.height / 2 + textHeight / 2;
    FontProperties *properties = new FontProperties();
    properties->fg_color = WHITE;
    properties->bg_color = BLACK;
    write_mode(
        TEXT_FONT, 
        "On - Every weekday", 
        &textX, 
        &textY, 
        mainFramebuffer, 
        WHITE_ON_BLACK,
        properties
    );

    Rect_t editIconArea = {
        .x = cardArea.x + cardArea.width - up_icon_width - CARD_PADDING * 6,
        .y = cardArea.y + cardArea.height / 2 - up_icon_height / 2,
        .width = edit_black_icon_width,
        .height =  edit_black_icon_height
    };
    epd_copy_to_framebuffer(editIconArea, (uint8_t *) edit_black_icon_data, mainFramebuffer);

    epd_draw_toggle(
        cardArea.x + cardArea.width - TOGGLE_WIDTH - CARD_PADDING,
        cardArea.y + cardArea.height / 2 - TOGGLE_HEIGHT / 2,
        true,
        mainFramebuffer,
        dummyFunction
    );

    // 2nd alarm card
    cardArea.y = SCREEN_MIDDLE_WITH_STATUS_BAR - SMALL_CARD_HEIGHT / 2;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(alarm_gray_icon_data), //icon of current weather
        alarm_gray_icon_width,
        alarm_gray_icon_height,
        "11:40",
        "",
        HEADLINE_FONT,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        GRAY,
        BLACK,
        BLACK_ON_WHITE,
        mainFramebuffer,
        dummyFunction
    );

    textX = cardArea.x + CARD_PADDING * 2 + alarm_icon_width + 160;
    textY = cardArea.y + cardArea.height / 2 + textHeight / 2;
    properties->fg_color = BLACK;
    properties->bg_color = GRAY;
    write_mode(
        TEXT_FONT, 
        "Off - Every Mon & Tue", 
        &textX, 
        &textY, 
        mainFramebuffer, 
        WHITE_ON_BLACK,
        properties
    );

    editIconArea.x = cardArea.x + cardArea.width - up_icon_width - CARD_PADDING * 6,
    editIconArea.y = cardArea.y + cardArea.height / 2 - up_icon_height / 2,
    epd_copy_to_framebuffer(editIconArea, (uint8_t *) edit_gray_icon_data, mainFramebuffer);

    epd_draw_toggle(
        cardArea.x + cardArea.width - TOGGLE_WIDTH - CARD_PADDING,
        cardArea.y + cardArea.height / 2 - TOGGLE_HEIGHT / 2,
        false,
        mainFramebuffer,
        dummyFunction
    );

    // 3rd alarm card
    cardArea.y = SCREEN_MIDDLE_WITH_STATUS_BAR + SMALL_CARD_HEIGHT / 2 + CARD_PADDING;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(alarm_icon_data),
        alarm_icon_width,
        alarm_icon_height,
        "16:58",
        "",
        HEADLINE_FONT,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        BLACK,
        WHITE,
        WHITE_ON_BLACK,
        mainFramebuffer,
        dummyFunction
    );

    textX = cardArea.x + CARD_PADDING * 2 + alarm_icon_width + 160;
    textY = cardArea.y + cardArea.height / 2 + textHeight / 2;
    properties->fg_color = WHITE;
    properties->bg_color = BLACK;
    write_mode(
        TEXT_FONT, 
        "On - Tomorrow, once", 
        &textX, 
        &textY, 
        mainFramebuffer, 
        WHITE_ON_BLACK,
        properties
    );

    editIconArea.x = cardArea.x + cardArea.width - up_icon_width - CARD_PADDING * 6,
    editIconArea.y = cardArea.y + cardArea.height / 2 - up_icon_height / 2,
    epd_copy_to_framebuffer(editIconArea, (uint8_t *) edit_black_icon_data, mainFramebuffer);

    epd_draw_toggle(
        cardArea.x + cardArea.width - TOGGLE_WIDTH - CARD_PADDING,
        cardArea.y + cardArea.height / 2 - TOGGLE_HEIGHT / 2,
        true,
        mainFramebuffer,
        dummyFunction
    );

    // Scroll buttons
    Rect_t arrowIconArea = {
        .x = EPD_WIDTH - CARD_PADDING * 2 - up_icon_width,
        .y = EPD_HEIGHT / 2 - CARD_PADDING - up_icon_height,
        .width = up_icon_width,
        .height =  up_icon_height
    };
    epd_copy_to_framebuffer(arrowIconArea, (uint8_t *) up_icon_data, mainFramebuffer);
    arrowIconArea.y = EPD_HEIGHT / 2 + CARD_PADDING;
    epd_copy_to_framebuffer(arrowIconArea, (uint8_t *) down_icon_data, mainFramebuffer);

    // Add new alarm button
    epd_draw_circle_button(
        "+",
        HEADLINE_FONT,
        EPD_WIDTH - 60,
        EPD_HEIGHT - 60,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        mainFramebuffer,
        dummyFunction
    ); 

    epd_draw_main_framebuffer();
}
