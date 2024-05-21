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
#include "../../include/fonts.h"
#include "../../include/components.h"
#include "../../include/colors.h"

// ----------------------------
// Images
// ----------------------------
#include "../../../image/black_bg/padlock_small_icon.h"
#include "../../../image/black_bg/power_bck_icon.h"
#include "../../../image/black_bg/coffee_icon.h"
#include "../../../image/white_bg/power_big_icon.h"
#include "../../../image/white_bg/power_icon.h"
#include "../../../image/white_bg/cancel_icon.h"
#include "../../../image/white_bg/bulb_icon.h"
#include "../../../image/white_bg/volume_icon.h"
#include "../../../image/white_bg/cup_icon.h"
#include "../../../image/white_bg/info_icon.h"
#include "../../../image/white_bg/blinds_icon.h"
#include "../../../image/white_bg/white_coffee_icon.h"
#include "../../../image/bg.h"

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
#include "../../include/apps/system/control_panel.h"

void toggle() {
    // Here would be the logic for toggling the checkboxes and radio buttons
}

void powerOff() {
    epd_clear();
    epd_draw_grayscale_image(epd_full_screen(), (uint8_t *)bg_data);
    delay(2000);
    epd_sleep();
}

void openPowerOffPopup() {
    epd_clear();
    setOverlayActive(true);
    clearOverlayTouchPoints();
    epd_fill_rect(0, 0, EPD_WIDTH, EPD_HEIGHT, epd_convert_color_range(BLACK), getOverlayFramebuffer());

    epd_trigger_popup(
        (uint8_t*)power_big_icon_data,
        power_big_icon_width,
        power_big_icon_height,
        "Power off the device?",
        "Are you sure you want to power off the device?\nThis will close all running apps and turn off the\ndisplay. You can turn it back on by pressing the \nmost right button above the screen.",
        (uint8_t*)power_bck_icon_data,
        power_bck_icon_width,
        power_bck_icon_height,
        "Power off", 
        powerOff,
        (uint8_t*)cancel_icon_data,
        cancel_icon_width,
        cancel_icon_height,
        "Cancel", 
        epd_clear_popup
    );

    epd_draw_overlay_framebuffer();
}

void makeCoffee() {
    // Here would be the function that communicates with the coffee machine
    epd_trigger_notification(
        const_cast<uint8_t*>(coffee_icon_data),
        coffee_icon_width,
        coffee_icon_height,
        "Kitchen coffee machine", 
        "Preparing latte macchiato." 
    );
}

