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
#include "../../../image/white_bg/alarm_white_icon.h"
#include "../../../image/white_bg/cancel_icon.h"
#include "../../../image/white_bg/backspace_icon.h"
#include "../../../image/black_bg/save_icon.h"

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
#include "../../include/apps/alarm/new_alarm.h"

void openNewAlarmPopup() {
    epd_clear();
    setOverlayActive(true);
    clearOverlayTouchPoints();
    uint8_t *framebuffer = getOverlayFramebuffer();
    epd_fill_rect(0, 0, EPD_WIDTH, EPD_HEIGHT, epd_convert_color_range(BLACK), framebuffer);

    // Background
    Rect_t bgArea = {
        .x = CARD_PADDING * 2,
        .y = CARD_PADDING * 2,
        .width = EPD_WIDTH - CARD_PADDING * 4,
        .height = EPD_HEIGHT - CARD_PADDING * 4
    };
    epd_draw_multi_line_card(
        (uint8_t*)alarm_white_icon_data,
        alarm_white_icon_width,
        alarm_white_icon_height,
        "New alarm",
        "",
        TITLE_FONT,
        TEXT_FONT,
        bgArea,
        CORNER_RADIUS,
        WHITE,
        BLACK,
        BLACK_ON_WHITE,
        framebuffer,
        dummyFunction
    );

    // Reapeat checkboxes
    epd_draw_radio_button(
        "Once",
        TEXT_FONT,
        bgArea.x + CARD_PADDING * 2,
        bgArea.y + bgArea.height - CARD_PADDING - CHECK_BOX_SIZE - (CHECK_BOX_SIZE + 15) * 3,
        WHITE,
        BLACK,
        false,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    epd_draw_check_box(
        "Mon",
        TEXT_FONT,
        bgArea.x + CARD_PADDING * 2,
        bgArea.y + bgArea.height - CARD_PADDING - CHECK_BOX_SIZE - (CHECK_BOX_SIZE + 15) * 2,
        WHITE,
        BLACK,
        false,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    epd_draw_check_box(
        "Tue",
        TEXT_FONT,
        bgArea.x + CARD_PADDING * 2,
        bgArea.y + bgArea.height - CARD_PADDING - CHECK_BOX_SIZE - (CHECK_BOX_SIZE + 15),
        WHITE,
        BLACK,
        false,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    epd_draw_check_box(
        "Wed",
        TEXT_FONT,
        bgArea.x + CARD_PADDING * 2,
        bgArea.y + bgArea.height - CARD_PADDING - CHECK_BOX_SIZE,
        WHITE,
        BLACK,
        false,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    epd_draw_check_box(
        "Thu",
        TEXT_FONT,
        bgArea.x + CARD_PADDING * 2 + 140,
        bgArea.y + bgArea.height - CARD_PADDING - CHECK_BOX_SIZE - (CHECK_BOX_SIZE + 15) * 3,
        WHITE,
        BLACK,
        false,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    epd_draw_check_box(
        "Fri",
        TEXT_FONT,
        bgArea.x + CARD_PADDING * 2 + 140,
        bgArea.y + bgArea.height - CARD_PADDING - CHECK_BOX_SIZE - (CHECK_BOX_SIZE + 15) * 2,
        WHITE,
        BLACK,
        false,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    epd_draw_check_box(
        "Sat",
        TEXT_FONT,
        bgArea.x + CARD_PADDING * 2 + 140,
        bgArea.y + bgArea.height - CARD_PADDING - CHECK_BOX_SIZE - (CHECK_BOX_SIZE + 15),
        WHITE,
        BLACK,
        false,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    epd_draw_check_box(
        "Sun",
        TEXT_FONT,
        bgArea.x + CARD_PADDING * 2 + 140,
        bgArea.y + bgArea.height - CARD_PADDING - CHECK_BOX_SIZE,
        WHITE,
        BLACK,
        false,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    // Time 
    int textX = bgArea.x + CARD_PADDING * 3;
    int textY = bgArea.y + bgArea.height / 4 + 60;
    write_mode(
        HEADLINE_FONT, 
        "9:40", 
        &textX, 
        &textY, 
        framebuffer, 
        BLACK_ON_WHITE, 
        NULL
    );

    epd_draw_hline(
        bgArea.x + CARD_PADDING * 2,
        bgArea.y + bgArea.height / 4 + 75,
        bgArea.width / 2 - CARD_PADDING * 4,
        BLACK,
        framebuffer
    );

    Rect_t backspaceIconArea = {
        .x = bgArea.x + CARD_PADDING * 2 + bgArea.width / 2 - CARD_PADDING * 4 - backspace_icon_width - CARD_PADDING,
        .y = bgArea.y + bgArea.height / 4 + 75 - CARD_PADDING - backspace_icon_height,
        .width = backspace_icon_width,
        .height =  backspace_icon_height
    };
    epd_copy_to_framebuffer(backspaceIconArea, (uint8_t *) backspace_icon_data, framebuffer);

    // Time picker buttons
    epd_draw_circle_button(
        "1",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4 - 100,
        bgArea.y + CARD_PADDING * 2 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    ); 

    epd_draw_circle_button(
        "2",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4,
        bgArea.y + CARD_PADDING * 2 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    );

    epd_draw_circle_button(
        "3",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4 + 100,
        bgArea.y + CARD_PADDING * 2 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    );

    epd_draw_circle_button(
        "4",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4 - 100,
        bgArea.y + CARD_PADDING * 2 + 100 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    );

    epd_draw_circle_button(
        "5",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4,
        bgArea.y + CARD_PADDING * 2 + 100 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    );

    epd_draw_circle_button(
        "6",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4 + 100,
        bgArea.y + CARD_PADDING * 2 + 100 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    );

    epd_draw_circle_button(
        "7",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4 - 100,
        bgArea.y + CARD_PADDING * 2 + 200 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    );

    epd_draw_circle_button(
        "8",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4,
        bgArea.y + CARD_PADDING * 2 + 200 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    );

    epd_draw_circle_button(
        "9",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4 + 100,
        bgArea.y + CARD_PADDING * 2 + 200 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    );

    epd_draw_circle_button(
        "0",
        HEADLINE_FONT,
        EPD_WIDTH - bgArea.width / 4,
        bgArea.y + CARD_PADDING * 2 + 300 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        WHITE,
        framebuffer,
        dummyFunction
    );

    // Save button
    epd_draw_circle_button_icon(
        (uint8_t*)save_icon_data,
        save_icon_width,
        save_icon_height,
        EPD_WIDTH - bgArea.width / 4 + 100,
        bgArea.y + CARD_PADDING * 2 + 300 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        BLACK,
        framebuffer,
        dummyFunction
    );

    Rect_t buttonArea = {
        .x = EPD_WIDTH - bgArea.width / 4 + 100 - SMALL_CIRCLE_BUTTON_RADIUS,
        .y = bgArea.y + CARD_PADDING * 2 + 300 - SMALL_CIRCLE_BUTTON_RADIUS,
        .width = SMALL_CIRCLE_BUTTON_RADIUS * 2,
        .height = SMALL_CIRCLE_BUTTON_RADIUS * 2
    };
    addOverlayTouchPoint(buttonArea, epd_clear_popup); // This would save the alarm

    // Cancel button
    epd_draw_circle_button_icon(
        (uint8_t*)cancel_icon_data,
        cancel_icon_width,
        cancel_icon_height,
        EPD_WIDTH - bgArea.width / 4 - 100,
        bgArea.y + CARD_PADDING * 2 + 300 + SMALL_CIRCLE_BUTTON_RADIUS,
        SMALL_CIRCLE_BUTTON_RADIUS, 
        WHITE,
        framebuffer,
        dummyFunction
    );
    
    buttonArea.x = EPD_WIDTH - bgArea.width / 4 - 100 - SMALL_CIRCLE_BUTTON_RADIUS,
    addOverlayTouchPoint(buttonArea, epd_clear_popup);

    epd_draw_overlay_framebuffer();
}