/*******************************************************************
    Based on the OpenWeather API Example:
    My_OpenWeather_Test.ino
    https://github.com/Bodmer/OpenWeather/blob/main/examples/Onecall%20API%20(subscription%20required)/My_OpenWeather_Test/My_OpenWeather_Test.ino
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
#include "include/dimensions.h"

// ----------------------------
// Images
// ----------------------------
#include "../../../image/black_bg/temp_icon.h"
#include "../../../image/black_bg/sunrise_icon.h"
#include "../../../image/black_bg/humidity_icon.h"
#include "../../../image/black_bg/rain_icon.h"
#include "../../../image/black_bg/uv_icon.h"
#include "../../../image/black_bg/wind_icon.h"
#include "../../../image/black_bg/cloudy_icon.h"
#include "../../../image/white_bg/daily_icon.h"
#include "../../../image/white_bg/hourly_icon.h"
#include "../../../image/white_bg/back_icon.h"

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
#include "../../include/apps/weather/weather.h"

void showDailyWeather();

void weatherExit() {
}

void showHourlyWeather() {
    uint8_t * framebuffer = GetMainFramebuffer();
    ClearTouchPoints();
    CleanFramebuffer(framebuffer, epd_full_screen());
    epd_draw_status_bar(weatherExit); 

    // Title and back button
    epd_draw_tertiary_button_icon(
        const_cast<uint8_t *>(back_icon_data), 
        back_icon_width,
        back_icon_height,
        "Hourly weather",
        (GFXfont *)&OpenSans14B,
        30, 
        STATUS_BAR_HEIGHT + 20,  
        15, 
        0,
        WHITE_ON_BLACK, 
        framebuffer,
        ScreenWeather
    );

    // Button for daily weather
    epd_draw_tertiary_button_icon(
        const_cast<uint8_t *>(daily_icon_data), 
        daily_icon_width,
        daily_icon_height,
        "Daily",
        (GFXfont *)&OpenSans12,
        EPD_WIDTH - 150, 
        STATUS_BAR_HEIGHT + 20,  
        15, 
        0,
        WHITE_ON_BLACK, 
        framebuffer,
        showDailyWeather
    );

    // Information cards
    Rect_t cardArea = {
        EPD_WIDTH / 2 - 470, 
        STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 140, 
        300, 
        100
    };

    for (int i = 0; i < MAX_HOURS; i++) {
        HourlyWeather *hour = getHourWeather(i);
        cardArea.x = EPD_WIDTH / 2 - 470 + i * 320,
        cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 140;
        
        epd_draw_horizontal_card(
            const_cast<uint8_t*>(getWeatherIcon(hour->icon)),
            temp_icon_width,
            temp_icon_height,
            hour->time.c_str(),
            hour->description.c_str(),
            (GFXfont *)&OpenSans12B,
            (GFXfont *)&OpenSans12,
            cardArea,
            30,
            0,
            15,
            WHITE_ON_BLACK,
            framebuffer,
            dummyFunction
        );

        cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 20;
        epd_draw_horizontal_card(
            const_cast<uint8_t *>(temp_icon_data),
            temp_icon_width,
            temp_icon_height,
            "Temperature",
            hour->temperature.c_str(),
            (GFXfont *)&OpenSans12B,
            (GFXfont *)&OpenSans12,
            cardArea,
            30,
            0,
            15,
            WHITE_ON_BLACK,
            framebuffer,
            dummyFunction
        );

        cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 + 100;
        epd_draw_horizontal_card(
            const_cast<uint8_t *>(wind_icon_data),
            temp_icon_width,
            temp_icon_height,
            ("Rain " + hour->rain).c_str(),
            ("Wind " + hour->wind_speed).c_str(),
            (GFXfont *)&OpenSans12B,
            (GFXfont *)&OpenSans12,
            cardArea,
            30,
            0,
            15,
            WHITE_ON_BLACK,
            framebuffer,
            dummyFunction
        );
    }

    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
}

void showDailyWeather() {
    uint8_t * framebuffer = GetMainFramebuffer();
    ClearTouchPoints();
    CleanFramebuffer(framebuffer, epd_full_screen());
    epd_draw_status_bar(weatherExit); 

    // Title and back button
    epd_draw_tertiary_button_icon(
        const_cast<uint8_t *>(back_icon_data), 
        back_icon_width,
        back_icon_height,
        "Daily weather",
        (GFXfont *)&OpenSans14B,
        30, 
        STATUS_BAR_HEIGHT + 20,  
        15, 
        0,
        WHITE_ON_BLACK, 
        framebuffer,
        ScreenWeather
    );

    // Button for hourly weather
    epd_draw_tertiary_button_icon(
        const_cast<uint8_t *>(hourly_icon_data), 
        daily_icon_width,
        daily_icon_height,
        "Hourly",
        (GFXfont *)&OpenSans12,
        EPD_WIDTH - 150, 
        STATUS_BAR_HEIGHT + 20,  
        15, 
        0,
        WHITE_ON_BLACK, 
        framebuffer,
        showHourlyWeather
    );

    // Information cards
    Rect_t cardArea = {
        EPD_WIDTH / 2 - 470, 
        STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 140, 
        300, 
        100
    };

    // MAX_DAYS - 1 because DAY = 0 is today
    for (int i = 0; i < MAX_DAYS - 1; i++) {
        DailyWeather *day = getDayWeather(i + 1);
        cardArea.x = EPD_WIDTH / 2 - 470 + i * 320,
        cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 140;
        
        epd_draw_horizontal_card(
            const_cast<uint8_t*>(getWeatherIcon(day->icon)),
            temp_icon_width,
            temp_icon_height,
            day->day.c_str(),
            day->description.c_str(),
            (GFXfont *)&OpenSans12B,
            (GFXfont *)&OpenSans12,
            cardArea,
            30,
            0,
            15,
            WHITE_ON_BLACK,
            framebuffer,
            dummyFunction
        );

        cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 20;
        epd_draw_horizontal_card(
            const_cast<uint8_t *>(temp_icon_data),
            temp_icon_width,
            temp_icon_height,
            ("Max " + day->temp_max).c_str(),
            ("Min " + day->temp_min).c_str(),
            (GFXfont *)&OpenSans12B,
            (GFXfont *)&OpenSans12,
            cardArea,
            30,
            0,
            15,
            WHITE_ON_BLACK,
            framebuffer,
            dummyFunction
        );

        cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 + 100;
        epd_draw_horizontal_card(
            const_cast<uint8_t *>(wind_icon_data),
            temp_icon_width,
            temp_icon_height,
            ("Rain " + day->rain).c_str(),
            ("Wind " + day->wind_speed).c_str(),
            (GFXfont *)&OpenSans12B,
            (GFXfont *)&OpenSans12,
            cardArea,
            30,
            0,
            15,
            WHITE_ON_BLACK,
            framebuffer,
            dummyFunction
        );
    }

    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
}

void ScreenWeather() {
    uint8_t * framebuffer = GetMainFramebuffer();
    ClearTouchPoints();
    CleanFramebuffer(framebuffer, epd_full_screen());
    epd_draw_status_bar(weatherExit); 
    CurrentWeather *current = getCurrentWeather();

    // Title
    int cursor_x = 30; 
    int cursor_y = STATUS_BAR_HEIGHT + 50;
    writeln((GFXfont *)&OpenSans14B, "Current weather ", &cursor_x, &cursor_y, framebuffer);

    // Buttons for daily and hourly weather
    epd_draw_tertiary_button_icon(
        const_cast<uint8_t *>(daily_icon_data), 
        daily_icon_width,
        daily_icon_height,
        "Daily",
        (GFXfont *)&OpenSans12,
        EPD_WIDTH - 300,
        STATUS_BAR_HEIGHT + 20, 
        15, 
        0,
        WHITE_ON_BLACK, 
        framebuffer,
        showDailyWeather
    );

    epd_draw_tertiary_button_icon(
        const_cast<uint8_t *>(hourly_icon_data), 
        hourly_icon_width,
        hourly_icon_height,
        "Hourly",
        (GFXfont *)&OpenSans12,
        EPD_WIDTH - 150, 
        STATUS_BAR_HEIGHT + 20, 
        15, 
        0,
        WHITE_ON_BLACK, 
        framebuffer,
        showHourlyWeather
    );

    // 1st column of information cards
    Rect_t cardArea = {
        EPD_WIDTH / 2 - 470, 
        STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 140, 
        300, 
        100
    };
    epd_draw_horizontal_card(
        const_cast<uint8_t*>(getWeatherIcon(current->icon)),
        temp_icon_width,
        temp_icon_height,
        "Description",
        current->description.c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 20;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(temp_icon_data),
        temp_icon_width,
        temp_icon_height,
        "Temperature",
        current->temperature.c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 + 100;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(temp_icon_data),
        temp_icon_width,
        temp_icon_height,
        "Feels like",
        current->feels_like.c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    // 2nd column of information cards
    cardArea.x = EPD_WIDTH / 2 - 150;
    cardArea.y =STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 140;
    epd_draw_horizontal_card(
        const_cast<uint8_t*>(sunrise_icon_data),
        temp_icon_width,
        temp_icon_height,
        "Sunrise & set",
        (current->sunrise + " - " + current->sunset).c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 20;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(uv_icon_data),
        temp_icon_width,
        temp_icon_height,
        "UV Index",
        current->uvi.c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 + 100;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(cloudy_icon_data),
        temp_icon_width,
        temp_icon_height,
        "Clouds",
        current->clouds.c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    //3rd column of information cards
    cardArea.x = EPD_WIDTH / 2 + 170;
    cardArea.y =STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 140;
    epd_draw_horizontal_card(
        const_cast<uint8_t*>(humidity_icon_data),
        temp_icon_width,
        temp_icon_height,
        "Humidity",
        current->humidity.c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 - 20;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(rain_icon_data),
        temp_icon_width,
        temp_icon_height,
        "Rain",
        current->rain.c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    cardArea.y = STATUS_BAR_HEIGHT + (EPD_HEIGHT - STATUS_BAR_HEIGHT) / 2 + 100;
    epd_draw_horizontal_card(
        const_cast<uint8_t *>(wind_icon_data),
        temp_icon_width,
        temp_icon_height,
        "Wind speed",
        current->wind_speed.c_str(),
        (GFXfont *)&OpenSans12B,
        (GFXfont *)&OpenSans12,
        cardArea,
        30,
        0,
        15,
        WHITE_ON_BLACK,
        framebuffer,
        dummyFunction
    );

    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
}