void displayControlPanel() {
    uint8_t *mainFramebuffer = getMainFramebuffer();
    clearTouchPoints();
    cleanFramebufferAndEPD(mainFramebuffer, epd_full_screen());
    epd_fill_rect(0, 0, EPD_WIDTH, EPD_HEIGHT, epd_convert_color_range(BLACK), mainFramebuffer);
    epd_draw_status_bar(dummyFunction);

    // Lights card with checkboxes
    Rect_t cardArea = {
        .x = CARD_PADDING,
        .y = STATUS_BAR_SAFE_ZONE + CARD_PADDING,
        .width = SQUARE_CARD_SIZE * 1.5,
        .height = SQUARE_CARD_SIZE
    };

    epd_draw_multi_line_card(
        (uint8_t*)bulb_icon_data,
        bulb_icon_width,
        bulb_icon_height,
        "Lights",
        "",
        TITLE_FONT,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        WHITE,
        BLACK,
        BLACK_ON_WHITE,
        mainFramebuffer,
        dummyFunction
    );

    epd_draw_check_box(
        "Bedroom", 
        TEXT_FONT_BOLD,
        cardArea.x + CARD_PADDING * 2 + bulb_icon_width, 
        STATUS_BAR_SAFE_ZONE + CARD_PADDING * 2 + 50 * 1, 
        WHITE,
        BLACK, 
        true,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_check_box(
        "Living room", 
        TEXT_FONT,
        cardArea.x + CARD_PADDING * 2 + bulb_icon_width, 
        STATUS_BAR_SAFE_ZONE + CARD_PADDING * 2 + 50 * 2, 
        WHITE,
        BLACK, 
        false,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );
    
    epd_draw_check_box(
        "Kitchen", 
        TEXT_FONT_BOLD,
        cardArea.x + CARD_PADDING * 2 + bulb_icon_width, 
        STATUS_BAR_SAFE_ZONE + CARD_PADDING * 2 + 50 * 3, 
        WHITE,
        BLACK, 
        true,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    // Window blinds card with radio buttons 
    cardArea.x += cardArea.width + CARD_PADDING;

    epd_draw_multi_line_card(
        (uint8_t*)blinds_icon_data,
        blinds_icon_width,
        blinds_icon_height,
        "Window blinds",
        "",
        TITLE_FONT,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        WHITE,
        BLACK,
        BLACK_ON_WHITE,
        mainFramebuffer,
        dummyFunction
    );

    epd_draw_radio_button(
        "Up", 
        TEXT_FONT,
        cardArea.x + CARD_PADDING * 2 + bulb_icon_width, 
        STATUS_BAR_SAFE_ZONE + CARD_PADDING * 2 + 50 * 1, 
        WHITE,
        BLACK, 
        false,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_radio_button(
        "Middle", 
        TEXT_FONT,
        cardArea.x + CARD_PADDING * 2 + bulb_icon_width, 
        STATUS_BAR_SAFE_ZONE + CARD_PADDING * 2 + 50 * 2, 
        WHITE,
        BLACK, 
        false,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_radio_button(
        "Down", 
        TEXT_FONT_BOLD,
        cardArea.x + CARD_PADDING * 2 + bulb_icon_width, 
        STATUS_BAR_SAFE_ZONE + CARD_PADDING * 2 + 50 * 3, 
        WHITE,
        BLACK, 
        true,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    // Volume card with slider
    cardArea.x += cardArea.width + CARD_PADDING;
    cardArea.width = EPD_WIDTH - cardArea.x - CARD_PADDING;

    epd_draw_horizontal_card(
        (uint8_t*)volume_icon_data,
        volume_icon_width,
        volume_icon_height,
        "",
        "",
        TEXT_FONT_BOLD,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        WHITE,
        BLACK,
        WHITE_ON_BLACK,
        mainFramebuffer,
        dummyFunction
    );

    epd_draw_slider(
        cardArea.x + cardArea.width - SLIDER_WIDTH - 10,
        cardArea.y + cardArea.height / 2 - SLIDER_HEIGHT / 2,
        mainFramebuffer,
        dummyFunction,
        dummyFunction
    );

    // Coffee machine card with progress bar
    cardArea.x = CARD_PADDING,
    cardArea.y += SQUARE_CARD_SIZE + CARD_PADDING,
    cardArea.width = EPD_WIDTH / 2 - CARD_PADDING * 1.5;
    cardArea.height = EPD_HEIGHT - cardArea.y - CARD_PADDING / 2;

    epd_draw_multi_line_card(
        (uint8_t*)cup_icon_data,
        cup_icon_width,
        cup_icon_height,
        "Coffee machine water",
        "",
        TITLE_FONT,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        WHITE,
        BLACK,
        BLACK_ON_WHITE,
        mainFramebuffer,
        dummyFunction
    );

    epd_draw_progress_bar(
        cardArea.x + CARD_PADDING * 2 + bulb_icon_width, 
        cardArea.y + CARD_PADDING * 2 + 20,  
        EPD_WIDTH / 2 - cardArea.x - CARD_PADDING * 4 - bulb_icon_width, 
        35, 
        GRAY, 
        BLACK, 
        mainFramebuffer
    );

    Rect_t coffeeButtonArea = {
        .x = EPD_WIDTH / 2 - CARD_PADDING - 260,
        .y = EPD_HEIGHT - CARD_PADDING - BUTTON_HEIGHT,
        .width = 260,
        .height = BUTTON_HEIGHT
    };

    epd_draw_button_icon(
        const_cast<uint8_t*>(white_coffee_icon_data),
        white_coffee_icon_width,
        white_coffee_icon_height,
        "Make coffee",
        TEXT_FONT,
        coffeeButtonArea,
        CORNER_RADIUS,
        WHITE,
        BLACK,
        BLACK_ON_WHITE,
        mainFramebuffer,
        makeCoffee
    );

    // UI info card
    cardArea.x = EPD_WIDTH / 2 + CARD_PADDING / 2,
    epd_draw_multi_line_card(
        (uint8_t*)info_icon_data,
        info_icon_width,
        info_icon_height,
        "EPD-UI-Lib",
        "github.com/tommesaros",
        TITLE_FONT,
        TEXT_FONT,
        cardArea,
        CORNER_RADIUS,
        WHITE,
        BLACK,
        BLACK_ON_WHITE,
        mainFramebuffer,
        dummyFunction
    );

    Rect_t powerOffButtonArea = {
        .x = EPD_WIDTH - CARD_PADDING * 1.5 - 230,
        .y = EPD_HEIGHT - CARD_PADDING - BUTTON_HEIGHT,
        .width = 230,
        .height = BUTTON_HEIGHT
    };

    epd_draw_button_icon(
        const_cast<uint8_t*>(power_icon_data),
        power_icon_width,
        power_icon_height,
        "Power off",
        TEXT_FONT,
        powerOffButtonArea,
        CORNER_RADIUS,
        WHITE,
        BLACK,
        BLACK_ON_WHITE,
        mainFramebuffer,
        openPowerOffPopup
    );

    epd_draw_main_framebuffer();
}