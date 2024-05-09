#ifndef TOUCH_HANDLER_H
#define TOUCH_HANDLER_H

#include <touch.h>

TouchClass TouchSetup();
void AddTouchPoint(int x, int y, int width, int height, void (*function)());
void ClearTouchPoints();

#endif // TOUCH_HANDLER_H
