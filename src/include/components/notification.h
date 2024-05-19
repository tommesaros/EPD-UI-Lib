#ifndef NOTIFICATION_H
#define NOTIFICATION_H

/**
 * Triggers a notification that will appear for a short duration
 * in place of a status bar.
 *
 * @param image_data The image data for the notification.
 * @param image_width The width of the image.
 * @param image_height The height of the image.
 * @param primaryLabel The primary label for the notification.
 * @param secondaryLabel The secondary label for the notification.
 */
void epd_trigger_notification(
    uint8_t *image_data,
    int32_t image_width,
    int32_t image_height,
    const char * primaryLabel, 
    const char * secondaryLabel
);

#endif // NOTIFICATION_H