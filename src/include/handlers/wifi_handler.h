#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

/**
 * @brief Sets up the WiFi connection.
 * 
 * This function is responsible for setting up the WiFi connection.
 * It should be called before any other network-related operations.
 */
void WiFiSetup();

/**
 * @brief Handles WiFi events.
 * 
 * This function is called when a WiFi event occurs.
 * It takes an event parameter of type WiFiEvent_t, which represents the event that occurred.
 * 
 * @param event The WiFi event that occurred.
 */
void WiFiEvent(WiFiEvent_t event);

#endif // WIFI_HANDLER_H
