#include <Arduino.h>
#include "epd_driver.h"

#include "../../../font/opensans12.h"
#include "../../../font/opensans26b.h"

#include "../../include/credentials.h"
#include "../../include/wifi_init.h"

void ScreenWiFiInit() {
    int32_t wifi_popup_cursor_x = 150;
    int32_t wifi_popup_cursor_y = 150;
    writeln((GFXfont *)&OpenSans26B, "Connecting to WiFi...", &wifi_popup_cursor_x, &wifi_popup_cursor_y, framebuffer);
    wifi_popup_cursor_x = 150;
    wifi_popup_cursor_y = 190;
    writeln((GFXfont *)&OpenSans12, "Please make sure that ", &wifi_popup_cursor_x, &wifi_popup_cursor_y, framebuffer);
    writeln((GFXfont *)&OpenSans12, WIFI_SSID, &wifi_popup_cursor_x, &wifi_popup_cursor_y, framebuffer);
    writeln((GFXfont *)&OpenSans12, " network is reachable.", &wifi_popup_cursor_x, &wifi_popup_cursor_y, framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
}