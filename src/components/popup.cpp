// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include "epd_driver.h"
#include <Wire.h>
#include <touch.h>
#include "pins.h"

// ----------------------------
// Internal libraries
// ----------------------------
#include "../include/fonts.h"
#include "../include/colors.h"
#include "../include/components/popup.h"
#include "../include/components/status_bar.h"
#include "../include/components.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../include/handlers/epd_handler.h"
#include "../include/handlers/touch_handler.h"
#include "../include/handlers/framebuffer_handler.h"

//full black screen
//then status bac
//then big whote card with write_string 
//and button at the end
//secondary touchpoints
// IF provided aditional text (desc), make space for it

void epd_clear_popup() {
    setOverlayActive(false);
    clearOverlayTouchPoints();
    epd_clear();
    epd_draw_main_framebuffer();
}

void epd_trigger_popup(
    uint8_t *imageData,
    int32_t imageWidth,
    int32_t imageHeight,
    const char *title, 
    const char *text, 
    uint8_t *primaryButtonIconData,
    int32_t primaryButtonIconWidth,
    int32_t primaryButtonIconHeight,
    const char *primaryButtonLabel, 
    void (*primaryFunction)(),
    uint8_t *secondaryButtonIconData,
    int32_t secondaryButtonIconWidth,
    int32_t secondaryButtonIconHeight,
    const char *secondaryButtonLabel, 
    void (*secondaryFunction)()) {
        uint8_t *framebuffer = getOverlayFramebuffer();
        //TODO Black bg

        // Background
        epd_draw_multi_line_card(
            (uint8_t*)imageData,
            imageWidth,
            imageHeight,
            title,
            text,
            TITLE_FONT,
            TEXT_FONT,
            POPUP_AREA,
            CORNER_RADIUS,
            WHITE,
            BLACK,
            BLACK_ON_WHITE,
            framebuffer,
            dummyFunction
        );

        // Primary button
        int textWidth = 0;
        int textHeight = 0;
        epd_get_text_dimensions(TEXT_FONT, primaryButtonLabel, &textWidth, &textHeight);
        Rect_t buttonArea = {
            .x = POPUP_AREA.x + POPUP_AREA.width - CARD_PADDING * 5 - textWidth - primaryButtonIconWidth, //TODO more padding
            .y = POPUP_AREA.y + POPUP_AREA.height - CARD_PADDING - BUTTON_HEIGHT, // TODO buttonheight to dimensions
            .width = textWidth + primaryButtonIconWidth + CARD_PADDING * 4,
            .height = BUTTON_HEIGHT
        };
        epd_draw_button_icon(
            primaryButtonIconData, 
            primaryButtonIconWidth,
            primaryButtonIconHeight,
            primaryButtonLabel,
            TEXT_FONT,
            buttonArea, 
            CORNER_RADIUS, 
            BLACK, 
            WHITE,
            WHITE_ON_BLACK, 
            framebuffer,
            dummyFunction
        );
        addOverlayTouchPoint(buttonArea, primaryFunction);

        // Secondary button
        epd_get_text_dimensions(TEXT_FONT, secondaryButtonLabel, &textWidth, &textHeight);
        buttonArea.x -= textWidth + CARD_PADDING * 5 + secondaryButtonIconWidth;
        buttonArea.width = textWidth + secondaryButtonIconWidth + CARD_PADDING * 4;
        epd_draw_button_icon(
            secondaryButtonIconData, 
            secondaryButtonIconWidth,
            secondaryButtonIconHeight,
            secondaryButtonLabel,
            TEXT_FONT,
            buttonArea, 
            CORNER_RADIUS, 
            WHITE, 
            BLACK,
            WHITE_ON_BLACK, 
            framebuffer,
            dummyFunction
        );
        addOverlayTouchPoint(buttonArea, secondaryFunction);
}