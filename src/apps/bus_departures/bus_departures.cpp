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
#include "../../../image/white_bg/bus_stop_icon.h"

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
#include "../../include/apps/bus_departures/bus_departures.h"

// show bus departures - tertiary buttons for each bus stop

void displayBusDepartures() {
    uint8_t *mainFramebuffer = getMainFramebuffer();
    clearTouchPoints();
    cleanFramebufferAndEPD(mainFramebuffer, epd_full_screen());
    epd_draw_status_bar(dummyFunction);

    // First bus stop
    Rect_t cardArea = {
        .x = CARD_PADDING,
        .y = STATUS_BAR_SAFE_ZONE + CARD_PADDING,
        .width = EPD_WIDTH / 3 - CARD_PADDING * 1.25,
        .height = EPD_HEIGHT - STATUS_BAR_SAFE_ZONE - CARD_PADDING * 2
    };
    epd_draw_multi_line_card(
        (uint8_t*)bus_stop_icon_data,
        bus_stop_icon_width,
        bus_stop_icon_height,
        "Botanická",
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

    int textX = cardArea.x + CARD_PADDING ;
    int textY = cardArea.y + CARD_PADDING + 70;
    write_string(
        TEXT_FONT, 
        "32 - Ceská\n32 - Srbská", 
        &textX, 
        &textY, 
        mainFramebuffer
    );
    textX = cardArea.x + cardArea.width - CARD_PADDING * 2;
    textY = cardArea.y + CARD_PADDING + 70;
    write_string(
        TEXT_FONT, 
        "3\"\n7\"", 
        &textX, 
        &textY, 
        mainFramebuffer
    );

    // Second bus stop
    cardArea.x = cardArea.width + CARD_PADDING * 2;
    epd_draw_multi_line_card(
        (uint8_t*)bus_stop_icon_data,
        bus_stop_icon_width,
        bus_stop_icon_height,
        "Hrncírská",
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

    textX = cardArea.x + CARD_PADDING ;
    textY = cardArea.y + CARD_PADDING + 70;
    write_string(
        TEXT_FONT, 
        "1 - Reckovice\n1 - Bystrc, Ecerova\n6 - Královo pole\n6 - Starý Lískovec", 
        &textX, 
        &textY, 
        mainFramebuffer
    );
    textX = cardArea.x + cardArea.width - CARD_PADDING * 2;
    textY = cardArea.y + CARD_PADDING + 70;
    write_string(
        TEXT_FONT, 
        "1\"\n2\"\n7\"\n9\"\n", 
        &textX, 
        &textY, 
        mainFramebuffer
    );

    // Third bus stop
    cardArea.x = cardArea.width * 2 + CARD_PADDING * 3;
    epd_draw_multi_line_card(
        (uint8_t*)bus_stop_icon_data,
        bus_stop_icon_width,
        bus_stop_icon_height,
        "Konecného n.",
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

    textX = cardArea.x + CARD_PADDING ;
    textY = cardArea.y + CARD_PADDING + 70;
    write_string(
        TEXT_FONT, 
        "  3 - Rakovecká\n10 - Rakovecká\n  3 - Stará osada\n12 - Techno. park\n26 - Stefánikova c.\n12 - Komárov\n25 - Osová\n10 - Stránská skála\n25 - Stefánikova c.\n26 - Kamenný vrch", 
        &textX, 
        &textY, 
        mainFramebuffer
    );
    textX = cardArea.x + cardArea.width - CARD_PADDING * 2;
    textY = cardArea.y + CARD_PADDING + 70;
    write_string(
        TEXT_FONT, 
        "0\"\n1\"\n1\"\n3\"\n5\"\n5\"\n6\"\n7\"\n9\"\n9\"", 
        &textX, 
        &textY, 
        mainFramebuffer
    );

    epd_draw_main_framebuffer();
}