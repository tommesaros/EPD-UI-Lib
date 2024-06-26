#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H

/**
 * Sets up the time.
 * 
 * This function initializes the connection to a NTP server allowing the 
 * user to get current time.
 */
void timeSetup();

/**
 * Gets the current hour.
 * 
 * @return The current hour as an integer.
 */
int getHour();

/**
 * Gets the current minute.
 * 
 * @return The current minute as an integer.
 */
int getMinute();

/**
 * Gets the current time and date formatted as "DD.MM.RRRR"
 * 
 * @return A pointer to a character array containing the current time and date.
 */
char* getDate();

#endif // TIME_HANDLER_H