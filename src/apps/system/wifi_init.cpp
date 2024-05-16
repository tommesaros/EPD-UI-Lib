// ----------------------------
// External libraries
// ----------------------------
#include <Arduino.h>
#include "epd_driver.h"

// ----------------------------
// Internal libraries
// ----------------------------
#include "include/fonts.h"
#include "include/components.h"
#include "include/colors.h"

// ----------------------------
// Images
// ----------------------------
#include "../../../image/white_bg/wifi_icon.h"

// ----------------------------
// Credentials
// Make sure to import your own credentials to the credentials.h file!
// ----------------------------
#include "../../include/credentials.h"

// ----------------------------
// Handlers
// ----------------------------
#include "../../include/handlers/framebuffer_handler.h"

// ----------------------------
// Apps
// ----------------------------
#include "../../include/apps/system/wifi_init.h"

void displayWiFiInitMessage() {
    uint8_t *framebuffer = getOverlayFramebuffer();
    cleanFramebufferAndEPD(framebuffer, epd_full_screen());

    int32_t textX = 100;
    int32_t textY = 240;
    writeln(HEADLINE_FONT, "Connecting to WiFi...", &textX, &textY, framebuffer);

    char wifi_init_text[256];
    sprintf(
        wifi_init_text, 
        "Please make sure that %s\nnetwork is reachable and the password stored\nin src/constants/credentials is correct.", 
        WIFI_SSID
    );
    textX = 100;
    textY = 290;
    write_string(TEXT_FONT, (char *)wifi_init_text, &textX, &textY, framebuffer);

    Rect_t iconArea = {
        .x = EPD_WIDTH - 100 - wifi_icon_width,
        .y = EPD_HEIGHT / 2 - wifi_icon_height / 2,
        .width = wifi_icon_width,
        .height =  wifi_icon_height
    };
    epd_copy_to_framebuffer(iconArea, (uint8_t *) wifi_icon_data, framebuffer);

    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
}