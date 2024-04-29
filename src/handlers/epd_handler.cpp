#include <Arduino.h>
#include "epd_driver.h"

#include "../include/handlers/epd_handler.h"

void EPDSetup() {
    epd_init();
    epd_poweron();
    epd_clear();
    
    return;
}