#ifndef NOTIFICATION_H
#define NOTIFICATION_H

//TODO DESCRIPTION
void epd_trigger_notification(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    const char * primaryLabel, 
    const char * secondaryLabel
);

#endif // NOTIFICATION_H