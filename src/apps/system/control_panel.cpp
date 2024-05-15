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
#include "../../../image/white_bg/power_icon.h"

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

bool firstCheckBox = true;
bool secondCheckBox = false;

void toggle() {
    //TODO draw opposite of what it is
}

void openPowerOffPopup() {
    epd_trigger_notification(
        // Here would be the function that opens the door
        const_cast<uint8_t*>(padlock_small_icon_data),
        padlock_small_icon_width,
        padlock_small_icon_height,
        "Door opened", 
        "Hallway door is open for 30 seconds." 
    );
}

void displayControlPanel() {
    //TODO white cards 
    //TODO slider for volume
    //TODO wireless toggle
    //TODO window blinds radion buttons
    //TODO ?? checkboxes
    uint8_t *mainFramebuffer = getMainFramebuffer();
    clearTouchPoints();
    cleanFramebufferAndEPD(mainFramebuffer, epd_full_screen());
    epd_fill_rect(0, 0, EPD_WIDTH, EPD_HEIGHT, BLACK, mainFramebuffer);
    epd_draw_status_bar(dummyFunction);

    //TODO Logic for control panel
    epd_draw_check_box(
        "Ahoj", 
        (GFXfont *)&OpenSans12B,
        20, 
        100, 
        0,
        15, 
        firstCheckBox,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_check_box(
        "Caaau", 
        (GFXfont *)&OpenSans12B,
        20, 
        150, 
        0,
        15, 
        secondCheckBox,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_radio_button(
        "Ahoj", 
        (GFXfont *)&OpenSans12B,
        20, 
        200, 
        0,
        15, 
        firstCheckBox,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    epd_draw_radio_button(
        "Caaau", 
        (GFXfont *)&OpenSans12B,
        20, 
        250, 
        0,
        15, 
        secondCheckBox,
        BLACK_ON_WHITE,
        mainFramebuffer,
        toggle
    );

    // TODO Remaining coffee machine water?
    epd_draw_progress_bar(
        20, 
        300, 
        300, 
        15, 
        GRAY, 
        BLACK, 
        mainFramebuffer
    );
    // TODO Make cofee button

    //TODO Power off button -> popup dialog/card

    epd_fill_rounded_rect(20, 380, 100, 20, 5,100, mainFramebuffer);
    epd_fill_rounded_rect(20, 400, 100, 20, 5,200, mainFramebuffer);
    epd_fill_rounded_rect(20, 420, 100, 20, 5,220, mainFramebuffer);
    epd_fill_rounded_rect(20, 440, 100, 20, 5,240, mainFramebuffer);
    epd_fill_rounded_rect(20, 440, 100, 20, 5,150, mainFramebuffer);
5,
    epd_fill_rounded_rect(120, 380, 100, 20,5, epd_convert_font_color(10), mainFramebuffer);
    epd_fill_rounded_rect(120, 400, 100, 20,5, epd_convert_font_color(11), mainFramebuffer);
    epd_fill_rounded_rect(120, 420, 100, 20,5, epd_convert_font_color(12), mainFramebuffer);
    epd_fill_rounded_rect(120, 440, 100, 20,5, epd_convert_font_color(13), mainFramebuffer);
    epd_fill_rounded_rect(120, 440, 100, 20,5, epd_convert_font_color(14), mainFramebuffer);

    Rect_t powerOffButtonArea = {
        .x = EPD_WIDTH - 260,
        .y = EPD_HEIGHT - 90,
        .width = 230,
        .height = 70
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

    epd_draw_grayscale_image(epd_full_screen(), mainFramebuffer);



    //TODO power off popup and then show image 
    // epd_sleep();
}